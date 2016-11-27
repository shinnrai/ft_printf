/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 14:50:11 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/01 14:50:12 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

const char	g_hex[17] = "0123456789abcdef"; //TODO move to libft

static int	_format_p(void *ptr, t_flags *flags)
{
	unsigned long long	val;
	short				len;
	char 				c;

	val = (unsigned long long)ptr;
	ft_write("0x", 2, flags);
	len = 1;
	while (val >= 16)
	{
		val /= 16;
		len++;
	}
	val = (unsigned long long)ptr;
	while (len-- != 0)
	{
		c = g_hex[(ABS((val / ft_power(16, len)) % 16))]; //TODO check for wtf value
		ft_write(&c, 1, flags);
	}
	return (flags->error) ? -1 : flags->chars_wr;

}

int format_p(t_flags *flags, va_list ap)
{
	void				*val;

	val = va_arg(ap, void *);
	flags->just_count = true;
	_format_p(val, flags);
	if (flags->precision == 0 && val == 0)
		flags->chars_val = 2;
	flags->just_count = false;
	format_before(flags);//putting '-' in format function
	if (flags->precision != 0 || val != 0)
		flags->chars_wr = _format_p(val, flags);
	else
	{
		ft_write("0x", 2, flags);
		flags->chars_wr = (flags->error) ? -1 : flags->chars_wr;
	}
	format_after(flags);
	return (flags->chars_wr);
}
