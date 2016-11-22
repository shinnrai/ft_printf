/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 14:47:38 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/01 14:47:41 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <libftprintf.h>

//TODO move to header
const char	g_hex[17] = "0123456789abcdef";

static int	get_power(long double *nbr)
{
	int i;

	i = 0;
	*nbr = ABS(*nbr);
	if (*nbr > 1)
		while ((*nbr) >= 2)
		{
			i++;
			*nbr /= 2;
		}
	else if (0 < *nbr && *nbr < 1)
		while (*nbr < 1)
		{
			i--;
			*nbr *= 2;
		}
	return (i);
}

static int	round(long double *nbr, t_flags *flags)
{
	int 		precision;
	long double	left;

	*nbr = ABS(*nbr);
	if (flags->precision == -1)
		flags->precision = 6; // TODO default value
	precision = flags->precision;
	left = *nbr - (int)*nbr;
	while (precision-- > 0)
		left = 16 * left - (int) (left * 16);
	if (left >= 0.5)
		left = -1;
	precision = flags->precision;
	while (precision-- > 0)
		left = left / 16;
	*nbr = *nbr - left;
	if (*nbr >= 2)
	{
		*nbr /= 2;
		return (1);
	}
	return (0);
}


static int	_format_a(long double nbr, t_flags *flags)
{
	int 	power;
	int 	left;
	t_flags	*flags_d;

	if (nbr < 0)
		ft_write("-", 1, flags);
	ft_write("0x", 2, flags);
	power = get_power(&nbr);
	power += round(&nbr, flags); //TODO test with min max
	left = flags->precision;
	ft_write((nbr == 0) ? "0" : "1", 1, flags);
	if (nbr != 0 && (nbr - (int)nbr != 0) && left != 0 || flags->alternative) //maybe remove left == 0
		ft_write(".", 1, flags);
	while (nbr != 0 && (nbr - (int)nbr != 0) && left-- != 0)
	{
		nbr = (nbr - (int)nbr) * 16;
		ft_write(&g_hex[(int)nbr], 1, flags);
	}
	ft_write("p", 1, flags);
	if (power >= 0)
		ft_write("+", 1, flags);
	flags_d = new_flags(flags->fd, 'd', false);
	flags_d->precision = 2;
	format_d(power, flags_d);
	return (flags->error) ? -1 : flags->chars_wr;
}

int 		format_a(t_flags *flags, va_list ap) //TODO check for nan +-inf
{
	long double	nbr;
	int			chars;

	if ()
	return (flags->error) ? -1 : _format_a(nbr, flags);
}