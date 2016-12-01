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

static int	_format_p(void *ptr, t_flags *flags)
{
	unsigned long long	val;
	int					len;
	char 				c;
	char				*hex;

	hex = "0123456789abcdef";
	val = (unsigned long long)ptr;
	len = 1;
	while (val >= 16)
	{
		val /= 16;
		len++;
	}
	val = (unsigned long long)ptr;
	if (flags->precision > len)
		len = flags->precision;
	if (flags->precision == 0 && val == 0)
		len = 0;
	while (len-- > 0)
	{
		c = hex[(ABS((val / ft_power(16, len)) % 16))]; //TODO check for wtf value
		ft_write(&c, 1, flags);
	}
	return (flags->error) ? -1 : flags->chars_wr;

}

int format_p(t_flags *flags, va_list ap)
{
	void				*val;
	int 				precision;

	val = va_arg(ap, void *);
	flags->just_count = true;
	_format_p(val, flags);
	flags->precision = ((flags->chars_val > flags->precision) && val != NULL) ? -1 : flags->precision;
	flags->chars_val += 2;
	flags->just_count = false;
	format_before(flags);//putting '-' in format function
	precision = flags->precision;
	ft_write("0x", 2, flags);
	if (flags->zero || flags->precision != -1)
		while (precision-- - flags->chars_val > 0)
			ft_write("0", 1, flags);
	if (flags->precision != 0 || val != 0)
		flags->chars_wr = _format_p(val, flags);
	else
		flags->chars_wr = (flags->error) ? -1 : flags->chars_wr;
	format_after(flags);
	return (flags->chars_wr);
}
