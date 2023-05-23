/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:08:08 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/23 16:32:16 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	else if (ft_isspecialchar(c))
		return (1);
	return (0);
}

int	ft_isspecialchar(int c)
{
	if (c != '|' && c != '>' && c != '<' && !ft_isspace(c) && c != 34 && c != 39 && c != '\0')
		return (1);
	return (0);
}
int	ft_isseparators(int c)
{
	if (c != '|' && c != '>' && c != '<')
		return (0);
	return (1);
}

int	is_qoute(int c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}