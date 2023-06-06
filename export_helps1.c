/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helps1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:25:14 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/06 18:06:31 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_equal_tool(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

void	export_ex(t_token *head, t_envs **envs, int fd)
{
	if (head && head->type < 2)
	{
		ft_putstr_fd("env: illegal option or arguments\n", fd);
		g_status = 256;
	}
	else
		execute_env(envs, fd);
}
