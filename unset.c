/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:42:44 by markik            #+#    #+#             */
/*   Updated: 2023/06/06 18:38:34 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_protection(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (!ft_isalnum_expand(str[i]) && str[i] != '_')
		{
			g_status = 256;
			ft_putstr_fd("unset: not an identifier: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	remove_env(t_envs **tmp)
{
	free((*tmp)->name);
	free((*tmp)->value);
	free((*tmp));
}

void	unset_error(t_token *head, int choice)
{
	g_status = 256;
	if (choice == 1)
	{
		ft_putstr_fd("Minishell: unset: ", 2);
		ft_putstr_fd(head->string, 2);
		ft_putstr_fd(": invalid option\n", 2);
	}
	else if (choice == 2)
	{
		ft_putstr_fd("unset: not an identifier: ", 2);
		ft_putstr_fd(head->string, 2);
		ft_putstr_fd("\n", 2);
	}
}

int	check_unset(t_token **token, t_envs **envs)
{
	t_token	*head;

	head = *token;
	if (head && ft_strlen(head->string) == ft_strlen("unset") \
			&& !ft_strncmp(head->string, "unset", ft_strlen("unset")))
	{
		if (!head->next)
			return (0);
		else
		{
			head = head->next;
			if (head->string[0] == '-')
				return (unset_error(head, 1), 0);
			while (head && head->type < 2)
			{
				if (!ft_strncmp(head->string, "=", ft_strlen("=")))
					return (unset_error(head, 2), 0);
				unset_env(head->string, envs);
				head = head->next;
			}
		}
	}
	return (0);
}
