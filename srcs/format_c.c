/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 14:47:59 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/01 14:48:00 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

/*static int	_format_c(int c, t_flags *flags)
{
	return (ft_putchar_fd((unsigned char)c, flags->fd));
}*/

static int	_format_c(wint_t c, t_flags *flags) //TODO check if is working with just %c
{
	return (ft_putwchar_fd(c, flags->fd));
}

int 		format_c(t_flags *flags, va_list ap)
{
	wint_t	val;

	if (flags->length_mod == LEN_L)
		val = va_arg(ap, wint_t);
	else
		val = va_arg(ap, int);
	flags->chars_val = _format_c(val, flags_count(flags));
	return (_format_c(val, flags));
}