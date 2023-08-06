# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 14:31:22 by del-yaag          #+#    #+#              #
#    Updated: 2023/08/06 09:42:45 by del-yaag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = minishell.c \
	  builtin/cd/cd.c \
	  builtin/cd/cd_utils.c \
	  builtin/cd/cd_helpers.c \
	  builtin/echo/echo_command.c \
	  execution/execution.c \
	  execution/execution_utils.c \
	  execution/execution_utils1.c \
	  execution/execution_utils2.c \
	  execution/execution_utils3.c \
	  execution/execution_utils4.c \
	  execution/execution_utils5.c \
	  execution/signals.c \
	  builtin/exit/exit_function.c \
	  builtin/exit/exit_main.c \
	  expand/expand.c \
	  expand/expand_functions.c \
	  expand/expand_checker.c \
	  expand/expand_func_tools.c \
	  expand/expand_tools.c \
	  builtin/export/env_variables.c \
	  builtin/export/export.c \
	  builtin/export/export_tools.c \
	  builtin/export/export_helps.c \
	  builtin/export/export_funcs.c \
	  builtin/export/export_helps1.c \
	  parcing/handle_whitespace.c \
	  parcing/handle_char.c \
	  parcing/handle_separators.c \
	  parcing/handle_qoutes.c \
	  parcing/quotes_tools.c \
	  parcing/quotes_tools_p2.c \
	  parcing/syntax_error.c \
	  builtin/pwd/pwd.c \
	  builtin/unset/unset_help.c \
	  builtin/unset/unset.c \
	  utils/ft_strndup.c \
	  utils/ft_isalnum.c \
	  utils/ft_split.c \
	  utils/ft_strtrim.c \
	  utils/ft_strjoin.c \
	  utils/ft_atoi_itoa.c \
	  utils/ft_itoa.c \
	  utils/list_funcs.c \
	  utils/minishell_tools.c \
	  utils/minishell_utils.c \
	  utils/minishell_utils1.c \
	  utils/split_utils.c 
	  
OBG = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I/Users/del-yaag/homebrew/opt/readline/include #-fsanitize=address -g
CC = cc
RM = rm -f

NAME = minishell

all: $(NAME)

$(NAME): $(OBG)
	$(CC) $(CFLAGS) -lreadline -L/Users/del-yaag/homebrew/opt/readline/lib $(OBG) -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	${RM} ${OBG}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
