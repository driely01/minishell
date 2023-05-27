/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:27:59 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/27 17:29:01 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_char(t_token **token, t_var *var)
{
	t_token	*head;

	head = *token;
	while (head && head->next && head->next->next)
		head = head->next;
	var->str = ft_strdup(head->next->string);
	head->string = ft_strjoin(head->string, var->str);
	free(head->next->string);
	free(head->next);
	head->next = NULL;
	free(var->str);
}

int	handle_char(t_token **token, char *input, size_t *i)
{
	t_token	*head;
	t_var	var;

	var.start = *i;
	while (input[*i] && ft_isalnum(input[*i]))
		(*i)++;
	var.end = *i - 1;
	add_node(token);
	head = *token;
	while (head && head->next)
	head = head->next;
	head->string = ft_strndup(input, var.start, var.end);
	if (input[*i] == 34)
	{
		if (double_qoutes(token, input, i) == -1)
			return (-1);
		fill_char(token, &var);
	}
	else if (input[*i] == 39)
	{
		if (single_qoutes(token, input, i) == -1)
			return (-1);
		fill_char(token, &var);
	}
	return (0);
}
