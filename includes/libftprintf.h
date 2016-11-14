/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 15:18:00 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/01 15:18:01 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H //TODO change names of files to ft_printf_*.c

# include <unistd.h>
# include <stdlib.h>
# include <locale.h>
# include <wchar.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>

typedef char			t_case;
# define CAPITAL		'A'
# define SMALL			'a'

typedef unsigned		t_length_mod;
# define LEN_H			0
# define LEN_HH			1
# define LEN_NONE		2
# define LEN_L			3
# define LEN_LL			4
# define LEN_J			5
# define LEN_Z			6
# define LEN_T			7
# define LEN_L_CAP		8

typedef struct			s_flags
{
	//TODO add flags
	int 				fd;
	bool				capital;
	bool				left_justified;
	bool				sign;
	bool				space;
	bool				alternative;
	bool				zero;
	int 				field_width;
	int					precision;
	bool				expl_precision;
	bool				just_count;
	t_length_mod		length_mod;
	char				format;
	int					chars_wr;
	char				*error;
}						t_flags;

# define ABS(x)			(x) < 0 ? -(x) : (x)

int						ft_putchar_fd(char c, int fd);
int						ft_putwchar_fd(wchar_t c, int fd);
int						ft_putstr_fd(char const *s, int fd);
int						ft_putnstr_fd(char const *str, int fd, int length);
int						ft_putwstr_fd(wchar_t const *str, int fd);
int						ft_putnwstr_fd(wchar_t const *str, int fd, int length);
size_t					ft_strlen(const char *s);
char					*ft_strdup(const char *s1);
int						ft_isdigit(int c);
int						ft_atoi(const char *str);
void					ft_putnbr_fd(int n, int fd); //TODO make length return

size_t					ft_strncpy_count(char *dst, const char *src,
										 size_t len);
void					ft_write(const char *to_write, int size,
								 t_flags *flags);
t_flags					*new_flags(int fd, char format, bool just_count);
t_flags					*flags_count(t_flags *flags);
t_flags					*read_format(int fd, char **str, va_list ap);

int						format_a(t_flags *flags, va_list ap);
int						format_c(int c, t_flags *flags);
int						format_C(wint_t c, t_flags *flags);
int						format_d(ptrdiff_t nbr, t_flags *flags);
int 					format_e(double nbr, t_flags *flags);
int						format_s(char *str, t_flags *flags);
int						format_S(wchar_t *str, t_flags *flags);

#endif
