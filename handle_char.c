#include "minishell.h"

void    handle_char(t_token **token, char *input, size_t *i)
{
    t_token *head;
    int start;
    int end;
    int count;

    start = *i;
    while (input[*i] && ft_isalnum(input[*i]))
        (*i)++;
    end = *i - 1;
    add_node(token);
    head = *token;
    while(head && head->next)
        head = head->next;
    head->string = ft_strndup(input, start, end);
    printf("%s\n", head->string);
}