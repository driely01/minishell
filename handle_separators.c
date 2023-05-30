/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_separators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:31:29 by markik            #+#    #+#             */
/*   Updated: 2023/05/29 14:32:59 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	choosen_separator(char *input, size_t *i, int c)
{
	while (input[*i] == c)
		(*i)++;
}

static void	fill_separators(t_token **token, t_var *var, char *input)
{
	t_token	*head;

	add_node(token);
	head = *token;
	while (head && head->next)
		head = head->next;
	head->string = ft_strndup(input, var->start, var->end);
	head->type = SEPAR;
}

int	handel_separators(t_token **token, char *input, size_t *i)
{
	t_var	var;

	var.start = *i;
	if (input[*i] == '|')
		choosen_separator(input, i, '|');
	else if (input[*i] == '<')
		choosen_separator(input, i, '<');
	else if (input[*i] == '>')
		choosen_separator(input, i, '>');
	var.end = *i - 1;
	fill_separators(token, &var, input);
	return (0);
}
