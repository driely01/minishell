/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:20:28 by del-yaag          #+#    #+#             */
/*   Updated: 2023/08/06 09:40:07 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	if (!found)
		return (NULL);
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
		if (!(*envs))
		{
			clear_list_envs(envs);
			return ;
		}
		(*envs)->next = NULL;
		*head = *envs;
	}
	else
	{
		(*envs)->next = malloc(sizeof(t_envs));
		if (!(*envs))
		{
			clear_list_envs(envs);
			return ;
		}
		*envs = (*envs)->next;
		(*envs)->next = NULL;
	}
}

char	**add_env(char **env)
{
	char	**str;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen_2(env);
	if (len == 0)
		return (NULL);
	str = malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	while (env[i])
	{
		str[i] = ft_strdup(env[i]);
		i++;
	}
	str[i] = NULL;
	return (str);
}
