/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:29:36 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/30 21:14:40 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_error(char *str, t_token *token, t_envs *envs, int choice)
{
	if (choice == 1)
	{
		ft_putstr_fd("exit\nbash: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		clear_list(&token);
		clear_list_envs(&envs);
		exit(255);
	}
	else if (choice == 2)
	{
		clear_list(&token);
		clear_list_envs(&envs);
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
}

void	ft_exit(t_token *token, t_envs *envs)
{
	t_token				*head;

	head = token;
	while (token)
	{
		if (!ft_strncmp(token->string, "exit", 4)
			&& ft_strlen(token->string) == ft_strlen("exit"))
		{
			token = token->next;
			exit_cases(token, head, envs);
		}
		token = token->next;
	}
}

