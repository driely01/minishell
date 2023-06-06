/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:12:10 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/06 17:17:24 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_ifnt_seperator(t_exp *expand, char *str, size_t *i, size_t *j)
{
	str[*j] = expand->str[*i];
	(*j)++;
	(*i)++;
}

void	check_dup_dollars(t_exp *expand, char *input, size_t *i)
{
	expand->count++;
	while (input[*i] && input[*i] == '$')
	{
		expand->count++;
		(*i)++;
	}
}

void	expand_compare(t_exp *expand, char *input, size_t *i)
{
	expand->cli_start = *i;
	if (input[*i] >= '0' && input[*i] <= '9')
	{	
		(*i)++;
		return ;
	}
	else
	{	
		if (input[*i] && valid_expand(input[*i]))
			(*i)++;
		while (input[*i] && ft_isalnum_expand(input[*i]))
			(*i)++;
	}
}

void	change_line_help(char *input, size_t *i)
{
	if (*i < ft_strlen(input) && input[*i] != '?'
		&& ft_isalnum_expand(input[*i]))
	{
		input[*i - 1] = 31;
		input[*i] = 31;
	}
}

char	*change_line_input(t_exp *expand, t_envs *envs, char *input, size_t *i)
{
	check_dup_dollars(expand, input, i);
	if (expand->count % 2 == 1)
	{
		expand->test = ft_strdup(input);
		return (free(input), expand->test);
	}
	expand_compare(expand, input, i);
	if (expand->cli_start == *i)
	{
		change_line_help(input, i);
		expand->test = ft_strdup(input);
		return (free(input), expand->test);
	}
	search_env(expand, envs, input, i);
	if (!expand->str)
	{
		expand->test = ft_strdup(input);
		return (free(input), expand->test);
	}
	expand->str = handling_complecated_case(expand);
	input = replace_word(expand, input, i);
	return (free(expand->tab), input);
}
