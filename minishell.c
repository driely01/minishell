/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:38:29 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/21 21:27:45 by del-yaag         ###   ########.fr       */
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

	if (!(*token))
	{
		(*token) = malloc(sizeof(t_token));
		head = (*token);
	}
	else
	{
		(*token)->next = malloc(sizeof(t_token));
		(*token) = (*token)->next;
	}
	if (!(*token))
		clear_list(*token);
}

int	main(int argc, char **argv, char **env) {
	// write some code
	return (0);
}