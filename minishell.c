/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:38:29 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/27 21:24:34 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_line(t_envs *envs)
{
	char	*input;
	t_token	*list;
	t_token	*head;

	while (1)
	{
		list = NULL;
		input = readline("\033[1;36mMinishell \033[0m");
		add_history(input);
		input = minishell_tools(&list, envs, input);
		free(input);
		head = list;
		while (head)
		{
			printf("%s\n", head->string);
			head = head->next;
		}
		clear_list(&list);
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
	fill_envs(&envs, env);
	read_line(envs);
	return (0);
}
