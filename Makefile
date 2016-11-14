# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/26 12:41:24 by ofedorov          #+#    #+#              #
#    Updated: 2016/11/05 13:12:06 by ofedorov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra

SRCSFL	+=	test_main.c

SRCSFD	=	srcs
OBJSFD	=	objs
INCLFD	=	includes

SRCS	=	$(addprefix $(SRCSFD)/, $(SRCSFL))
OBJS	=	$(addprefix $(OBJSFD)/, $(SRCSFL:.c=.o))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	ar src $@ $(OBJS)
	ranlib $@

$(OBJSFD):
	mkdir $@

$(OBJSFD)/%.o: $(SRCSFD)/%.c | $(OBJSFD)
	$(CC) $(CFLAGS) -I$(INCLFD) -c $< -o $@

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJSFD)

fclean: clean
	rm -rf $(NAME)

re: fclean all
