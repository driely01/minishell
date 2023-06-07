/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:05:59 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/07 11:33:49 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_line_byword(t_exp *expand, char *str, size_t *z)
{
	expand->replace_word_a = expand->replace_word_i - 1;
	while (expand->str[expand->replace_word_j])
	{
		str[expand->replace_word_a] = expand->str[expand->replace_word_j];
		expand->replace_word_a++;
		expand->replace_word_j++;
	}
	*z = expand->replace_word_a;
	expand->replace_word_i = expand->cli_end + 1;
}

void	keep_line_byword(t_exp *expand, char *str, char *line)
{
	if (expand->replace_word_a > 0)
	{
		str[expand->replace_word_a] = line[expand->replace_word_i];
		expand->replace_word_a++;
		expand->replace_word_i++;
	}
	else
	{
		str[expand->replace_word_i] = line[expand->replace_word_i];
		expand->replace_word_i++;
	}
}

char	*replace_word(t_exp *expand, char *line, size_t *z)
{
	char	*str;

	expand->replace_word_i = 0;
	expand->replace_word_a = 0;
	expand->replace_word_j = 0;
	expand->replace_word_len = (ft_strlen(line) - (ft_strlen(expand->tab) + 1)
			+ ft_strlen(expand->str) + 1);
	str = malloc(sizeof(char) * expand->replace_word_len);
	if (!str)
		return (NULL);
	while (expand->replace_word_i <= ft_strlen(line))
	{
		if (expand->replace_word_i == expand->cli_start)
			change_line_byword(expand, str, z);
		else
			keep_line_byword(expand, str, line);
	}
	free(line);
	free(expand->str);
	return (str);
}

char	*ft_strenv(t_exp *expand, size_t z, int flag)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	if (check_ifseperator_file(expand, z) != -1)
		return (expand->str);
	len = ft_strlen(expand->str);
	str = malloc(sizeof(char) * len + 3);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (expand->str[i])
	{
		if (i == z)
			expand_if_seperator(expand, str, &i, &j);
		else
			expand_ifnt_seperator(expand, str, &i, &j);
	}
	str[j] = '\0';
	if (flag == 1)
		free(expand->str);
	return (str);
}

char	*handling_complecated_case(t_exp *expand)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (expand->str[i])
	{
		if (ft_isseparators(expand->str[i]))
		{
			expand->str = ft_strenv(expand, i, flag);
			i++;
			i++;
			flag = 1;
		}
		i++;
	}
	if (flag == 0)
		expand->str = ft_strdup(expand->str);
	return (expand->str);
}
