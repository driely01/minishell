/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:14:43 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/06 17:15:02 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command_help(t_exec *help, size_t *i)
{
	signal(SIGINT, SIG_DFL);
	if (help->infile != STDIN_FILENO)
	{
		dup2(help->infile, 0);
		close(help->infile);
	}
	if (help->outfile != STDOUT_FILENO)
	{
		dup2(help->outfile, 1);
		close(help->outfile);
	}
	if (help->pipe_fd != NULL)
	{
		while (help->pipe_fd[*i])
		{
			close(help->pipe_fd[*i][0]);
			close(help->pipe_fd[*i][1]);
			(*i)++;
		}
	}
}

void	print_command(t_exec *help)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(help->command[0], 2);
	ft_putstr_fd(" command not found\n", 2);
	exit(1);
}
