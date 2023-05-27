/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:30:08 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/27 17:23:09 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_qoutes(char *input, t_var *var, size_t *i)
{
	var->count = 0;
	(*i)++;
	var->start = *i;
	while (input[*i] && input[*i] != 39)
	{
		if (ft_isseparators(input[*i]) && !here_doc(input))
		{
			perror(input);
			return (-1);
		}
		(*i)++;
	}
	if (input[*i] != 39)
	{
		printf("Syntax erorr\n");
		*(var->flag) = 0;
		return (-1);
	}
	var->end = *i - 1;
	(*i)++;
	return (0);
}

int	skip_doubleqoutes(char *input, t_var *var, size_t *i)
{
	(*i)++;
	var->start = *i;
	while (input[*i] && input[*i] != 34)
	{
		if (ft_isseparators(input[*i]) && !here_doc(input))
		{
			perror(input);
			return (-1);
		}
		(*i)++;
	}
	if (input[*i] != 34)
	{
		printf("Syntax erorr\n");
		*(var->flag) = 0;
		return (-1);
	}
	var->end = *i - 1;
	(*i)++;
	return (0);
}

int	flag_two(t_token **token, t_var *var, char *input, size_t *i)
{
	t_token	*head;

	while (input[*i] && input[*i] == 39)
	{
		var->count++;
		(*i)++;
	}
	if (var->count % 2 == 0)
	{
		head = *token;
		while (head && head->next)
			head = head->next;
	}
	else
	{
		(*i)--;
		*(var->flag) = 3;
		if (single_qoutes(token, input, i) == -1)
			return (-1);
	}
	return (0);
}

int	flagd_two(t_token **token, t_var *var, char *input, size_t *i)
{
	t_token	*head;

	while (input[*i] && input[*i] == 34)
	{
		var->count++;
		(*i)++;
	}
	if (var->count % 2 == 0)
	{
		head = *token;
		while (head && head->next)
			head = head->next;
	}
	else
	{
		(*i)--;
		*(var->flag) = 3;
		if (single_qoutes(token, input, i) == -1)
			return (-1);
	}
	return (0);
}

int	set_check_flag(t_token **token, t_var *var, char *input, size_t *i)
{
	if (*(var->flag) == 1)
		fill_and_join(token, var, input, 2);
	else if (*(var->flag) == 2)
	{
		if (flag_two(token, var, input, i) == -1)
			return (-1);
	}
	else if (*(var->flag) == 3)
		fill_and_join(token, var, input, 2);
	else
	{
		add_node(token);
		fill_and_join(token, var, input, 1);
	}
	if (input[*i] == 39 && input[*i + 1] != 39)
		*(var->flag) = 1;
	else if (input[*i] == 39 && input[*i + 1] == 39)
		*(var->flag) = 2;
	else
		*(var->flag) = 0;
	return (0);
}
