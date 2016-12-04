/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 23:04:25 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/21 23:04:29 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

static int _format_other(t_flags *flags)
{
	if (flags->format)
		ft_write(&flags->format, 1, flags);
	return (flags->error) ? -1 : flags->chars_wr;
}

int		format_another(t_flags *flags, va_list ap)
{
	(void)ap;
	flags->chars_val = 1;
	format_before(flags);
	_format_other(flags);
	format_after(flags);
	return (flags->chars_wr);
}
