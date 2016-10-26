# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/26 12:41:24 by ofedorov          #+#    #+#              #
#    Updated: 2016/10/26 12:55:51 by ofedorov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra

SRCSFL	+=	

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
