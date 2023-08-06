/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:06:20 by markik            #+#    #+#             */
/*   Updated: 2023/08/06 09:40:30 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	updating_pwd(t_envs *envs)
{
	t_envs		*head;
	t_envs		*tmp_old;
	t_envs		*tmp_new;
	char		*str;
	static int	i;

	head = envs;
	tmp_old = NULL;
	tmp_new = NULL;
	while (head)
	{
		update_tmp(head, &tmp_old, &tmp_new);
		head = head->next;
	}
	if (tmp_old && tmp_old->value)
	{
		free(tmp_old->value);
		tmp_old->value = ft_strdup(tmp_new->value);
	}
	str = getcwd(NULL, 0);
	if (!str)
		updating_pwd_tool(tmp_new, &i);
	else
		updating_pwd_tools(tmp_new, str, &i);
}

void	executing_cd_allone(t_envs *envs)
{
	char	*str;

	str = ft_getenv(envs, "HOME");
	if (!str || chdir(str))
	{
		g_status = 256;
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		return ;
	}
	updating_pwd(envs);
}

void	executing_last_cd(t_envs *envs)
{
	char	*str;

	str = ft_getenv(envs, "OLDPWD");
	if (!str || chdir(str))
	{
		g_status = 256;
		ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
		return ;
	}
	updating_pwd(envs);
}

void	executing_cd(t_envs *envs, char *path)
{
	if (!path || chdir(path))
	{
		perror("cd");
		g_status = 256;
		return ;
	}
	updating_pwd(envs);
}

int	check_cd(t_token **token, t_envs *envs)
{
	t_token	*head;

	head = *token;
	if ((head && ft_strlen(head->string) == ft_strlen("cd")
			&& !ft_strncmp(head->string, "cd", ft_strlen("cd"))))
	{
		if (!head->next)
			return (executing_cd_allone(envs), 0);
		else
		{
			if (!help_cd(head, envs))
				return (0);
		}
	}
	return (0);
}
