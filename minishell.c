/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:38:29 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/06 18:18:01 by del-yaag         ###   ########.fr       */
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
		free_split(string);
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

	title = NULL;
	while (1)
	{
		env = updating_env(envs, env);
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
			clear_list(&list);
		}
		free(title);
	}
	clear_list_envs(&envs);
	clear_history();
}

void	if_no_env(t_envs **envs, t_envs **head)
{
	char	*getpwd;

	add_envs(envs, head);
	getpwd = getcwd(NULL, 0);
	(*envs)->name = ft_strdup("PWD");
	(*envs)->value = ft_strdup(getpwd);
	free(getpwd);
	add_envs(envs, head);
	(*envs)->name = ft_strdup("PATH");
	(*envs)->value = ft_strdup("/bin:/usr/bin/");
	add_envs(envs, head);
	(*envs)->name = ft_strdup("_");
	(*envs)->value = ft_strdup("./minishell");
}

void	update_shlvl(t_envs **head)
{
	int	level;

	level = ft_atoi((*head)->value);
	free((*head)->value);
	level++;
	(*head)->value = ft_itoa(level);
}

int	main(int argc, char **argv, char **env)
{
	t_envs	*envs;
	char	**str;

	if (argc > 1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	(void)argv;
	envs = NULL;
	str = fill_envs(&envs, env);
	if (!str)
		str = adding_empty_env(envs);
	read_line(envs, str);
	return (0);
}
