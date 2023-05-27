/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:20:28 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/27 20:55:04 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_list_envs(t_envs **list)
{
	if (!(*list))
		return ;
	if ((*list)->next)
		clear_list_envs(&(*list)->next);
	free((*list)->name);
	free((*list)->value);
	free(*list);
}

char	*ft_strlen_var(char *str, char c)
{
	size_t	i;
	size_t	j;
	char	*found;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] != c)
		i++;
	found = malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		found[j] = str[j];
		j++;
	}
	found[j] = '\0';
	return (found);
}

char	*ft_getenv(t_envs *envs, char *search)
{
	size_t	len_env;
	size_t	len_search;

	len_search = ft_strlen(search);
	while (envs)
	{
		len_env = ft_strlen(envs->name);
		if (!ft_strncmp(envs->name, search, len_search)
			&& len_env == len_search)
			return (envs->value);
		envs = envs->next;
	}
	return (NULL);
}

void	add_envs(t_envs **envs, t_envs **head)
{
	if (!(*envs))
	{
		*envs = malloc(sizeof(t_envs));
		*head = *envs;
	}
	else
	{
		(*envs)->next = malloc(sizeof(t_envs));
		*envs = (*envs)->next;
	}
	if (!(*envs))
		clear_list_envs(envs);
	(*envs)->next = NULL;
}

void	fill_envs(t_envs **envs, char **env)
{
	size_t	i;
	t_envs	*head;

	i = 0;
	while (env[i])
	{
		add_envs(envs, &head);
		(*envs)->name = ft_strlen_var(env[i], '=');
		(*envs)->value = ft_strdup(getenv((*envs)->name));
		i++;
	}
	*envs = head;
}
