/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:38:29 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/05 13:27:31 by del-yaag         ###   ########.fr       */
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
			// 	printf("type %d here_exp %d => %s\n", head->type, head->here_exp, head->string);
			// 	head = head->next;
			// }
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
	add_envs(envs, head);
	(*envs)->name = ft_strdup("SHLVL");
	(*envs)->value = ft_strdup("1");
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

void	if_no_shlvl(t_envs **head)
{
	t_envs	*new;
	
	while ((*head) && (*head)->next)
	{
		if (ft_strlen((*head)->name) == 5 && !ft_strncmp((*head)->name, "SHLVL", 5))
		{
			update_shlvl(head);
			break ;
		}
		(*head) = (*head)->next;
	}
	if ((*head) && !(*head)->next && !(ft_strlen((*head)->name) == 5
		&& !ft_strncmp((*head)->name, "SHLVL", 5)))
	{
		new = malloc(sizeof(t_envs));
		new->name = ft_strdup("SHLVL");
		new->value = ft_strdup("1");
		(*head)->next = new;
		new->next = NULL;
	}
}

char	**fill_envs(t_envs **envs, char **env)
{
	t_envs	*head;
	char	**str;
	size_t	i;

	i = 0;
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
