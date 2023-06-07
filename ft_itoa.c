/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:41:15 by markik            #+#    #+#             */
/*   Updated: 2023/06/07 11:52:57 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_status(char *line, size_t i)
{
	t_stat	stat;

	stat.char_status = ft_itoa(g_status >> 8);
	stat.len_status = ft_strlen(stat.char_status);
	stat.len_line = ft_strlen(line);
	stat.j = 0;
	stat.a = 0;
	stat.b = 0;
	stat.str = malloc(sizeof(char) * (stat.len_line - ft_strlen("$?")
				+ stat.len_status) + 2);
	if (!stat.str)
		return (NULL);
	while (stat.j < stat.len_line)
	{
		if (stat.j == i)
		{
			while (stat.char_status[stat.a])
				stat.str[stat.b++] = stat.char_status[stat.a++];
			stat.j = i + 2;
		}
		stat.str[stat.b++] = line[stat.j++];
	}
	stat.str[stat.b] = '\0';
	free(stat.char_status);
	return (free(line), stat.str);
}

char	*dollar_status_check(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i + 1] && line[i] == '$' && line[i + 1] == '?')
		{
			line = replace_status(line, i);
			return (line);
		}
		i++;
	}
	return (line);
}

static	int	ft_power(long n)
{
	int	power;

	power = 0;
	if (n <= 0)
	{
		n = -n;
		power++;
	}
	while (n > 0)
	{
		n = n / 10;
		power++;
	}
	return (power);
}

char	*ft_itoa(int n)
{
	int		power;
	char	*str;
	long	nb;

	nb = n;
	power = ft_power(nb);
	str = (char *)malloc(sizeof (char) * (power + 1));
	if (!str)
		return (NULL);
	str[power] = '\0';
	if (nb == 0)
		str[0] = 48;
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[power - 1] = nb % 10 + 48;
		nb = nb / 10;
		power--;
	}
	return (str);
}
