/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:13:14 by del-yaag          #+#    #+#             */
/*   Updated: 2023/08/06 09:23:20 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isalnum_expand(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	valid_expand(char c)
{
	if (c == '_' || is_alpha(c))
		return (1);
	return (0);
}

int	check_ifseperator_file(t_exp *expand, int z)
{
	int	fd;

	fd = open(&expand->str[z], O_RDWR, 0777);
	if (fd != -1)
		close(fd);
	return (fd);
}

void	expand_if_seperator(t_exp *expand, char *str, size_t *i, size_t *j)
{
	str[*j] = 39;
	(*j)++;
	str[*j] = expand->str[*i];
	(*j)++;
	str[*j] = 39;
	(*j)++;
	(*i)++;
}
