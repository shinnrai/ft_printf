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

static int   _format_d(ptrdiff_t nbr, int length, t_flags *flags) //TODO handle -1 and precision
{
	char	c;

    if (nbr < 0)
    {
        write(flags->fd, "-", 1);
        length++;
        length = _format_d(ABS(nbr / 10), length, flags);
    }
    else if (nbr > 9)
        length = _format_d(nbr / 10, length, flags);
	c = ABS(nbr % 10) + '0';
    write(flags->fd, &c, 1);
    length++;
    return (length);
}

int          format_d(ptrdiff_t nbr, t_flags *flags)
{
	if (nbr != 0 || flags->precision != 0)
    	return (_format_d(nbr, 0, flags));
	return (0);
}
