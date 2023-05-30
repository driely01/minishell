/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:16:16 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/30 20:35:57 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_what(t_token **token, char *input, size_t *i)
{
	if (ft_isalnum(input[*i]))
	{
		if (handle_char(token, input, i) == -1)
			return (-1);
	}
	else if ((input[*i] >= 9 && input[*i] <= 13) || input[*i] == 32)
		handle_whitespace(input, i);
	else if (ft_isseparators(input[*i]))
	{
		if (handel_separators(token, input, i) == -1)
			return (-1);
	}
	else if (input[*i] == 34)
	{
		if (double_qoutes(token, input, i) == -1)
			return (-1);
	}
	else if (input[*i] == 39)
	{
		if (single_qoutes(token, input, i) == -1)
			return (-1);
	}
	return (0);
}

int	tokenizer(t_token **token, char *input)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(input);
	while (i < len)
	{
		if (check_what(token, input, &i) == -1)
			return (-1);
	}
	return (0);
}

char	*remove_character(char *line, int c)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = strlen(line);
	while (i < len)
	{
		if (line[i] != c)
			line[j++] = line[i];
		i++;
	}
	line[j] = '\0';
	str = ft_strdup(line);
	free(line);
	return (str);
}

char	*minishell_tools(t_token **token, t_envs *envs, char *input)
{
	char	*trimed;
	char	*line;

	trimed = ft_strtrim(input, " \t\r\f\v");
	if (!trimed)
	{
		free(input);
		return (NULL);
	}
	free(input);
	line = expand_input(envs, trimed);
	line = remove_character(line, 31);
	if (tokenizer(token, line) == -1)
		return (clear_list(token), free(line), NULL);
	if (!syntax_error(*token))
		return (clear_list(token), free(line), NULL);
	return (line);
}
