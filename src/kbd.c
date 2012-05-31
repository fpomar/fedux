#include "../include/kasm.h"

unsigned char scancodes[128] =
{
	0,  27,
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	'-', '=', 
	'\b',	/* Backspace */
	'\t',	/* Tab */
 	'q', 'w', 'e', 'r',	't', 'y', 'u', 'i', 'o', 'p',
	'[', ']', '\n',	/* Enter key */
	0,			/* 29   - Control */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
	'\'', '`',   0,		/* Left shift */
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,				/* Right shift */
	'*',
	0,	/* Alt */
	' ',	/* Space bar */
	0,	/* Caps lock */
	0,	/* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,	/* < ... F10 */
	0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

static int tickpos = 0;


void keyboard_handler()
{
	char *video = (char *) 0xb8000;
	int scancode = _inb(0x60);

	/* Only when pressed */

	if (!(scancode & 0x80))
	{
		scancode &= 0x7F;
    	video[tickpos]= scancodes[scancode];
    	tickpos += 2;
	}
}

