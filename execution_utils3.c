/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:48:47 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/06 15:19:21 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_executing(t_token **token, t_exec *help, t_envs **envs, char **env)
{
	t_token	*head;
	size_t	pipe_count;
	size_t	i;

	pipe_count = pipe_exist(token);
	if (!pipe_count)
		return ;
	making_pipe(&help, pipe_count);
	help->pid_child1 = execute_cmd_tools(token, envs, env, help);
	i = 1;
	while (i < pipe_count)
	{
		head = head_next_pipe(token, i);
		help->infile = help->pipe_fd[(i) - 1][0];
		help->outfile = help->pipe_fd[i][1];
		help->pid_child3 = execute_cmd_tools(&head, envs, env, help);
		i++;
	}
	initialize_pipe(token, &head, &help, i);
	help->pid_child2 = execute_cmd_tools(&head, envs, env, help);
	close_and_free(&help);
	pip_waitpid(help->pid_child1, help->pid_child2, help->pid_child3);
}

int	here_doc_child(t_token **token, t_envs *envs, char *argv, int *fd)
{
	char	*buffer;
	char	*stop_sign;

	stop_sign = ft_strdup(argv);
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		buffer = readline("heredoc> ");
		if (buffer == NULL || (ft_strlen(buffer) == ft_strlen(stop_sign)
				&& (!ft_strncmp(buffer, stop_sign, ft_strlen(stop_sign)))))
			return (free(stop_sign), free(buffer), exit(0), 0);
		if ((*token) && (*token)->type == 8 && (*token)->here_exp == 0)
		{
			buffer = expand_input(envs, buffer);
			buffer = remove_character(buffer, 31);
		}
		write(fd[1], buffer, ft_strlen(buffer));
		write(fd[1], "\n", 1);
		free(buffer);
	}
	return (close(fd[0]), close(fd[1]), exit(0), 0);
}

int	_here_doc(char *argv, t_token **token, t_envs *envs)
{
	pid_t	pid;
	int		fake_status;
	int		fd[2];

	pipe(fd);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 0);
	else if (pid == 0)
		here_doc_child(token, envs, argv, fd);
	close(fd[1]);
	waitpid(pid, &fake_status, 0);
	signal(SIGINT, signal_handler);
	if (fake_status == 2)
	{
		write(1, "\n", 1);
		return (-1);
	}
	return (fd[0]);
}

int	here_doc_exec(t_token *tmp, t_token **head, t_envs *envs, int *infile_fd)
{
	int	here_fd;

	*head = (*head)->next;
	here_fd = _here_doc((*head)->string, head, envs);
	if (here_fd == -1)
		return (-1);
	if (((*head)->next && (*head)->next) || tmp->type < 2)
		*infile_fd = here_fd;
	return (0);
}

int	redirection_in_exec(t_token *tmp, t_token **head, int *infile_fd)
{
	*head = (*head)->next;
	*infile_fd = redirection_in((*head)->string);
	if (*infile_fd == -1)
		return (-1);
	if (!(*head)->next)
		if (!tmp || tmp->type >= 2)
			return (-1);
	return (0);
}
