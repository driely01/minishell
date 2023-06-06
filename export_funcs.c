/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:27:49 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/05 18:31:38 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*head_name(char *str, int flag)
{
	char	*string;
	int		start;
	int		end;

	start = 0;
	if (flag == 1)
		end = execute_equal_tool(str) - 2;
	else
		end = execute_equal_tool(str) - 1;
	if (end == -1)
	{
		string = ft_strdup(str);
		return (string);
	}
	string = ft_strndup(str, start, end);
	return (string);
}

char	*head_value(char *str)
{
	char	*string;
	int		start;
	int		end;

	start = execute_equal_tool(str) + 1;
	end = ft_strlen(str) - 1;
	if (start > end)
	{
		string = ft_strdup("\31");
		return (string);
	}
	string = ft_strndup(str, start, end);
	return (string);
}

void	execute_equal(t_envs **envs, char *str)
{
	t_envs	*head;

	head = ft_lstadd_back(envs);
	head->name = head_name(str, 0);
	head->value = head_value(str);
}

void	execute_plus_equal(t_envs **envs, char *str)
{
	t_envs	*head;

	head = ft_lstadd_back(envs);
	head->name = head_name(str, 1);
	head->value = head_value(str);
}

void	execute_not_equal(t_envs **envs, char *str)
{
	t_envs	*head;

	head = ft_lstadd_back(envs);
	head->name = head_name(str, 0);
	head->value = ft_strdup("\0");
}
