/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:16:16 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/22 17:10:19 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(t_token **token, char *input)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(input);
	while (i < len)
	{
		if (ft_isalnum(input[i]))
		{
			handle_char(token, input, &i);
		}
		else if ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
			handle_whitespace(input, &i);
		else if (ft_isseparators(input[i]))
			handel_separators(token, input, &i);
		else if (is_qoute(input[i]) || ft_isalnum(input[i]))
		{
			handel_qoutes(token, input, &i);
		}
		// else
		// 	handel_specialchar(token, input, &i);
	}
}

void	minishell_tools(t_token **token, char *input)
{
	char	*trimed;

	trimed = ft_strtrim(input, " '\t''\r''\f''\v'");
	free(input);
	tokenizer(token, trimed);
}
