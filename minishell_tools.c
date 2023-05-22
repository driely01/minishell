/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:16:16 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/22 20:31:12 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizer(t_token **token, char *input)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(input);
	while (i < len)
	{
		if (ft_isalnum(input[i]))
		{
			if (handle_char(token, input, &i) == -1)
				return (-1);
		}
		else if ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
			handle_whitespace(input, &i);
		else if (ft_isseparators(input[i]))
			handel_separators(token, input, &i);
		else if (input[i] == 34)
		{
			if (double_qoutes(token, input, &i) == -1)
				return (-1);
		}
		else if (input[i] == 39)
			if (single_qoutes(token, input, &i) == -1)
				return (-1);
		// else
		// 	handel_specialchar(token, input, &i);
	}
	return (0);
}

void	minishell_tools(t_token **token, char *input)
{
	char	*trimed;

	trimed = ft_strtrim(input, " \t\r\f\v");
	if (!trimed)
		return;
	free(input);
	tokenizer(token, trimed);
	free(trimed);
}
