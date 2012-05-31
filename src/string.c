#include "../include/string.h"

char *
strcpy(char *dest, const char *src)
{
    char *ret = dest;
    while (*src != '\0')
    {
        *dest++ = *src++; 
    }
    *dest = '\0';
    return ret;
}

char *
strncpy(char *dest, const char *src, size_t n)
{
    char *ret = dest;
    int i = 0;
    while (i < n && *src != '\0')
    {
        *dest++ = *src++; 
        i++;
    }
    while (i < n)
    {
        *dest++ = '\0';
        i++;
    }
    return ret;
}

size_t
strlen(const char *s)
{
    size_t i = 0;
    while (*s++ != '\0')
    {
        i++;
    }
    return i;
}

int
strcmp(const char *s1, const char *s2)
{
    int i = 0;
    while (s1[i] == s2[i])
    {
        i++;
    }
    return *s1 - *s2;
}

int
strncmp(const char *s1, const char *s2, size_t n)
{
    int i = 0;
    while (i < n && s1 == s2)
    {
        i++;
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

void *
memcpy(void *dest, const void *src, size_t n)
{
    char *d = (char *)dest;
    char *s = (char *)src;
    while (n--)
    {
        *d++ = *s++;
    }
    return dest;
}

int
memcmp(const void *s1, const void *s2, size_t n)
{
    unsigned char *c1 = (unsigned char *)s1;
    unsigned char *c2 = (unsigned char *)s2;
    while (--n && *c1 == *c2)
    {
        c1++;
        c2++;
    }
    return *c1 - *c2;
}

void *
memset(void *s, int c, size_t n)
{
    unsigned char *p = (unsigned char *)s;
    while (n--)
    {
        *p++ = c;
    }
    return s;
}
