/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:45:16 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/24 17:29:39 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_token
{
	char 			*string;
	struct s_token	*next;
	// struct s_var	g_var;
}	t_token;

// typedef struct s_var
// {
// 	int flag;
// }	t_var;

// list functions
void	add_node(t_token **token);
void	clear_list(t_token **list);

// check functions
size_t	ft_strlen(const char *str);
int		ft_isalnum(int c);
int		ft_isspecialchar(int c);
int		is_qoute(int c);
int		ft_isseparators(int c);
int	 	ft_isspace(int c);

// string functions
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strndup(char *str, int start, int end);
void	minishell_tools(t_token **list, char **env, char *input);
int		handle_char(t_token **token, char *input, size_t *i);
int     double_qoutes(t_token **token, char *input, size_t *i);
int    	single_qoutes(t_token **token, char *input, size_t *i);
char	*ft_strdup(char *src);
char	*ft_strcpy(char *dest, char *src);
char    *expand_input(char **env, char *input);

// handlers functions
void	handle_whitespace(char *input, size_t *i);
void    handel_specialchar(t_token **token, char *input, size_t *i);
void    handel_separators(t_token **token, char *input, size_t *i);


// split functions
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t number, size_t size);

#endif