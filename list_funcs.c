/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:41:55 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/22 12:35:17 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_list(t_token *list)
{
	t_token	*next;
	
	while (list)
	{
		next = list->next;
		free(list);
		list = next;
	}
}

void	add_node(t_token **token)
{
	t_token	*head;
	t_token *new;

	if (!(*token))
	{
		*token = malloc(sizeof(t_token));
		(*token)->next = NULL;
	}
	else
	{
		head = *token;
		while (head && head->next)
			head = head->next; 
		new = malloc(sizeof(t_token));
		head->next = new;
		new->next = NULL;
	}
	if (!(*token))
		clear_list(*token);
}
