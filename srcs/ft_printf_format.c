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

unsigned char g_cs[9] = {0, 0, 1, 1, 0, 0, 0, 0, 0};
unsigned char g_dioxn[9] = {1, 1, 1, 1, 1, 1, 1, 1, 0};
unsigned char g_feag[9] = {0, 0, 1, 1, 0, 0, 0, 0, 1};
unsigned char g_p[9] = {0, 0, 1, 0, 0, 0, 0, 0, 0};

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

int 	check_l_mod(t_flags *flags)
{
	if (flags->format == 'c' || flags->format == 's')
		return (g_cs[flags->length_mod]);
	if (flags->format == 'd' || flags->format == 'i' ||
		flags->format == 'o' || flags->format == 'x' ||
		flags->format == 'n')
		return(g_dioxn[flags->length_mod]);
	if (flags->format == 'f' || flags->format == 'e' ||
		flags->format == 'a' || flags->format == 'g')
		return (g_feag[flags->length_mod]);
	if (flags->format == 'p')
		return (g_p[flags->length_mod]);
	return (0);
}

int		format(t_flags *flags, va_list ap)
{
	if (!check_l_mod(flags))
		flags->error = "Error: cannot use this length modifier "
				"with this format";
	(void)ap;
}
