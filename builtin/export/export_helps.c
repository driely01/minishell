/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:29:11 by del-yaag          #+#    #+#             */
/*   Updated: 2023/08/06 09:39:58 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_tmp(t_envs **envs, t_envs **tmp, t_envs **head)
{
	if (!(*tmp))
	{
		if ((*head)->next)
			(*envs) = (*head)->next;
		free((*head)->name);
		free((*head)->value);
		free((*head));
	}
	else
	{
		(*tmp)->next = (*head)->next;
		free((*head)->name);
		free((*head)->value);
		free((*head));
		(*head) = (*tmp);
	}
}

void	change_if_found(t_envs **envs, char *str)
{
	t_envs	*head;
	t_envs	*tmp;
	char	*name;

	name = head_name(str, 0);
	head = *envs;
	tmp = NULL;
	while (head)
	{
		if (ft_strlen(head->name) == ft_strlen(name)
			&& !strncmp(head->name, str, ft_strlen(name)))
			change_tmp(envs, &tmp, &head);
		tmp = head;
		head = head->next;
	}
	free(name);
}

int	change_if_found_not_equal(t_envs **envs, char *str)
{
	t_envs	*head;
	char	*name;

	head = *envs;
	name = head_name(str, 0);
	while (head)
	{
		if (ft_strlen(head->name) == ft_strlen(name)
			&& !strncmp(head->name, str, ft_strlen(name)))
			return (free(name), 1);
		head = head->next;
	}
	free(name);
	return (0);
}

int	check_value(t_envs *head, char *name, char *str)
{
	char	*value;

	value = head_value(str);
	if (!value)
		return (free(name), 1);
	else if (!head->value[0])
	{
		free(head->value);
		head->value = ft_strdup(value);
	}
	else
		head->value = ft_strjoin(head->value, value);
	return (free(name), free(value), 1);
}

int	change_if_found_plus_equal(t_envs **envs, char *str)
{
	t_envs	*head;
	char	*name;

	head = *envs;
	name = head_name(str, 1);
	while (head)
	{
		if (ft_strlen(head->name) == ft_strlen(name)
			&& !strncmp(head->name, str, ft_strlen(name)))
		{
			if (check_value(head, name, str) == 1)
				return (1);
		}
		head = head->next;
	}
	return (free(name), 0);
}
