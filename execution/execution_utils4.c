/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:51:02 by del-yaag          #+#    #+#             */
/*   Updated: 2023/08/06 09:23:20 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirection_out_exec(t_token **head, int *outfile_fd)
{
	(*head) = (*head)->next;
	*outfile_fd = redirection_out((*head)->string);
	if (*outfile_fd == -1)
		return (-1);
	return (0);
}

int	redirection_append_exec(t_token **head, int *outfile_fd)
{
	*head = (*head)->next;
	*outfile_fd = redirection_append((*head)->string);
	if (*outfile_fd == -1)
		return (-1);
	return (0);
}

char	*semi_command_exec(t_token **head, char *semi_command)
{
	char	*str;

	if (!semi_command)
		semi_command = ft_strdup((*head)->string);
	else
	{
		str = ft_strjoin(semi_command, " ");
		semi_command = ft_strjoin(str, (*head)->string);
	}
	return (semi_command);
}

int	execute_cmd_exec(t_token *tmp, t_token **head, int *infile_fd,
	int *outfile_fd)
{
	if ((*head)->type == 5)
	{
		if (redirection_in_exec(tmp, head, infile_fd) == -1)
			return (-1);
	}
	else if ((*head)->type == 6)
	{
		if (redirection_out_exec(head, outfile_fd) == -1)
			return (-1);
	}
	else if ((*head)->type == 4)
	{
		if (redirection_append_exec(head, outfile_fd) == -1)
			return (-1);
	}
	return (0);
}
