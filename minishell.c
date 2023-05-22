/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:38:29 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/22 12:47:44 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env) {
	char	*input;
	t_token *list;

	list = NULL;
	if (argc > 1)
		return (0);
	(void)argv;
	(void)env;
	while (1)
	{
		input = readline("\033[1;36mMinishell \033[0m");
		add_history(input);
		minishell_tools(&list, input);
	}
	clear_history();
	return (0);
}