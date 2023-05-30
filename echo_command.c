/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:19:32 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/30 21:21:39 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	printf_echo_args(t_token *head, int is_option, int fd)
{	
	while (head && head->type != 2)
	{
		ft_putstr_fd(head->string, fd);
		head = head->next;
	}
	if (!is_option)
		ft_putstr_fd("\n", fd);
}

int	skip_n(t_token *token)
{
	size_t	i;

	i = 0;
	if (token && token->string[i] == '-' && token->string[i + 1] == 'n')
		i++;
	else
		return (0);
	while (token && token->string[i] == 'n')
		i++;
	if (token && token->string[i] == 0)
		return (1);
	return (0);
}

static void	handle_echo_args(t_token **head, size_t len, char *command, int fd)
{
	if (!ft_strncmp((*head)->string, command, 4)
		&& len == ft_strlen((*head)->string))
	{
		(*head) = (*head)->next;
		if (!(*head))
			ft_putstr_fd("\n", fd);
		else if (skip_n(*head))
		{
			while (skip_n(*head))
				(*head) = (*head)->next;
			if (!(*head))
				ft_putstr_fd("", fd);
			else
				printf_echo_args((*head), 1, fd);
		}
		else
			printf_echo_args((*head), 0, fd);
	}
	if ((*head) != NULL)
		(*head) = (*head)->next;
}

void	echo_command(t_token *token, int fd)
{
	t_token	*head;
	char	*command;
	size_t	len;

	head = token;
	command = "echo";
	len = ft_strlen(command);
	while (head)
	{
		handle_echo_args(&head, len, command, fd);
		if (head != NULL)
			head = head->next;
	}
}
