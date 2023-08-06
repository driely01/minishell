/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_qoutes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:57:18 by del-yaag          #+#    #+#             */
/*   Updated: 2023/08/06 09:23:20 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	single_qoutes(t_token **token, char *input, size_t *i)
{
	static int	flag;
	t_var		var;

	var.flag = &flag;
	if (skip_qoutes(input, &var, i) == -1)
		return (-1);
	if (set_check_flag(token, &var, input, i) == -1)
		return (-1);
	if (ft_isalnum(input[*i]))
	{
		if (is_char(token, &var, input, i) == -1)
			return (-1);
	}
	else if (input[*i] == 34)
	{
		if (double_qoutes(token, input, i) == -1)
			return (-1);
		if (!qoutes(token, &var))
			return (0);
	}
	return (0);
}

int	double_qoutes(t_token **token, char *input, size_t *i)
{
	static int	flag;
	t_var		var;

	var.flag = &flag;
	if (skip_doubleqoutes(input, &var, i) == -1)
		return (-1);
	if (set_check_dflag(token, &var, input, i) == -1)
		return (-1);
	if (ft_isalnum(input[*i]))
	{
		if (is_char(token, &var, input, i) == -1)
			return (-1);
	}
	else if (input[*i] == 39)
	{
		if (single_qoutes(token, input, i) == -1)
			return (-1);
		if (!qoutes(token, &var))
			return (0);
	}
	return (0);
}
