#include "../../include/kasm.h"
#include "../../include/stdio.h"
#include "../../include/string.h"
#include "../../include/software/commons.h"
#include "../../include/serialman.h"

void chat_help(char *args);
void chat_setname(char *args);
void chat_exit(char *args);
void chat_init(void);

static bool exit = false;

static char name[64];

typedef struct {
    char *name;
    void (*exec)(char *args);
} chat_command_t;


static chat_command_t chat_commands[] = {
    { "/help", chat_help },
    { "/setname", chat_setname },
    { "/exit", chat_exit },
    { NULL, NULL }
};

void
chat_help(char *args)
{
    printf("Type /help to show this message again.\n");
    printf("Type /setname to change your nickname.\n");
    printf("Type /exit to leave the chat.\n");
}

void
chat_setname(char *args)
{
    int length = 0;
    name[0] = 0;

    do
    {
        printf("Please enter your nickname: ");
        gets(name, 64);
        trim(name);

        length = strlen(name);
    }
    while (length == 0);

    printf("Great! your nickname is now %s\n", name);
}

void
chat_exit(char *args)
{
    printf("Leaving chat.\n");
    exit = true;
}

int
chat_command(char *s)
{
    int i;
    for (i = 0; chat_commands[i].name != NULL; i++)
    {
        if (strcmp(s, chat_commands[i].name) == 0)
        {
            chat_commands[i].exec(s);
            return 1;
        }
    }
    return 0;
}

int
exec_chat(int argc, char **argv)
{
    args_shift(1, &argc, &argv);

    if (argc == 1 && strcmp(argv[0], "--version") == 0)
    {
        printf("chat 1.0 (Fedux release 1.0)\n");
        printf("Copyright (C) 2012 Federico Pomar & Federico Bond\n");
        return 0;
    }

    printf("Welcome to fedux-chat!\n");

    chat_help(NULL);
    chat_setname(NULL);
    chat_init();

    return 0;
}

bool
read_from_local(char *buffer, int *idx)
{
    char ch;
    if (read(STDIN_FILENO, &ch, sizeof(char)))
    {
        buffer[(*idx)++] = ch;
        if (ch == '\n')
        {
            buffer[*idx] = 0;
            write(TTYS0, buffer, *idx);
            *idx = 0;
        }
        return true;
    }
    return false;
}

bool
read_from_remote(char *buffer, int *idx)
{
    char ch;
    if (read(TTYS0, &ch, sizeof(char)))
    {
        /* printf("Read!\n"); */
        /* buffer[(*idx)++] = ch; */
        /* if (ch == '\n') */
        /* { */
            /* buffer[*idx] = 0; */
            /* printf("%s\n", buffer); */
            /* *idx = 0; */
        /* } */
        return true;
    }
    return false;
}

void
chat_init()
{
    char in[256];
    char out[256];
    char ch;

    int in_idx = 0, out_idx = 0;
    bool vread;

    while (true)
    {
        vread = read_from_local(out, &out_idx);
        if (!vread)
            vread = read_from_remote(in, &in_idx);
    }
}

