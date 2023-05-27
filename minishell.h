/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:45:16 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/27 21:36:54 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token
{
	char			*string;
	struct s_token	*next;
}	t_token;

typedef struct s_envs
{
	char			*name;
	char			*value;
	struct s_envs	*next;
}	t_envs;

typedef struct s_var
{
	char	*str;
	int		start;
	int		end;
	int		count;
	int		*flag;
}	t_var;

typedef struct s_expand
{
	size_t	cli_start;
	size_t	cli_end;
	size_t	replace_word_i;
	size_t	replace_word_j;
	size_t	replace_word_a;
	size_t	replace_word_len;
	size_t	lxk;
	size_t	x;
	size_t	count;
	char	*tab;
	char	*test;
	char	*str;
	int		flag;
	int		start;
	int		end;
}	t_exp;

// list functions
void	add_node(t_token **token);
void	clear_list(t_token **list);

// check functions
size_t	ft_strlen(const char *str);
int		ft_isalnum(int c);
int		ft_isspecialchar(int c);
int		is_qoute(int c);
int		ft_isseparators(int c);
int		ft_isspace(int c);
int		ft_isalnum_expand(int c);
int		check_vlag(char *tab, int i);
int		here_doc(char *str);

// string functions
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strndup(char *str, int start, int end);
char	*ft_strdup(char *src);

// minishell tools
char	*minishell_tools(t_token **token, t_envs *envs, char *input);

// expand functions
void	change_line_byword(t_exp *expand, char *str, size_t *z);
void	keep_line_byword(t_exp *expand, char *str, char *line);
char	*replace_word(t_exp *expand, char *line, size_t *z);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strenv(t_exp *expand, size_t z);
char	*handling_complecated_case(t_exp *expand);
void	expand_compare(t_exp *expand, char *input, size_t *i);
void	search_env(t_exp *expand, t_envs *envs, char *input, size_t *i);
char	*change_line_input(t_exp *expand, t_envs *envs, char *input, size_t *i);
int		check_flag(char *tab, size_t *i, size_t start);
void	expand_env_single_quote(t_exp *expand, char *input, size_t *i);
char	*expand_env_double_quote(t_exp *expand, t_envs *envs,
			char *input, size_t *i);
char	*expand_env_char(t_exp *expand, t_envs *envs, char *input, size_t *i);
void	expand_env_seperators(char *input, size_t *i);
char	*expand_env(t_exp *expand, t_envs *envs, char *input);
char	*expand_input(t_envs *envs, char *input);
char	*remove_character(char *line, int c);

// check expand functions
int		is_alpha(char c);
int		ft_isalnum_expand(int c);
int		valid_expand(char c);
int		check_ifseperator_file(t_exp *expand, int z);
void	expand_if_seperator(t_exp *expand, char *str, size_t *i, size_t *j);
void	expand_ifnt_seperator(t_exp *expand, char *str, size_t *i, size_t *j);
void	check_dup_dollars(t_exp *expand, char *input, size_t *i);

// environment variables functions
void	clear_list_envs(t_envs **list);
char	*ft_strlen_var(char *str, char c);
char	*ft_getenv(t_envs *envs, char *search);
void	add_envs(t_envs **envs, t_envs **head);
void	fill_envs(t_envs **envs, char **env);

// handlers functions
int		handle_char(t_token **token, char *input, size_t *i);
void	handle_whitespace(char *input, size_t *i);
void	handel_separators(t_token **token, char *input, size_t *i);
int		double_qoutes(t_token **token, char *input, size_t *i);
int		single_qoutes(t_token **token, char *input, size_t *i);

// qoutes tools
int		skip_qoutes(char *input, t_var *var, size_t *i);
int		skip_doubleqoutes(char *input, t_var *var, size_t *i);
int		flag_two(t_token **token, t_var *var, char *input, size_t *i);
int		flagd_two(t_token **token, t_var *var, char *input, size_t *i);
int		set_check_flag(t_token **token, t_var *var, char *input, size_t *i);
int		set_check_dflag(t_token **token, t_var *var, char *input, size_t *i);
int		is_char(t_token **token, t_var *var, char *input, size_t *i);
int		qoutes(t_token **token, t_var *var);
void	fill_and_join(t_token **token, t_var *var, char *input, int choice);

//	herdoc function
int		here_doc(char *str);

// split functions
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t number, size_t size);

#endif