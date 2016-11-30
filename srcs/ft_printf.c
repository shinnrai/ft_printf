/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 10:08:21 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/22 10:08:22 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

static void	write_count(int fd, const char *str, int size, int *ch)
{
	int ret = write(fd, str, size);
	*ch = (ret == size) ? *ch + ret : -1;
}

void	display_error(const char *str) //TODO move to libft
{
	ft_putstr_fd("\nERROR: ", 2);
	ft_putstr_fd(str, 2);
	exit(1);
}

static void	setup_formats(void)
{
	g_formats['a'] = format_a;
	g_formats['c'] = format_c;
	g_formats['d'] = format_d;
	g_formats['c'] = format_c;
	g_formats['i'] = format_i;
	g_formats['e'] = format_e;
	g_formats['s'] = format_s;
	g_formats['o'] = format_o;
	g_formats['u'] = format_u;
	g_formats['x'] = format_x;
	g_formats['p'] = format_p;
	g_formats['%'] = format_percent;
}

int 	ft_vprintf(const char *format, va_list ap)
{
	return (ft_vdprintf(1, format, ap));
}

int 	ft_printf(const char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	return (ft_vprintf(format, ap));
}

int 	ft_vdprintf(int fd, const char *format, va_list ap)
{
	int			chars_wr;
	t_flags	*flags;

	chars_wr = 0;
	setlocale(LC_ALL, "");
	setup_formats();
	if (!format)
		exit(11); //TODO check
	while (*format)
	{
		if (*format == '%')
		{
			flags = read_format(fd, &format, ap);
			if (flags->format == '?') // <----- error
			{
				//format++;
				continue;
			}
			else if (flags->error)
				display_error(flags->error);
			chars_wr += switch_format(flags, ap);
			if (flags->error)
				display_error(flags->error);
		}
		else
			write_count(fd, format, 1, &chars_wr);
		format++;
	}
	return (chars_wr);
}

int		ft_dprintf(int fd, const char *format, ...) //maybe add restrict
{
	va_list	ap;

	va_start(ap, format);
	return (ft_vdprintf(fd, format, ap));
}
