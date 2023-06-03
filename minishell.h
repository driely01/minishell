/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:45:16 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/03 18:53:33 by del-yaag         ###   ########.fr       */
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
# include "../get_next_line/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_type
{
	WORD,
	QUOTES,
	SEPAR,
	HER_EDOC,
	APPEND,
	RED_IN,
	RED_OUT,
	PIPE,
	DELIM
}	t_type;

typedef struct s_token
{
	char			*string;
	int				type;
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
char	*making_minishell_title(t_envs *envs, char *title);
char	**fill_envs(t_envs **envs, char **env);
void	updating_pwd_tool(t_envs *tmp_new, int *i);
void	updating_pwd_tools(t_envs *tmp_new, char *str, int *i);
int	check_cd(t_token **token, t_envs *envs);
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
char	*ft_strjoiness(char *s1, char *s2);
char	*ft_strndup(char *str, int start, int end);
char	*ft_strdup(char *src);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen_2(char **str);
void	free_split(char **split);

// minishell tools
char	*minishell_tools(t_token **token, t_envs *envs, char *input);
char	**updating_env(t_envs *envs, char **env);
char	**aka_fill_env(t_envs *envs, size_t len);

// expand functions
void	change_line_byword(t_exp *expand, char *str, size_t *z);
void	keep_line_byword(t_exp *expand, char *str, char *line);
char	*replace_word(t_exp *expand, char *line, size_t *z);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strenv(t_exp *expand, size_t z, int flag);
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

// syntax error functions
int		syntax_error(t_token *token);

//	signal functions
void    signal_handler(int sig);

// check expand functions
int		is_alpha(char c);
int		ft_isalnum_expand(int c);
int		valid_expand(char c);
int		check_ifseperator_file(t_exp *expand, int z);
void	expand_if_seperator(t_exp *expand, char *str, size_t *i, size_t *j);
void	expand_ifnt_seperator(t_exp *expand, char *str, size_t *i, size_t *j);
void	check_dup_dollars(t_exp *expand, char *input, size_t *i);
void	isquote_env(char *input, size_t *i);

// echo functions
void	echo_command(t_token *token, int fd);
int		skip_n(t_token *token);

// export functions
int		check_cases(t_envs **envs, char *str, int check);
int		execute_export(char *str, t_envs **envs, int fd);
int		export_handle(t_token *head, t_envs **envs, int fd);
int		check_export(t_token **token, t_envs **envs, int fd);
void	change_tmp(t_envs **envs, t_envs **tmp, t_envs **head);
void	change_if_found(t_envs **envs, char *str);
int		change_if_found_not_equal(t_envs **envs, char *str);
int		check_value(t_envs *head, char *name, char *str);
int		change_if_found_plus_equal(t_envs **envs, char *str);
void	execute_env(t_envs **envs, int fd);
void	execute_export_allone(t_envs **envs, int fd);
int		equal_search(char *str, int fd);
t_envs	*ft_lstadd_back(t_envs **lst);
int		execute_equal_tool(char *str);
char	*head_name(char *str, int flag);
char	*head_value(char *str);
void	execute_equal(t_envs **envs, char *str);
void	execute_plus_equal(t_envs **envs, char *str);
void	execute_not_equal(t_envs **envs, char *str);

// exit functions
void	ft_exit(t_token *token, t_envs *envs, int flag);
void	ft_error(char *str, t_token *token, t_envs *envs, int flag);
void	ft_error_two(t_token *token, t_envs *envs, int flag);
int		exit_cases(t_token *token, t_token *head, t_envs *envs, int fd);

// pwd functions
void	ft_pwd(t_token *token, t_envs *envs, int fd);

// cd functions
void	updating_pwd(t_envs *envs);
void	executing_cd_allone(t_envs *envs);
void	executing_last_cd(t_envs *envs);
void	executing_cd(t_envs *envs, char *path);
int		check_cd(t_token **token, t_envs *envs);

// unset functions
int		unset_protection(char *str);
void	remove_env(t_envs **tmp);
void	search_unset_env(char *str, t_envs **envs);
void	unset_env(char *str, t_envs **envs);
int		check_unset(t_token **token, t_envs **envs);

// environment variables functions
void	clear_list_envs(t_envs **list);
char	*ft_strlen_var(char *str, char c);
char	*ft_getenv(t_envs *envs, char *search);
void	add_envs(t_envs **envs, t_envs **head);
char	**add_env(char **env);
char	**fill_envs(t_envs **envs, char **env);

// handlers functions
int		handle_char(t_token **token, char *input, size_t *i);
void	handle_whitespace(char *input, size_t *i);
int		handel_separators(t_token **token, char *input, size_t *i);
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

// execution cmd
void	execute_cmd(t_token **token, t_envs **envs, char **env);
void	builtin_func(t_token **token, t_envs **envs, int outfile, int flag);
pid_t	execute_cmd_tools(t_token **token, t_envs **envs, char **env, char **path, int infile, int outfile, int **pipe_fd);

#endif