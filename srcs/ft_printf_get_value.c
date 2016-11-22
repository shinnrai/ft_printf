/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_get_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 16:33:14 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/16 16:33:15 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

unsigned long long int	get_value_oxu(t_flags *flags, va_list ap)
{
	unsigned long long int	val;

	if (flags->length_mod == LEN_T)
		val = va_arg(ap, ptrdiff_t); //TODO check if working
	else if (flags->length_mod == LEN_Z)
		val = va_arg(ap, size_t);
	else if (flags->length_mod == LEN_J)
		val = va_arg(ap, uintmax_t);
	else if (flags->length_mod == LEN_LL)
		val = va_arg(ap, unsigned long long);
	else if (flags->length_mod == LEN_L)
		val = va_arg(ap, unsigned long);
	else if (flags->length_mod == LEN_NONE)
		val = va_arg(ap, unsigned int);
	else if (flags->length_mod == LEN_H)
		val = va_arg(ap, unsigned short); //TODO check if working, if not, switch to cast
	else if (flags->length_mod == LEN_HH)
		val = va_arg(ap, unsigned char);
	else
		return (0);
}
