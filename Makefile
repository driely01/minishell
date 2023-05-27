# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 14:31:22 by del-yaag          #+#    #+#              #
#    Updated: 2023/05/27 20:53:45 by del-yaag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = minishell.c \
	  handle_whitespace.c \
	  ft_strndup.c \
	  ft_isalnum.c \
	  ft_split.c \
	  ft_strtrim.c \
	  handle_char.c \
	  quotes_tools.c \
	  list_funcs.c \
	  minishell_tools.c \
	  split_utils.c \
	  handle_separators.c \
	  handle_qoutes.c \
	  ft_strjoin.c \
	  quotes_tools_p2.c \
	  expand.c \
	  expand_functions.c \
	  expand_checker.c \
	  expand_func_tools.c \
	  expand_tools.c \
	  env_variables.c

OBG = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -f

NAME = minishell

all: $(NAME)

$(NAME): $(OBG)
	$(CC) $(CFLAGS) -lreadline $(OBG) -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} ${OBG}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re  