/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:22:19 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/12 17:22:21 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

t_flags	*new_flags(int fd, char format, bool just_count)
{
	t_flags	*flags;

	flags = (t_flags*)malloc(sizeof(t_flags)); //TODO check for error
	flags->fd = fd;
	flags->format = format;
	flags->length_mod = LEN_NONE;
	flags->just_count = just_count;
	flags->chars_wr = 0;
	flags->error = NULL;
	flags->alternative = false;
	flags->capital = false;
	flags->field_width = -1;
	flags->left_justified = false;
	flags->precision = -1;
	flags->expl_precision = false;
	flags->sign = false;
	flags->space = false;
	return (flags);
}

t_flags	*flags_count(t_flags *flags)
{
	t_flags	*flags_count = new_flags(flags->fd, flags->format, true);
	flags_count->length_mod = flags->length_mod;
	flags_count->alternative = flags->alternative;
	flags_count->capital = flags->capital;
	flags_count->precision = flags->precision;
	flags_count->expl_precision = flags->expl_precision;
	flags_count->sign = flags->sign;
	flags_count->space = flags->space;
	return (flags_count);
}

int		format(t_flags *flags, va_list ap)
{
	(void)ap;
}
