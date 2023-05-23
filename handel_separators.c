/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_separators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:31:29 by markik            #+#    #+#             */
/*   Updated: 2023/05/23 13:05:36 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    choosen_separator(t_token **token, char *input, size_t *i, int c)
{
    while(input[*i] == c)
        (*i)++;
}

void    handel_separators(t_token **token, char *input, size_t *i)
{
    t_token *head;
    size_t  start;
    size_t  end;
    
    start = *i;
    if (input[*i] == '|')
        choosen_separator(token, input, i, '|');
    else if (input[*i] == '<')
        choosen_separator(token, input, i, '<');
    else if (input[*i] == '>')
        choosen_separator(token, input, i, '>');
    if (input[*i] == '\0')
    {
        printf("Syntax Error\n");
        return ;
    }
    end = *i - 1;
    add_node(token);
    head = *token;
    while (head && head->next)
        head = head->next;
    head->string = ft_strndup(input, start, end);
}
