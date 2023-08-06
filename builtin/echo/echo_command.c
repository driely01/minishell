/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:19:32 by del-yaag          #+#    #+#             */
/*   Updated: 2023/08/06 09:40:21 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	printf_echo_args(char **command, size_t *i, int is_option, int fd)
{	
	while (command[*i])
	{
		ft_putstr_fd(command[*i], fd);
		ft_putstr_fd(" ", fd);
		(*i)++;
	}
	if (!is_option)
		ft_putstr_fd("\n", fd);
}

int	skip_n(char **command, size_t *i)
{
	size_t	j;

	j = 0;
	if (command[*i] && command[*i][j] == '-' && command[*i][j + 1] == 'n')
		j++;
	else
		return (0);
	while (command[*i] && command[*i][j] == 'n')
		j++;
	if (command[*i] && command[*i][j] == 0)
		return (1);
	return (0);
}

static void	handle_echo_args(char **command, size_t *i, int fd)
{
	if (!ft_strncmp(command[*i], "echo", 4))
	{
		(*i)++;
		if (!command[*i])
			ft_putstr_fd("\n", fd);
		else if (skip_n(command, i))
		{
			while (skip_n(command, i))
				(*i)++;
			if (!command[*i])
				ft_putstr_fd("", fd);
			else
				printf_echo_args(command, i, 1, fd);
		}
		else
			printf_echo_args(command, i, 0, fd);
	}
}

void	echo_command(char **command, int fd)
{
	size_t	i;

	i = 0;
	while (command[i])
	{
		handle_echo_args(command, &i, fd);
		if (command[i])
			i++;
	}
}
