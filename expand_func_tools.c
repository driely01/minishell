/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_func_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:15:21 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/28 12:53:35 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flag(char *tab, size_t *i, size_t start)
{
	int	x;

	x = 1;
	if ((*i) > ft_strlen(tab))
		return (0);
	if ((*i) == start)
		return (1);
	while (start <= (*i))
	{
		if (tab[start] == 34)
		x += 1;
		start++;
	}
	if (x % 2 == 0)
		return (0);
	return (1);
}

void	expand_env_single_quote(t_exp *expand, char *input, size_t *i)
{
	expand->x++;
	(*i)++;
	if (expand->x % 2 == 1)
	{
		while ((*i) < ft_strlen(input) && input[(*i)] != 39)
			(*i)++;
	}
}

char	*expand_env_double_quote(t_exp *expand, t_envs *envs,
			char *input, size_t *i)
{
	char	*tab;

	expand->flag = 1;
	if (input[*i] != '$')
	(*i)++;
	if (input[*i] == 39)
		(*i)++;
	expand->start = (*i);
	if (input[*i] == '$')
	{
		tab = change_line_input(expand, envs, input, i);
		input = ft_strdup(tab);
		free(tab);
	}
	if (input[*i] == 34)
		(*i)++;
	expand->flag = check_flag(input, i, expand->start);
	return (input);
}

char	*expand_env_char(t_exp *expand, t_envs *envs, char *input, size_t *i)
{
	char	*tab;

	tab = change_line_input(expand, envs, input, i);
	input = ft_strdup(tab);
	free(tab);
	return (input);
}

void	isquote_env(char *input, size_t *i)
{
	int	c;

	if (is_qoute(input[*i]))
	{
		c = input[*i];
		(*i)++;
		while ((*i) < ft_strlen(input) || input[*i] == 31)
		{
			if (input[*i] == c)
				break ;
			(*i)++;
		}
		(*i)++;
		if (*i < ft_strlen(input) && is_qoute(input[*i]))
			isquote_env(input, i);
		while (*i < ft_strlen(input) && input[*i] != 32
			&& !ft_isseparators(input[*i]))
		{
			(*i)++;
			if (is_qoute(input[*i]))
				isquote_env(input, i);
		}
		return ;
	}
}
