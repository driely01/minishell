#include "minishell.h"

void    hundle_char(t_token **token, char *input, int *i)
{
    t_token *head;

    head = *token;
    while(head->next)
        head = head->next;
    
}