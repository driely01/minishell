/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:16:54 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/07 11:51:24 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_envs(t_envs **envs, char **env)
{
	t_envs	*head;
	char	**str;
	size_t	i;

	i = 0;
	head = NULL;
	if (!*env)
		if_no_env(envs, &head);
	else
	{
		while (env[i])
		{
			add_envs(envs, &head);
			(*envs)->name = ft_strlen_var(env[i], '=');
			(*envs)->value = ft_strdup(getenv((*envs)->name));
			i++;
		}
	}
	*envs = head;
	if_no_shlvl(&head);
	str = add_env(env);
	return (str);
}

size_t	size_of_envs(t_envs *envs)
{
	t_envs	*head;
	size_t	count;

	head = envs;
	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

char	**adding_empty_env(t_envs *envs)
{
	t_envs	*head;
	char	**str;
	char	*save;
	size_t	len;
	size_t	i;

	head = envs;
	len = size_of_envs(envs);
	str = malloc(sizeof(char *) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (head->next && i < len)
	{
		save = ft_strjoiness(envs->name, "=");
		str[i] = ft_strjoiness(save, envs->value);
		free(save);
		i++;
		head = head->next;
	}
	str[i] = NULL;
	return (str);
}

void	shlvl_help(t_envs **head)
{
	t_envs	*new;

	if ((*head) && !(*head)->next)
	{	
		if (ft_strlen((*head)->name) == 5
			&& !ft_strncmp((*head)->name, "SHLVL", 5))
			update_shlvl(head);
		else
		{	
			new = malloc(sizeof(t_envs));
			if (!new)
			{
				clear_list_envs(head);
				return ;
			}
			new->name = ft_strdup("SHLVL");
			new->value = ft_strdup("1");
			(*head)->next = new;
			new->next = NULL;
		}
	}
}

void	if_no_shlvl(t_envs **head)
{
	while ((*head) && (*head)->next)
	{
		if (ft_strlen((*head)->name) == 5
			&& !ft_strncmp((*head)->name, "SHLVL", 5))
		{
			update_shlvl(head);
			break ;
		}
		(*head) = (*head)->next;
	}
	shlvl_help(head);
}
