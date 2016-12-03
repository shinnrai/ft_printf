/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_o.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 14:49:16 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/01 14:49:18 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

unsigned long long	get_value_oxu(t_flags *flags, va_list ap)
{
	if (flags->length_mod == LEN_T)
		return (unsigned long long)va_arg(ap, ptrdiff_t);
	if (flags->length_mod == LEN_Z)
		return (unsigned long long)va_arg(ap, size_t);
	if (flags->length_mod == LEN_J)
		return (unsigned long long)va_arg(ap, uintmax_t);
	if (flags->length_mod == LEN_LL)
		return (unsigned long long)va_arg(ap, unsigned long long);
	if (flags->length_mod == LEN_L)
		return (unsigned long long)va_arg(ap, unsigned long);
	if (flags->length_mod == LEN_NONE)
		return (unsigned long long)va_arg(ap, unsigned int);
	if (flags->length_mod == LEN_H)
		return (unsigned long long)(unsigned short)va_arg(ap, int);
	if (flags->length_mod == LEN_HH)
		return (unsigned long long)(unsigned char)va_arg(ap, int);
	return (0);
}

static int	_format_o(unsigned long long nbr, t_flags *flags)
{
	short		len;
	ptrdiff_t	val;
	char		c;
	char		*hex;

	hex = "0123456789abcdef";
	val = nbr;
	len = 1;
	while (val >= 8)
	{
		val /= 8;
		len++;
	}
	while (len-- != 0)
	{
		c = '0' + (ABS((nbr / ft_power(8, len)) % 8)); //TODO check for wtf value
		ft_write(&c, 1, flags);
	}
	return (flags->error) ? -1 : flags->chars_wr;
}

int 	format_o(t_flags *flags, va_list ap) //TODO check 0 precision and 0 value, also alternative
{
	unsigned long long	val;

	val = get_value_oxu(flags, ap);
	flags->just_count = true;
	_format_o(val, flags);
	if (flags->precision == 0 && val == 0 && !flags->alternative)
		flags->chars_val = 0;
	flags->just_count = false;
	format_before(flags);//putting '-' in format function
	if (flags->alternative && val != 0 && flags->precision <= flags->chars_val + 1)
		ft_write("0", 1, flags);
	if (flags->precision != 0 || val != 0 || flags->alternative)
		flags->chars_wr = _format_o(val, flags);
	format_after(flags);
	return (flags->chars_wr);
}
