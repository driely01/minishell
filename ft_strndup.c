#include "minishell.h"

char *ft_strndup(char *str, int start, int end)
{
    char    *string;
    int i;

    i = 0;
    string = malloc(sizeof(char) * (end - start) + 2);
    while(end - start >= 0)
    {
            string[i] = str[start];
            i++;
            start++;
    }
    string[i] = '\0';
    return (string);
}