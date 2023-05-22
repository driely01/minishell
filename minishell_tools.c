/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:16:16 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/22 10:40:43 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(t_token **token, char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (ft_isalnum(input[i]))
			handle_char(token, input, &i);
		else if ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
			handle_whitespace(input, &i);
		else if (is_separator(input[i]))
			handel_separators(token, input, &i);
		else if (is_qoute(input[i]))
			handel_qoutes(token, input, &i);
		else
			handel_specialchar(token, input, &i);
	}
}

void	minishell_tools(t_token **token, char *input)
{
	char	*trimed;

	trimed = ft_strtrim(input, " '\t''\r''\f''\v'");
	free(input);
	tokenizer(token, trimed);
}
