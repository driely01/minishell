/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:38:29 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/03 19:51:38 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*making_minishell_title(t_envs *envs, char *title)
{
	char	**string;
	char	*str;
	char	*save;
	int		i;

	i = 0;
	str = ft_getenv(envs, "PWD");
	if (!str)
		str = "Minishell/Minishell";
	string = ft_split(str, '/');
	while (string[i] && string[i + 1])
		i++;
	if (i == 0)
	{
		title = ft_strdup("\033[1;36m/ \033[0m");
		return (title);
	}
	title = ft_strdup(string[i]);
	free_split(string);
	save = ft_strjoiness("\033[1;36m", title);
	free(title);
	title = ft_strjoin(save, " \033[0m");
	return (title);
}

static void	read_line(t_envs *envs, char **env)
{
	char	*input;
	char	*title;
	t_token	*list;
	// t_token	*head;

	title = NULL;
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		list = NULL;
		title = making_minishell_title(envs, title);
		input = readline(title);
		add_history(input);
		input = minishell_tools(&list, envs, input);
		if (input)
		{
			free(input);
			execute_cmd(&list, &envs, env);
			env = updating_env(envs, env);
			// head = list;
			// while (head)
			// {
			// 	printf("%d  %s\n", head->type, head->string);
			// 	head = head->next;
			// }
			clear_list(&list);
		}
		free(title);
	}
	clear_list_envs(&envs);
	clear_history();
}

char	**fill_envs(t_envs **envs, char **env)
{
	t_envs	*head;
	char	**str;
	size_t	i;

	i = 0;
	if (!*env)
		return (NULL);
	while (env[i])
	{
		add_envs(envs, &head);
		(*envs)->name = ft_strlen_var(env[i], '=');
		(*envs)->value = ft_strdup(getenv((*envs)->name));
		i++;
	}
	*envs = head;
	str = add_env(env);
	return (str);
}

int	main(int argc, char **argv, char **env)
{
	t_envs	*envs;
	char	**str;

	if (argc > 1)
		return (0);
	(void)argv;
	envs = NULL;
	str = fill_envs(&envs, env);
	read_line(envs, str);
	return (0);
}
