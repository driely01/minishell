/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:42:44 by markik            #+#    #+#             */
/*   Updated: 2023/05/30 18:58:36 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_protection(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (!ft_isalnum_expand(str[i]) && str[i] != '_')
		{
			printf("unset: not an identifier: %s\n", str);
			return (1);
		}
		i++;
	}
	return (0);
}

void    remove_env(t_envs *tmp)
{
    free(tmp->name);
    free(tmp->value);
    free(tmp);
}

void    search_unset_env(char *str, t_envs *envs)
{
    t_envs  *head;
    t_envs  *tmp;

    head = envs;
    tmp = NULL;
    while(head)
    {
        if (head && ft_strlen(head->name) == ft_strlen(str)
		    && !ft_strncmp(head->name, str, ft_strlen(str)))
            {
                if(!tmp)
                    envs = envs->next;
                else
                    tmp->next = head->next;
                remove_env(head);
                break ;
            }
        tmp = head;
        head = head->next;
    }
}

void    unset_env(char *str, t_envs *envs)
{
    if (!valid_expand(str[0]))
	{
		printf("unset: not an identifier: %s\n", str);
		return ;
	}
    if (!unset_protection(str))
        search_unset_env(str, envs);
}

int	check_unset(t_token **token, t_envs *envs)
{
    t_token *head;
    
    head = *token;
    if (head && ft_strlen(head->string) == ft_strlen("unset")
		&& !ft_strncmp(head->string, "unset", ft_strlen("unset")))
        {
            if (!head->next)
			    return 0;
            else
		    {
                head = head->next;
                if (head->string[0] == '-')
		            return (printf("Minishell: unset: %s: invalid option\n", head->string), 0);
                while (head && head->type < 2)
	            {
		            if (!ft_strncmp(head->string, "=", ft_strlen("=")))
			            return (printf("unset: not an identifier: %s\n", head->string), 0);
		            unset_env(head->string, envs);
		            head = head->next;
	            }
		    }
        }
    return 0;
}