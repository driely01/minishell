/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:55:38 by markik            #+#    #+#             */
/*   Updated: 2023/06/07 13:56:45 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	executing_my_command(t_token **token, t_envs **envs,
	char **env, t_exec *help)
{
	pid_t	pid;

	help->command = NULL;
	if (!help->semi_command)
		return (-1);
	help->path = ft_split(ft_getenv(*envs, "PATH"), ':');
	help->command = ft_split(help->semi_command, ' ');
	free(help->semi_command);
	if (if_builting(help->command[0]) == 1 && help->pipe_fd == NULL)
	{
		builtin_func(token, envs, help, 0);
		if (help->path)
			free_split(help->path);
		free_split(help->command);
		return (-1);
	}
	pid = exec_command(token, envs, env, help);
	free_split(help->command);
	if (help->path)
		free_split(help->path);
	return (pid);
}

int	inside_loop(t_token *head, t_envs **envs, t_exec *help)
{
	t_token	*tmp;

	while (head)
	{
		if (head->type == 3)
		{
			if (here_doc_exec(tmp, &head, *envs, &help->infile) == -1)
				return (-1);
		}
		else if (head->type == 5 || head->type == 6 || head->type == 4)
		{
			if (execute_cmd_exec(tmp, &head, &help->infile,
					&help->outfile) == -1)
				return (-1);
		}
		else if (head->type == 7)
			break ;
		else
		help->semi_command = semi_command_exec(&head, help->semi_command);
		tmp = head;
		head = head->next;
	}
	return (0);
}

pid_t	execute_cmd_tools(t_token **token, t_envs **envs,
	char **env, t_exec *help)
{
	t_token	*head;
	pid_t	pid;

	help->semi_command = NULL;
	head = *token;
	if (inside_loop(head, envs, help) == -1)
		return (free(help->semi_command), -1);
	pid = executing_my_command(token, envs, env, help);
	return (pid);
}

void	execute_cmd(t_token **token, t_envs **envs, char **env)
{
	t_exec	help;
	pid_t	pid;

	help.infile = STDIN_FILENO;
	help.outfile = STDOUT_FILENO;
	if (pipe_exist(token))
		pipe_executing(token, &help, envs, env);
	else
	{
		help.pipe_fd = NULL;
		pid = execute_cmd_tools(token, envs, env, &help);
		waitpid(pid, &g_status, 0);
		signal(SIGINT, signal_handler);
		if (g_status == 2)
		{
			g_status = 256;
			write(1, "\n", 1);
		}
	}
}
