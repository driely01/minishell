/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:45:16 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/25 16:24:54 by del-yaag         ###   ########.fr       */
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
	struct s_envs	*envs;
	struct s_token	*next;
}	t_token;

typedef struct s_envs
{
	char			*name;
	char			*value;
	struct s_envs	*next;
}	t_envs;

// list tokens functions
void	add_node(t_token **token);
void	clear_list(t_token **list);

// list envs functions
void	fill_envs(t_envs **envs, char **env);
void	clear_list_envs(t_envs **list);

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
void	minishell_tools(t_token **token, t_envs *envs, char *input);
int		handle_char(t_token **token, char *input, size_t *i);
int     double_qoutes(t_token **token, char *input, size_t *i);
int    	single_qoutes(t_token **token, char *input, size_t *i);
char	*ft_strdup(char *src);
char	*ft_strcpy(char *dest, char *src);
char    *expand_input(t_envs *env, char *input);
char	*ft_getenv(t_envs *envs, char *search);
char	*ft_strlen_var(char *str, char c);
int		ft_strncmp(char *s1, char *s2, size_t n);


// handlers functions
void	handle_whitespace(char *input, size_t *i);
void    handel_specialchar(t_token **token, char *input, size_t *i);
void    handel_separators(t_token **token, char *input, size_t *i);


// split functions
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t number, size_t size);

#endif