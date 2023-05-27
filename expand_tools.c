/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:12:10 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/27 21:08:01 by del-yaag         ###   ########.fr       */
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
	while (input[*i] && valid_expand(input[*i]))
		(*i)++;
}

void	search_env(t_exp *expand, t_envs *envs, char *input, size_t *i)
{
	size_t	b;

	expand->cli_end = *i - 1;
	expand->tab = ft_strndup(input, expand->cli_start, expand->cli_end);
	expand->str = ft_getenv(envs, expand->tab);
	if (!expand->str)
	{
		free(expand->tab);
		b = expand->cli_start - 1;
		while (b <= expand->cli_end)
		{
			input[b] = 31;
			b++;
		}
		*i = b;
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
	free(expand->tab);
	return (input);
}
