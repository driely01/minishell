/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:06:20 by markik            #+#    #+#             */
/*   Updated: 2023/06/03 18:29:03 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	updating_pwd(t_envs *envs)
{
	t_envs		*head;
	t_envs		*tmp_old;
	t_envs		*tmp_new;
	char		*str;
	static int	i;

	head = envs;
	while (head)
	{
		if (head->name && ft_strlen(head->name) == ft_strlen("OLDPWd")
			&& !ft_strncmp(head->name, "OLDPWD", ft_strlen("OLDPWD")))
			tmp_old = head;
		else if (head->name && ft_strlen(head->name) == ft_strlen("PWD")
			&& !ft_strncmp(head->name, "PWD", ft_strlen("PWD")))
			tmp_new = head;
			head = head->next;
	}
	free(tmp_old->value);
	tmp_old->value = ft_strdup(tmp_new->value);
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
		printf("Minishell: cd: HOME not set\n");
		return ;
	}
	updating_pwd(envs);
}

void	executing_last_cd(t_envs *envs)
{
	char	*str;

	str = ft_getenv(envs, "OLDPWD");
	if (!str || chdir(str))
		printf("Minishell: cd: OLDPWD not set\n");
	updating_pwd(envs);
}

void	executing_cd(t_envs *envs, char *path)
{
	if (!path || chdir(path))
		perror("cd");
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
			head = head->next;
			if (head->string[0] == '-')
			{
				if (head && ft_strlen(head->string) == ft_strlen("-")
					&& !ft_strncmp(head->string, "-", ft_strlen("-")))
					executing_last_cd(envs);
				else
					printf("Minishell: cd: %s: invalid option\n", head->string);
			}
			else if (head->type >= 2)
				return (0);
			else
				executing_cd(envs, head->string);
		}
	}
	return (0);
}
