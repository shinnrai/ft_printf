cmake_minimum_required(VERSION 3.6)
project(my_printf)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
include_directories(includes)

set(SOURCE_FILES  srcs/test_main.c includes/libftprintf.h  srcs/ft_write.c  srcs/format_s.c
        srcs/ft_putnwstr_fd.c srcs/ft_putwchar_fd.c srcs/ft_putnstr_fd.c srcs/ft_putchar_fd.c
        srcs/ft_strdup.c srcs/ft_strlen.c)

add_executable(my_printf ${SOURCE_FILES})