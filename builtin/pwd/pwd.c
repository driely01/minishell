/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:57:59 by del-yaag          #+#    #+#             */
/*   Updated: 2023/08/06 09:39:38 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd_cases(t_token **token, char *str, int fd)
{
	(*token) = (*token)->next;
	if ((*token) && (*token)->string[0] == '-')
	{
		g_status = 256;
		ft_putstr_fd("Minishell: pwd: ", fd);
		ft_putstr_fd((*token)->string, fd);
		ft_putstr_fd(": invalid option\n", fd);
	}
	else
	{
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
		while ((*token) && (*token)->type < 2)
			(*token) = (*token)->next;
		return (0);
	}
	return (1);
}

void	ft_pwd(t_token *token, t_envs *envs, int fd)
{
	char	*str;

	(void)envs;
	str = getcwd(NULL, 0);
	if (!str)
		return ;
	while (token)
	{
		if (!ft_strncmp(token->string, "pwd", 3)
			&& ft_strlen(token->string) == ft_strlen("pwd"))
		{
			if (!token->next)
			{
				ft_putstr_fd(str, fd);
				ft_putstr_fd("\n", fd);
			}
			else
				if (!pwd_cases(&token, str, fd))
					break ;
		}
		if (token)
			token = token->next;
	}
	free(str);
}
