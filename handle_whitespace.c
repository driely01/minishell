#include "minishell.h"

int ft_isspace(int c)
{
    if (c >= 9 && c <= 13 || c == 32)
        return (1);
    return (0);
}

void    handle_whitespace(char *input, size_t *i)
{
    while (ft_isspace(input[*i]))
        (*i)++;
}