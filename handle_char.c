#include "minishell.h"

int    handle_char(t_token **token, char *input, size_t *i)
{
    t_token *head;
    char    *str;
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
    if (input[*i] == 34)
    {
        if (double_qoutes(token, input, i) == -1)
            return (-1);
        str = ft_strdup(head->next->string);
        head->string = ft_strjoin(head->string, str);
        head->next = NULL;
        free(head->next);
        free(str);
    }
    else if (input[*i] == 39)
    {
        if (single_qoutes(token, input, i) == -1)
            return (-1);
        str = ft_strdup(head->next->string);
        head->string = ft_strjoin(head->string, str);
        head->next = NULL;
        free(head->next);
        free(str);
    }
    return (0);
}