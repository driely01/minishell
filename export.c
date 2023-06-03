/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:58:40 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/03 13:52:28 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cases(t_envs **envs, char *str, int check)
{
	if (check == 2)
		return (2);
	else if (check == 3)
	{
		if (change_if_found_plus_equal(envs, str) == 0)
			execute_plus_equal(envs, str);
	}
	else
	{
		change_if_found(envs, str);
		execute_equal(envs, str);
	}
	return (0);
}

int	execute_export(char *str, t_envs **envs, int fd)
{
	int	check;

	if (!valid_expand(str[0]))
	{
		ft_putstr_fd("export: not an identifier: ", fd);
		write(fd, &str[0], 1);
		write(fd, "\n", 1);
		return (2);
	}
	check = equal_search(str, fd);
	if (check)
	{
		if (check_cases(envs, str, check) == 2)
			return (2);
	}
	else if (!change_if_found_not_equal(envs, str))
		execute_not_equal(envs, str);
	return (0);
}

int	export_handle(t_token *head, t_envs **envs, int fd)
{
	head = head->next;
	if (head->string[0] == '-')
	{
		ft_putstr_fd("Minishell: export: ", fd);
		ft_putstr_fd(head->string, fd);
		ft_putstr_fd(": invalid option\n", fd);
		return (0);
	}
	while (head && head->type < 2)
	{
		if (!ft_strncmp(head->string, "=", ft_strlen("=")))
		{
			ft_putstr_fd("export: not an identifier: ", fd);
			ft_putstr_fd(head->string, fd);
			write(fd, "\n", 1);
			return (0);
		}
		execute_export(head->string, envs, fd);
		head = head->next;
	}
	return (1);
}

int	check_export(t_token **token, t_envs **envs, int fd)
{
	t_token	*head;

	head = *token;
	if (head && ft_strlen(head->string) == ft_strlen("env")
		&& !ft_strncmp(head->string, "env", ft_strlen("env")))
	{
		head = head->next;
		if (head && head->type < 2)
			ft_putstr_fd("env: illegal option or arguments\n", fd);
		else
			execute_env(envs, fd);
	}
	else if (head && ft_strlen(head->string) == ft_strlen("export")
		&& !ft_strncmp(head->string, "export", ft_strlen("export")))
	{
		if (!head->next)
			execute_export_allone(envs, fd);
		else
		{
			if (!export_handle(head, envs, fd))
				return (0);
		}
	}
	return (0);
}
