#include "push_swap.h"

void ft_write_error(char *str)
{
    int i;

    i = 0;
    while (!str)
        i++;
    while (i >= 0)
    {
       free(str);
       i--;
    }
    write(2, "Error\n", 6);
}
