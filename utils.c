#include "header.h"

void ft_putstr(char *s1, char *s2, int fd)
{
    int i;

    i = 0;
    if (s1)
    {
        while (s1[i])
            write(fd, &s1[i++], 1);
    }
    if (s2)
    {
        while (s2[i])
            write(fd, &s2[i++], 1);
    }
    write(fd, "\n", 1);
}

void ft_error()
{
    write(2, "error: fatal\n", 13);
    exit(1);
}