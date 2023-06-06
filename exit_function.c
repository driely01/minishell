/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:02:30 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/06 17:16:54 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	skip_spaces(char *str, int *sign)
{
	size_t	i;

	i = 0;
	(*sign) = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			(*sign) *= -1;
		i++;
	}
	return (i);
}

static unsigned long long	ft_atoi_exit(char *str, t_token *token,
	t_envs *envs, int flag)
{
	unsigned long long	res;
	unsigned long long	mood;
	int					sign;
	size_t				i;

	i = skip_spaces(str, &sign);
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += (str[i] - 48);
		i++;
	}
	if (sign == 1 && res > LONG_MAX)
		ft_error(str, token, envs, flag);
	else if (sign == -1 && res > LONG_MAX)
	{
		mood = 9223372036854775807;
		if (res > mood + 1)
			ft_error(str, token, envs, flag);
	}
	return (res * sign);
}

static int	is_number(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

int	exit_cases(t_token *token, t_token *head, t_envs *envs, int flag)
{
	unsigned long long	number;

	if (!token)
		ft_error_two(head, envs, flag);
	else if (token && is_number(token->string) && !token->next)
	{
		number = ft_atoi_exit(token->string, head, envs, flag);
		if (!flag)
			ft_putstr_fd("exit\n", 2);
		exit (number);
	}
	else if (token && !is_number(token->string) && !token->next)
		ft_error(token->string, token, envs, flag);
	else if (token && token->type < 2 && token->next->type < 2)
	{
		if (!flag)
		{
			ft_putstr_fd("exit\nbash: exit: too many arguments\n", 2);
			g_status = 256;
		}
		return (0);
	}
	return (1);
}
