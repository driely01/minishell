/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:27:06 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/30 21:41:15 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_env(t_envs *envs, int fd)
{
	t_envs	*head;

	head = envs;
	while (head)
	{
		if (head->value && head->value[0])
		{
			ft_putstr_fd(head->name, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(head->value, fd);
			ft_putstr_fd("\n", fd);
		}
		head = head->next;
	}
}

void	execute_export_allone(t_envs *envs, int fd)
{
	t_envs	*head;

	head = envs;
	while (head)
	{
		if (!head->value)
		{	
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(head->name, fd);
			ft_putstr_fd("=\"\"\n", fd);
		}
		else if (!head->value[0])
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(head->name, fd);
			ft_putstr_fd("\n", fd);
		}
		else
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(head->name, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(head->value, fd);
			ft_putstr_fd("\n", fd);
		}
		head = head->next;
	}
}

int	equal_search(char *str, int fd)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (3);
		else if (str[i] == '=')
			return (1);
		else if (!ft_isalnum_expand(str[i]) && str[i] != '_')
		{
			ft_putstr_fd("export: not an identifier: ", fd);
			write(fd, &str[i], 1);
			write(fd, "\n", 1);
			return (2);
		}
		i++;
	}
	return (0);
}

t_envs	*ft_lstadd_back(t_envs *lst)
{
	t_envs	*tmp;
	t_envs	*new;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp -> next != NULL)
	tmp = tmp -> next;
	new = malloc(sizeof(t_envs));
	tmp -> next = new;
	new->next = NULL;
	return (tmp->next);
}

int	execute_equal_tool(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}
