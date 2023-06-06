/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:34:42 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/02 19:35:39 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (str1[i] != str2[i] || str1[i] == 0 || str2[i] == 0)
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

void	expand_env_seperators(char *input, size_t *i)
{
	(*i) = (*i) + 2;
	while (*i < ft_strlen(input) && (ft_isspace(input[*i]) || input[*i] == 31))
		(*i)++;
	if (*i < ft_strlen(input) && is_qoute(input[*i]))
	{
		isquote_env(input, i);
		return ;
	}
	while ((*i) < ft_strlen(input) && (!ft_isspace(input[*i])
			|| input[*i] == 31))
	{
		if (ft_isseparators(input[*i]))
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
}

char	*expand_env(t_exp *expand, t_envs *envs, char *input)
{
	size_t	i;

	i = 0;
	while (i < expand->lxk)
	{
		if (input[i] == 39 && expand->flag == 0)
			expand_env_single_quote(expand, input, &i);
		else if ((i < ft_strlen(input) && input[i] == 34) || expand->flag == 1)
			input = expand_env_double_quote(expand, envs, input, &i);
		else if (i < ft_strlen(input) && input[i] == '$')
			input = expand_env_char(expand, envs, input, &i);
		else if (input[i] == '<' && input[i + 1] == '<')
			expand_env_seperators(input, &i);
		else if (i < ft_strlen(input) && input[i] != 39 && input[i] != 34
			&& input[i] != '$')
			i++;
		expand->lxk = ft_strlen(input);
		expand->count = 0;
	}
	return (input);
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

char	*expand_input(t_envs *envs, char *input)
{
	t_exp	expand;
	char	*tab;
	char	*str;

	expand.flag = 0;
	expand.x = 0;
	expand.lxk = ft_strlen(input);
	expand.count = 0;
	tab = expand_env(&expand, envs, input);
	str = ft_strdup(tab);
	free(tab);
	return (str);
}
