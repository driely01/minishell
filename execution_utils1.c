/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:46:19 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/06 18:23:07 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	exec_command(t_token **token, t_envs **envs, char **env, t_exec *help)
{
	char	*path;
	pid_t	pid;
	size_t	i;

	i = 0;
	path = if_path(help->command[0], help->path);
	if (path == NULL && g_status == 404)
		return (g_status = 256, -1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	else if (pid == 0)
	{
		exec_command_help(help, &i);
		if (if_builting(help->command[0]) == 1)
		{
			builtin_func(token, envs, help, 1);
			exit(0);
		}
		else if (execve(path, help->command, env) == -1)
			print_command(help);
	}
	return (free(path), pid);
}

int	redirection_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
	{
		perror(file);
		return (fd);
	}
	return (fd);
}

int	redirection_out(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror(file);
		return (fd);
	}
	return (fd);
}

int	redirection_append(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		perror(file);
		return (fd);
	}
	return (fd);
}

size_t	pipe_exist(t_token **token)
{
	t_token	*head;
	size_t	counter;

	head = *token;
	counter = 0;
	while (head)
	{
		if (head->type == 7)
			counter++;
		head = head->next;
	}
	return (counter);
}
