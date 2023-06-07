/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:41:55 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/07 11:42:13 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_list(t_token **list)
{
	if (!(*list))
		return ;
	if ((*list)->next)
		clear_list(&(*list)->next);
	free((*list)->string);
	free(*list);
	*list = NULL;
}

void	add_node(t_token **token)
{
	t_token	*head;
	t_token	*new;

	if (!(*token))
	{
		*token = malloc(sizeof(t_token));
		if (!(*token))
			clear_list(token);
		else
			(*token)->next = NULL;
	}
	else
	{
		head = *token;
		while (head && head->next)
			head = head->next;
		new = malloc(sizeof(t_token));
		if (!new)
			clear_list(token);
		else
		{
			head->next = new;
			new->next = NULL;
		}
	}
}
