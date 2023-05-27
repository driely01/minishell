/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_tools_p2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:51:23 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/27 17:23:29 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return (1);
		i++;
	}
	return (0);
}

void	fill_and_join(t_token **token, t_var *var, char *input, int choice)
{
	t_token	*head;

	if (choice == 1)
	{
		head = *token;
		while (head && head->next)
			head = head->next;
		head->string = ft_strndup(input, var->start, var->end);
		head->next = NULL;
	}
	else
	{
		head = *token;
		while (head && head->next)
			head = head->next;
		var->str = ft_strndup(input, var->start, var->end);
		head->string = ft_strjoin(head->string, var->str);
		free(var->str);
	}
}

int	is_char(t_token **token, t_var *var, char *input, size_t *i)
{
	t_token	*head;

	if (handle_char(token, input, i) == -1)
		return (-1);
	head = *token;
	while (head && head->next && head->next->next)
		head = head->next;
	var->str = ft_strdup(head->next->string);
	head->string = ft_strjoin(head->string, var->str);
	free(head->next->string);
	free(head->next);
	head->next = NULL;
	free(var->str);
	return (0);
}

int	qoutes(t_token **token, t_var *var)
{
	t_token	*head;

	head = *token;
	while (head && head->next && head->next->next)
		head = head->next;
	if (!head || !head->next)
		return (0);
	var->str = ft_strdup(head->next->string);
	head->string = ft_strjoin(head->string, var->str);
	free(head->next->string);
	free(head->next);
	head->next = NULL;
	free(var->str);
	return (1);
}

int	set_check_dflag(t_token **token, t_var *var, char *input, size_t *i)
{
	if (*(var->flag) == 1)
		fill_and_join(token, var, input, 2);
	else if (*(var->flag) == 2)
	{
		if (flagd_two(token, var, input, i) == -1)
			return (-1);
	}
	else if (*(var->flag) == 3)
		fill_and_join(token, var, input, 2);
	else
	{
		add_node(token);
		fill_and_join(token, var, input, 1);
	}
	if (input[*i] == 34 && input[*i + 1] != 34)
		*(var->flag) = 1;
	else if (input[*i] == 34 && input[*i + 1] == 34)
		*(var->flag) = 2;
	else
		*(var->flag) = 0;
	return (0);
}
