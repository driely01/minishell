/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:45:38 by del-yaag          #+#    #+#             */
/*   Updated: 2023/08/06 09:23:20 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_calculater(const char *str, int i, int sign)
{
	size_t	res;
	size_t	old;

	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		old = res;
		res *= 10;
		if ((res / 10) != old && sign == 1)
			return (-1);
		if ((res / 10) != old && sign == -1)
			return (0);
		res += (str[i] - 48);
		i++;
	}
	return (res * sign);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	return (ft_calculater(str, i, sign));
}
