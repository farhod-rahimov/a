#include "header.h"

void ft_putstr(char *s1, char *s2)
{
    int i;

    i = 0;
    if (s1)
    {
        while (s1[i])
            write(2, &s1[i++], 1);
    }
    i = 0;
    if (s2)
    {
        while (s2[i])
            write(2, &s2[i++], 1);
    }
    write(2, "\n", 1);
}

void ft_error()
{
    write(2, "error: fatal\n", 13);
    exit(1);
}