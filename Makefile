# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: markik <markik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 14:31:22 by del-yaag          #+#    #+#              #
#    Updated: 2023/05/22 14:23:14 by markik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = minishell.c handel_specialchar.c \
	  handle_whitespace.c ft_strndup.c \
	  ft_isalnum.c ft_split.c ft_strjoin.c \
	  ft_strtrim.c handlers.c handle_char.c \
	  list_funcs.c minishell_tools.c split_utils.c \
	  handel_separators.c handel_qoutes.c

OBG = $(SRC:.c=.o)

CFLAGS = -fsanitize=address -g
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