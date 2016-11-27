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

static int _format_percent(t_flags *flags)
{
	ft_write("%", 1, flags);
	return (flags->error) ? -1 : flags->chars_wr;
}

int		format_percent(t_flags *flags, va_list ap)
{
	flags->chars_val = 1;
	format_before(flags);
	_format_percent(flags);
	format_after(flags);
	return (flags->chars_wr);
}
