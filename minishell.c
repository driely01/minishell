/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:38:29 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/22 19:32:46 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env) {
	char	*input;
	t_token *list;
	t_token *head;

	list = NULL;
	if (argc > 1)
		return (0);
	(void)argv;
	(void)env;
	while (1)
	{
		list = NULL;
		input = readline("\033[1;36mMinishell \033[0m");
		add_history(input);
		minishell_tools(&list, input);
		head = list;
		while(head)
		{
			printf("%s\n", head->string);
			head = head->next;
		}
		clear_list(&list);
	}
	clear_history();
	return (0);
}