/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:00:40 by markik            #+#    #+#             */
/*   Updated: 2023/06/06 16:38:28 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	updating_pwd_tool(t_envs *tmp_new, int *i)
{
	char	*str;

	if (*i && tmp_new)
	{
		g_status = 256;
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		str = ft_strdup(tmp_new->value);
		free(tmp_new->value);
		tmp_new->value = ft_strjoin(str, "/..");
	}
	(*i) = 1;
}

void	updating_pwd_tools(t_envs *tmp_new, char *str, int *i)
{
	(*i) = 0;
	if (tmp_new)
	{
		free(tmp_new->value);
		tmp_new->value = ft_strdup(str);
	}
	free(str);
}
