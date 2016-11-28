/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 14:49:52 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/01 14:49:53 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

static int	_format_x(unsigned long long nbr, t_flags *flags)
{
	short		len;
	ptrdiff_t	val;
	char		c;
	char		*hex;

	hex = "0123456789abcdef";
	val = nbr;
	len = 1;
	while (val >= 16)
	{
		val /= 16;
		len++;
	}
	while (len-- != 0)
	{
		c = hex[(ABS((nbr / ft_power(16, len)) % 16))]; //TODO check for wtf value
		ft_write(&c, 1, flags);
	}
	return (flags->error) ? -1 : flags->chars_wr;
}

int 	format_x(t_flags *flags, va_list ap) //TODO check 0 precision and 0 value, also alternative
{
	unsigned long long	val;
	int 				precision;

	val = get_value_oxu(flags, ap);
	flags->just_count = true;
	_format_x(val, flags);
	if (flags->precision == 0 && val == 0)
		flags->chars_val = 0;
	flags->just_count = false;
	format_before(flags);//putting '-' in format function
	if (flags->alternative)
		ft_write("0x", 2, flags);
	precision = (flags->precision == -1) ? flags->field_width : flags->precision;
	if (precision != 0)
		while (precision-- - flags->chars_val > 0)
			ft_write("0", 1, flags);
	if (flags->precision != 0 || val != 0 || flags->alternative)
		_format_x(val, flags);
	format_after(flags);
	return (flags->chars_wr);
}