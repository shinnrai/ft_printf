# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/26 12:41:24 by ofedorov          #+#    #+#              #
#    Updated: 2016/12/05 12:15:48 by ofedorov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra

SRCSFL	+=	format_a.c format_c.c format_d.c format_e.c  \
			format_i.c format_o.c format_p.c format_another.c \
			format_s.c format_u.c format_x.c format_f.c
SRCSFL	+=	ft_printf.c ft_printf_format.c ft_printf_get_value.c \
			ft_printf_read_format.c ft_printf_write.c ft_printf_read_utils.c \
			ft_printf_checking_format.c
SRCSFL	+=	ft_atoi.c ft_isdigit.c ft_power.c ft_double_utils.c ft_wcharlen.c \
			ft_putchar_fd.c ft_putnbr_fd.c ft_putnstr_fd.c ft_putnwstr_fd.c \
			ft_putstr_fd.c ft_putwchar_fd.c ft_putwstr_fd.c \
			ft_strlen.c ft_wstrlen.c 

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
