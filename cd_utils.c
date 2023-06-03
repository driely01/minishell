/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:00:40 by markik            #+#    #+#             */
/*   Updated: 2023/06/02 19:33:28 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	updating_pwd_tool(t_envs *tmp_new, int *i)
{
	char	*str;

	if (*i)
	{
		printf("cd: error retrieving current directory: getcwd: cannot\
		access parent directories: No such file or directory\n");
		str = ft_strdup(tmp_new->value);
		free(tmp_new->value);
		tmp_new->value = ft_strjoin(str, "/..");
	}
	(*i) = 1;
}

void	updating_pwd_tools(t_envs *tmp_new, char *str, int *i)
{
	(*i) = 0;
	free(tmp_new->value);
	tmp_new->value = ft_strdup(str);
	free(str);
}
