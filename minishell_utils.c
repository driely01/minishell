/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:10:07 by markik            #+#    #+#             */
/*   Updated: 2023/06/03 18:47:44 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen_2(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

void	builtin_func(t_token **token, t_envs **envs, int outfile, int flag)
{
	check_export(token, envs, outfile);
	check_cd(token, *envs);
	echo_command(*token, outfile);
	ft_pwd(*token, *envs, outfile);
	check_unset(token, envs);
	ft_exit(*token, *envs, flag);
}

size_t	ft_lst_size(t_envs *envs)
{
	size_t	count;
	t_envs	*head;

	if (!envs)
		return (0);
	head = envs;
	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

char	**aka_fill_env(t_envs *envs, size_t len)
{
	t_envs	*head;
	char	**str;
	char	*save;
	size_t	i;

	head = envs;
	i = 0;
	str = malloc(sizeof(char *) * (len + 1));
	while (head)
	{
		save = ft_strjoiness(head->name, "=");
		str[i] = ft_strjoin(save, head->value);
		i++;
		head = head->next;
	}
	str[i] = NULL;
	return (str);
}

char	**updating_env(t_envs *envs, char **env)
{
	size_t	len;

	len = ft_lst_size(envs);
	if (len == 0)
	{
		if (env)
			free(env);
		env = NULL;
		return (env);
	}
	if (env)
		free_split(env);
	if (env)
		env = aka_fill_env(envs, len);
	return (env);
}
