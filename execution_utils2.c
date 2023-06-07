/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:47:35 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/07 13:55:50 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*head_next_pipe(t_token **token, size_t i)
{
	t_token	*head;
	size_t	count;

	count = 0;
	head = *token;
	while (head)
	{
		if (head->type == 7)
			count++;
		if (i == count)
			return (head->next);
		head = head->next;
	}
	return (0);
}

void	making_pipe(t_exec **help, size_t pipe_count)
{
	size_t	i;

	i = 0;
	(*help)->pipe_fd = malloc(sizeof(int *) * (pipe_count + 1));
	if (!(*help)->pipe_fd)
		return ;
	while (i < pipe_count)
	{
		(*help)->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!(*help)->pipe_fd[i])
			return ;
		pipe((*help)->pipe_fd[i]);
		i++;
	}
	(*help)->pipe_fd[i] = NULL;
	(*help)->outfile = (*help)->pipe_fd[0][1];
}

void	close_and_free(t_exec **help)
{
	size_t	i;

	i = 0;
	while ((*help)->pipe_fd[i])
	{
		close((*help)->pipe_fd[i][0]);
		close((*help)->pipe_fd[i][1]);
		free((*help)->pipe_fd[i]);
		i++;
	}
	free((*help)->pipe_fd);
}

void	pip_waitpid(pid_t pid_child1, pid_t pid_child2, pid_t pid_child3)
{
	waitpid(pid_child1, &g_status, 0);
	waitpid(pid_child2, &g_status, 0);
	waitpid(pid_child3, &g_status, 0);
	signal(SIGINT, signal_handler);
	if (g_status == 2)
	{
		g_status = 256;
		write(1, "\n", 1);
	}
}

void	initialize_pipe(t_token **token, t_token **head,
	t_exec **help, size_t i)
{
	*head = head_next_pipe(token, i);
	if (*head == NULL)
		*head = *token;
	(*help)->infile = (*help)->pipe_fd[(i) - 1][0];
	(*help)->outfile = STDOUT_FILENO;
}
