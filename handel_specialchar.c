#include "minishell.h"

void    handel_specialchar(t_token **token, char *input, size_t *i)
{
    t_token *head;
    int start;
    int end;

    add_node(token);
    head = *token;
    start = *i;
    while(head && head->next)
        head = head->next;
    while ((input[*i] && input[*i] < 9 && input[*i] > 13)\
    || (input[*i] && input[*i] != 32))
        (*i)++;
    end = *i - 1;
    head->string = ft_strndup(input, start, end);
    printf("special char: %s\n", head->string);
}