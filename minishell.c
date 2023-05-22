/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:38:29 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/22 10:15:50 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env) {
	char	*input;
	t_token *list;

	if (argc > 1)
		return (0);
	(void)argv;
	(void)env;
	while (1)
	{
		input = readline("Minishell ");
		add_history(input);
		minishell_tools(&list, input);
	}
	clear_history();
	return (0);
}