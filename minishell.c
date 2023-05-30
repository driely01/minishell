/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:38:29 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/30 21:42:10 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print(t_token *head)
{
	printf("%d  |%s|\n", head->type, head->string);
}

void	builtin_func(t_token **token, t_envs *envs, int fd)
{
	check_export(token, envs, fd);
	check_unset(token, envs);
	check_cd(token, envs);
	echo_command(*token, fd);
	ft_pwd(*token, envs, fd);
	ft_exit(*token, envs);
}

static void	read_line(t_envs *envs)
{
	char	*input;
	t_token	*list;
	int		fd;
	// t_token	*head;

	fd = 1;
	while (1)
	{
		list = NULL;
		input = readline("\033[1;36mMinishell \033[0m");
		add_history(input);
		input = minishell_tools(&list, envs, input);
		if (input)
		{
			free(input);
			builtin_func(&list, envs, fd);
			// head = list;
			// while (head)
			// {
			// 	print(head);
			// 	head = head->next;
			// }
			clear_list(&list);
		}
	}
	clear_list_envs(&envs);
	clear_history();
}

int	main(int argc, char **argv, char **env)
{
	t_envs	*envs;

	if (argc > 1)
		return (0);
	(void)argv;
	envs = NULL;
	fill_envs(&envs, env);
	read_line(envs);
	return (0);
}
