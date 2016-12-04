cmake_minimum_required(VERSION 3.6)
project(my_printf)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ") #-Wall -Wextra -Werror")
include_directories(includes)

set(SOURCE_FILES  includes/libftprintf.h  srcs/ft_write.c
        srcs/format_d.c  srcs/format_p.c  srcs/format_a.c  srcs/format_c.c
        srcs/format_e.c  srcs/format_i.c  srcs/format_o.c  srcs/format_percent.c
        srcs/format_s.c  srcs/format_u.c  srcs/format_x.c
        srcs/ft_putnwstr_fd.c srcs/ft_putwchar_fd.c srcs/ft_putnstr_fd.c srcs/ft_putchar_fd.c
        srcs/ft_strlen.c srcs/ft_printf_format.c srcs/ft_printf.c
        srcs/ft_printf_read_format.c srcs/ft_atoi.c srcs/ft_isdigit.c
        srcs/ft_putstr_fd.c srcs/ft_putwstr_fd.c srcs/ft_wstrlen.c srcs/ft_printf_get_value.c
        srcs_old/test_main.c)

add_executable(my_printf ${SOURCE_FILES})