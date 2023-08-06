/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 20:33:30 by del-yaag          #+#    #+#             */
/*   Updated: 2023/08/06 09:23:20 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_errors(t_token *token)
{
	if (token->type == 2 && !token->next)
	{
		g_status = 256;
		ft_putstr_fd("syntax error near unexpected token `", 2);
		write(2, &token->string[0], 1);
		write(2, "\n", 1);
		return (0);
	}
	if (token->type == 2 && token->string[0] == '|'
		&& ft_strlen(token->string) > 1)
	{
		g_status = 256;
		ft_putstr_fd("syntax error near unexpected token `", 2);
		write(2, &token->string[0], 1);
		write(2, "\n", 1);
		return (0);
	}
	return (1);
}

int	sep_after_sep(t_token *token)
{
	if (token && token->next && token->type == 2 && token->string[0] == '|'
		&& token->next->type == 2 && token->next->string[0] != '|')
		return (1);
	else if (token && token->next && token->type == 2 && token->next->type == 2)
	{
		g_status = 256;
		ft_putstr_fd("syntax error near unexpected token `", 2);
		write(2, &token->string[0], 1);
		write(2, "\n", 1);
		return (0);
	}
	return (1);
}

int	redirection_errors(t_token *token)
{
	if (token && token->next && token->type == 2
		&& (token->string[0] == '>' || token->string[0] == '<')
		&& ft_strlen(token->string) > 2)
	{
		g_status = 256;
		ft_putstr_fd("syntax error near unexpected token `", 2);
		write(2, &token->string[0], 1);
		write(2, "\n", 1);
		return (0);
	}
	return (1);
}

void	typed_sep(t_token *token)
{
	if (token->type == 2)
	{
		if (token->string[0] == '|')
			token->type = PIPE;
		else if (token->string[0] == '<' && token->string[1] == 0)
			token->type = RED_IN;
		else if (token->string[0] == '>' && token->string[1] == 0)
			token->type = RED_OUT;
		else if (token->string[0] == '<' && token->string[1] == '<')
			token->type = HER_EDOC;
		else if (token->string[0] == '>' && token->string[1] == '>')
			token->type = APPEND;
		if (token->string[0] == '<' && token->string[1] == '<'
			&& token->next && token->next->type < 2)
			token->next->type = DELIM;
	}
}

int	syntax_error(t_token *token)
{
	if (token && token->type == 2 && token->string[0] == '|')
	{
		g_status = 256;
		ft_putstr_fd("syntax error near unexpected token `", 2);
		write(2, &token->string[0], 1);
		write(2, "\n", 1);
		return (0);
	}
	while (token)
	{
		if (!pipe_errors(token))
			return (0);
		if (!redirection_errors(token))
			return (0);
		if (!sep_after_sep(token))
			return (0);
		typed_sep(token);
		token = token->next;
	}
	return (1);
}
