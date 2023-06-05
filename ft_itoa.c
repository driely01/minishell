/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:41:15 by markik            #+#    #+#             */
/*   Updated: 2023/06/04 17:19:37 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_status(char *line, size_t i)
{
	char	*char_status;
	size_t len_line;
	size_t	len_status;
	char	*str;
	size_t	j;
	size_t	a;
	size_t	b;

	char_status = ft_itoa(status>>8);
	len_status = ft_strlen(char_status);
	len_line = ft_strlen(line);
	j = 0;
	a = 0;
	b = 0;
	str = malloc(sizeof(char) * (len_line - ft_strlen("$?") + len_status) + 2);
	while(j < len_line)
	{
		if (j == i)
		{
			while(char_status[a])
			{
				str[b] = char_status[a];
				a++;
				b++;
			}
			j = i + 2;
		}
		str[b] = line[j];
		b++;
		j++;
	}
    str[b] = '\0';
    free(char_status);
	free(line);
	return (str);
}

char *dollar_status_check(char *line)
{
	size_t i;

	i = 0;
	while(line[i])
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
		return (0);
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