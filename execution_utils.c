/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:44:54 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/06 17:14:21 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ifpath_error(char *command, int choice)
{
	g_status = 404;
	if (choice == 1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(" :Permission Denied\n", 2);
	}
	else if (choice == 2)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(" :no such file or directory\n", 2);
	}
}

char	*ifpath_help(char *command, char **path_splied)
{
	char	*path;
	char	*str;
	int		i;

	i = 0;
	if (!path_splied)
		return (NULL);
	while (path_splied[i])
	{
		str = ft_strjoiness(path_splied[i], "/");
		path = ft_strjoin(str, command);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		i++;
	}
	if (access(path, F_OK) == -1)
		return (NULL);
	return (path);
}

char	*if_path(char *command, char **path_splied)
{
	if (!command)
		return (NULL);
	if (!ft_strncmp(command, "./", ft_strlen("./")))
	{
		if (!access(command, F_OK))
		{
			if (!access(command, X_OK))
				return (ft_strdup(command));
			else
				return (ifpath_error(command, 1), NULL);
		}
		else
			return (ifpath_error(command, 2), NULL);
	}
	else if (!ft_strncmp(command, "/", ft_strlen("/")))
		return (ft_strdup(command));
	return (ifpath_help(command, path_splied));
}

size_t	if_builting(char *head)
{
	if ((head && ft_strlen(head) == ft_strlen("env")
			&& !ft_strncmp(head, "env", ft_strlen("env")))
		|| (head && ft_strlen(head) == ft_strlen("export")
			&& !ft_strncmp(head, "export", ft_strlen("export")))
		|| (head && ft_strlen(head) == ft_strlen("unset")
			&& !ft_strncmp(head, "unset", ft_strlen("unset")))
		|| ((head && ft_strlen(head) == ft_strlen("echo")
				&& !ft_strncmp(head, "echo", ft_strlen("echo"))))
		|| ((head && ft_strlen(head) == ft_strlen("cd")
				&& !ft_strncmp(head, "cd", ft_strlen("cd"))))
		|| ((head && ft_strlen(head) == ft_strlen("pwd")
				&& !ft_strncmp(head, "pwd", ft_strlen("pwd"))))
		|| ((head && ft_strlen(head) == ft_strlen("exit")
				&& !ft_strncmp(head, "exit", ft_strlen("exit")))))
		return (1);
	return (0);
}
