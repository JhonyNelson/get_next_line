# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhcosta- <jhcosta-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/04 16:49:10 by jhcosta-          #+#    #+#              #
#    Updated: 2026/08/04 16:49:12 by jhcosta-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libgnl.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs

BUFFER_SIZE	?= 42

SRCS		= get_next_line.c get_next_line_utils.c
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
