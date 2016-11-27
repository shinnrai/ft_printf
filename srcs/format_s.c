/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 14:49:28 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/01 14:49:29 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

//TODO move to libft
#define MIN(x, y) (x) <= (y) ? (x) : (y)
#define MAX(x, y) (x) > (y) ? (x) : (y)

static int		_format_s(wchar_t *str, t_flags *flags)
{
	int	written;

	written = 0;
	if (flags->just_count)
	{
		if (flags->precision != -1)
			written = MIN(flags->precision, (int)ft_wstrlen(str));
		else
			while (*str++)
				written++;
		flags->chars_val = written;
	}
	else
	{
		if (flags->precision != -1)
			written = ft_putnwstr_fd(str, flags->fd, flags->precision);
		else
			written = ft_putwstr_fd(str, flags->fd);
		flags->chars_wr += written;
	}
	if (written < 0)
		flags->error = "can't write to the file descriptor";
	return (flags->error) ? -1 : flags->chars_wr;
}

//TODO move to libft
static wchar_t	*ft_str_to_wstr(char *str)
{
	wchar_t	*wstr;
	int		len;

	len = ft_strlen(str);
	wstr = (wchar_t*)malloc(sizeof(wchar_t) * (len + 1));
	wstr[len] = '\0';
	while (len-- >= 0)
		wstr[len] = (wchar_t)str[len];
	return (wstr);
}

static wchar_t	*get_value(t_flags *flags, va_list ap)
{
	if (flags->length_mod == LEN_L)
		return (va_arg(ap, wchar_t*));
	if (flags->length_mod == LEN_NONE)
		return (ft_str_to_wstr(va_arg(ap, char*)));
	return (NULL);
}

int 			format_s(t_flags *flags, va_list ap)
{
	wchar_t	*val;

	val = get_value(flags, ap);
	flags->just_count = true;
	_format_s(val, flags);
	flags->just_count = false;
	format_before(flags);
	_format_s(val, flags);
	format_after(flags);
	return (flags->chars_wr);
}
