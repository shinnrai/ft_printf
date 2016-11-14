/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 14:48:44 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/01 14:48:46 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

const char	g_dec[11] = "0123456789";

static int  get_power(double *nbr)
{
	int i;

	i = 0;
	if (*nbr >= 10)
		while ((*nbr) >= 10)
		{
			i++;
			*nbr /= 10;
		}
	else if (0 < *nbr && *nbr < 1)
		while (*nbr < 1)
		{
			i--;
			*nbr *= 10;
		}
	return (i);
}

static void	abs_round(long double *nbr, t_flags *flags)
{
	int 		precision;
	long double	left;

	*nbr = ABS(*nbr);
	if (flags->precision == -1)
		flags->precision = 13; // TODO default value
	precision = flags->precision;
	left = *nbr - (int)*nbr;
	while (precision-- > 0)
		left = 10 * left - (int) (left * 10);
	if (left >= 0.5)
		left = -1;
	precision = flags->precision;
	while (precision-- > 0)
		left = left / 10;
	*nbr = *nbr - left;
}

int 	format_e(long double nbr, t_flags *flags) //TODO check power e+00 or e+0
{
	int power;
	int c;
	int left;

	c = 0;
	if (nbr < 0)
		ft_write("-", 1, flags, &c);
	abs_round(&nbr, flags); //TODO test with min max
	left = flags->precision;
	power = get_power(&nbr);
	ft_write(&g_dec[(int)nbr], 1, flags, &c);
	if (nbr != 0 && (nbr - (int)nbr != 0) && left != 0) //maybe remove left == 0
		ft_write(".", 1, flags, &c);
	while (nbr != 0 && (nbr - (int)nbr != 0) && left-- != 0)
	{
		nbr = (nbr - (int)nbr) * 10;
		ft_write(&g_dec[(int)nbr], 1, flags, &c);
	}
	ft_write("e", 1, flags, &c);
	if (power >= 0)
		ft_write("+", 1, flags, &c);
	flags->precision = 2;
	c = (left = format_d(power, flags)) != -1 ? c + left : -1;
	return (c);
}
