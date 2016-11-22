/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 14:48:26 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/01 14:48:28 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
//TODO add to libft
static ptrdiff_t	power_ten(int power)
{
	ptrdiff_t	nbr;

	nbr = 1;
	if (power < 0)
		return (0);
	while (power-- > 0)
		nbr *= 10;
	return (nbr);
}

static int   _format_d(ptrdiff_t nbr, t_flags *flags) //TODO handle -1 and precision
{
	short		len;
	ptrdiff_t	val;
	char		c;

    val = nbr;
	len = 0;
	while (val != 0)
	{
		val /= 10;
		len++;
	}
	while (len-- != 0)
	{
		c = '0' + (ABS(nbr / power_ten(len))) % 10; //TODO check for wtf value
		ft_write(&c, 1, flags);
	}
    return (flags->chars_wr);
}

static ptrdiff_t	get_value(t_flags *flags, va_list ap)
{
	if (flags->length_mod == LEN_T)
		return (ptrdiff_t)va_arg(ap, ptrdiff_t);
	if (flags->length_mod == LEN_Z)
		return (ptrdiff_t)va_arg(ap, ssize_t);
	if (flags->length_mod == LEN_J)
		return (ptrdiff_t)va_arg(ap, intmax_t);
	if (flags->length_mod == LEN_LL)
		return (ptrdiff_t)va_arg(ap, long long);
	if (flags->length_mod == LEN_L)
		return (ptrdiff_t)va_arg(ap, long);
	if (flags->length_mod == LEN_NONE)
		return (ptrdiff_t)va_arg(ap, int);
	if (flags->length_mod == LEN_H)
		return (ptrdiff_t)(short int)va_arg(ap, int);
	if (flags->length_mod == LEN_HH)
		return (ptrdiff_t)(char)va_arg(ap, int);
	return (0);
}

int          format_d(t_flags *flags, va_list ap)
{
	ptrdiff_t	val;

	val = get_value(flags, ap);
	flags->chars_val = _format_d(val, flags_count(flags));
	flags->positive = (val < 0) ? false : true;
	format_before(flags);//putting '-' in format function
	if (flags->precision != 0)
		while (flags->precision-- - flags->chars_val > 0)
			ft_write("0", 1, flags);
	if (flags->precision != 0 && val != 0) //TODO check if working (precision)
		_format_d(val, flags);
	return (flags->chars_wr);
}
