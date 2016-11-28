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

#define is_dioxu(c) c == 'd' || c == 'i' || c == 'o' || c == 'x' || c == 'u'

t_flags	*new_flags(int fd, char format, bool just_count)
{
	t_flags	*flags;

	flags = (t_flags*)malloc(sizeof(t_flags)); //TODO check for error
	flags->fd = fd;
	flags->format = format;
	flags->length_mod = LEN_NONE;
	flags->just_count = just_count;
	flags->chars_wr = 0;
	flags->chars_val = 0;
	flags->error = NULL;
	flags->alternative = false;
	flags->capital = false;
	flags->field_width = -1;
	flags->spec_width = false;
	flags->left_justified = false;
	flags->precision = -1;
	flags->expl_precision = false;
	flags->sign = false;
	flags->positive = true;
	flags->space = false;
	return (flags);
}

void	format_before(t_flags *flags)
{
	int	spaces;

	spaces = flags->field_width - flags->chars_val;
	spaces += (flags->format == 'x' && flags->alternative ? 2 : 0);
	if ((flags->format == 'd' || flags->format == 'o' || flags->format == 'x' ||
		flags->format == 'u') && (flags->precision > flags->chars_val))
		spaces -= flags->precision - flags->chars_val;
	if (!flags->left_justified && flags->field_width != -1 && !flags->zero)
		while (spaces-- > 0)
			ft_write(" ", 1, flags);
	if (flags->sign && flags->positive)
		ft_write("+", 1, flags);
	if (flags->space && flags->positive)
		ft_write(" ", 1, flags);
	if (!flags->positive)
		ft_write("-", 1, flags);
	//TODO check if something else need to be done here
}

void	format_after(t_flags *flags) //TODO check if it's working
{
	if (flags->error || flags->chars_wr == -1)
		flags->chars_wr = -1;
	else if (flags->left_justified && flags->field_width != -1)
		while (flags->chars_wr < flags->field_width && !flags->error)
			ft_write(" ", 1, flags);
}

int		switch_format(t_flags *flags, va_list ap) //TODO redo
{
	return (g_formats[(int)flags->format](flags, ap));

}
