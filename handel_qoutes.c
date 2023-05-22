#include "minishell.h"

char    *ft_fillstr(char *input, int start, int end, int count)
{
    char *str;
    int     i;
    int     len;

    i = 0;
    len = end - start - count;
    str = malloc(sizeof(char) * (end - start - count) + 1);
    while(i < len)
    {
        if (input[start] == 34)
            start++;
        else
        {
            str[i] = input[start];
            i++;
            start++;
        }
    }
    str[i] = '\0';
    return (str);
}



void    handel_qoutes(t_token **token, char *input, size_t *i)
{
    t_token *head;
    char    *str;
    int start;
    int end;


    (*i)++;
    start = *i;
    while (input[*i] && input[*i] != 34)
        (*i)++;
    end = *i - 1;
    (*i)++;
    str = ft_strndup(input, start, end);
    if (input[*i] == 34 || input[*i] == 39)
        quote_after(token, str);
    else if (ft_isalnum(input[*i]))
        caractere_after(token, str);
    else if (ft_isseparators(input[*i]))
        seperators_spaces_after(token, str);
    // add_node(token);
    // head = *token;
    // while(head && head->next)
    //     head = head->next;
    // (*token)->string = ft_strndup(input, start, end);
    // (*token)->next = NULL;
    // printf("%s\n", (*token)->string);
}