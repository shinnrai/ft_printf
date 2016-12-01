/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 14:49:40 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/01 14:49:41 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

static int 			_format_u(unsigned long long nbr, t_flags *flags) //TODO handle -1
{
	short				len;
	unsigned long long	val;
	char				c;

	val = nbr;
	len = 1;
	while (val >= 10)
	{
		val /= 10;
		len++;
	}
	while (len-- != 0)
	{
		c = '0' + (ABS((nbr / ft_power(10, len)) % 10)); //TODO check for wtf value
		ft_write(&c, 1, flags);
	}
	return (flags->error) ? -1 : flags->chars_wr;
}

int          format_u(t_flags *flags, va_list ap)
{
	unsigned long long	val;

	val = get_value_oxu(flags, ap);
	flags->just_count = true;
	_format_u(val, flags);
	flags->just_count = false;
	if (flags->precision == 0 && val == 0)
		flags->chars_val = 0;
	format_before(flags);
	if (flags->precision != 0 || val != 0)
		_format_u(val, flags);
	format_after(flags);
	return (flags->chars_wr);
}