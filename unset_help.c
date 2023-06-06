/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:24:18 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/06 18:38:12 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_unset_env(char *str, t_envs **envs)
{
	t_envs	*head;
	t_envs	*tmp;

	head = (*envs);
	tmp = NULL;
	while (head)
	{
		if (head && ft_strlen(head->name) == ft_strlen(str) \
				&& !ft_strncmp(head->name, str, ft_strlen(str)))
		{
			if (!tmp)
				(*envs) = (*envs)->next;
			else
				tmp->next = head->next;
			remove_env(&head);
			break ;
		}
		tmp = head;
		head = head->next;
	}
}

void	unset_env(char *str, t_envs **envs)
{
	if (!valid_expand(str[0]))
	{
		g_status = 256;
		ft_putstr_fd("unset: not an identifier: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	if (!unset_protection(str))
		search_unset_env(str, envs);
}
