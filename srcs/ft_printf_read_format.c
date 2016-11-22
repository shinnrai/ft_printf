/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_read_format.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 22:45:20 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/12 22:45:24 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

# define IS_FLAG(x) \
		((x) == '-' || (x) == '+' || (x) == ' ' || (x) == '#' || (x) == '0')

unsigned char g_cs[9] = {0, 0, 1, 1, 0, 0, 0, 0, 0};
unsigned char g_dioxn[9] = {1, 1, 1, 1, 1, 1, 1, 1, 0};
unsigned char g_feag[9] = {0, 0, 1, 1, 0, 0, 0, 0, 1};
unsigned char g_pCS_perc[9] = {0, 0, 1, 0, 0, 0, 0, 0, 0};

static void	check_flags(t_flags *flags, char **format)
{
	while (**format == '-' || **format == '+' || **format == ' ' ||
			**format == '#' || **format == '0')
	{
		if (**format == '-')
			flags->left_justified = true;
		else if (**format == '+')
			flags->sign = true;
		else if (**format == ' ')
			flags->space = true;
		else if (**format == '#')
			flags->alternative = true;
		else if (**format == '0')
			flags->zero = true;
		(*format)++;
	}
	if ((flags->space && flags->sign) || (flags->zero && flags->left_justified))
		flags->error = "cannot use these flags together";
}

static void	check_precision(t_flags *flags, char **format, va_list ap)
{
	if (**format == '.')
	{
		(*format)++;
		if (**format == '*')
		{
			flags->precision = va_arg(ap, int); //TODO also handle error?
			if (flags->precision < 0)
				flags->precision = -2;
			flags->expl_precision = true;
			(*format)++;
		}
		else if (ft_isdigit(**format))
		{
			flags->precision = ft_atoi(*format);
			flags->expl_precision = true;
			while (ft_isdigit(**format))
				(*format)++;
		}
		else
			flags->precision = 0;
	}
}
void	check_length_mod(t_flags *flags, char **format)
{
	if (**format == 'h' && *(*format + 1) == 'h')
		flags->length_mod = LEN_HH;
	else if (**format == 'h')
		flags->length_mod = LEN_H;
	else if (**format == 'l' && *(*format + 1) == 'l')
		flags->length_mod = LEN_LL;
	else if (**format == 'l')
		flags->length_mod = LEN_L;
	else if (**format == 'j')
		flags->length_mod = LEN_J;
	else if (**format == 'z')
		flags->length_mod = LEN_Z;
	else if (**format == 't')
		flags->length_mod = LEN_T;
	else if (**format == 'L')
		flags->length_mod = LEN_L_CAP;
	else
		flags->length_mod = LEN_NONE;
	(*format)++;
	if (flags->length_mod == LEN_HH || flags->length_mod == LEN_LL)
		(*format)++;
}

void	check_field_width(t_flags *flags, char **format, va_list ap)
{
	if (**format == '*')
		flags->field_width = va_arg(ap, int); //TODO maybe check for error
	else if (ft_isdigit(**format))
		flags->field_width = ft_atoi(*format);
	if (flags->field_width < 0)
	{
		flags->left_justified = true;
		flags->field_width = -(flags->field_width);
	}
	if (**format == '*')
		(*format)++;
	else if (ft_isdigit(**format))
		while (ft_isdigit(**format))
			(*format)++;
}

void	determine_format(t_flags *flags, char **f)
{
	if (**f == 'c' || **f == 's' || **f == 'd' || **f == 'i' || **f == 'o' ||
		**f == 'x' || **f == 'u' || **f == 'f' || **f == 'e' || **f == 'a' ||
		**f == 'g' || **f == 'n' || **f == 'p')
		flags->format = **f;
	else if (**f == 'X' || **f == 'F' || **f == 'E' || **f == 'A' || **f == 'G')
	{
		flags->format = **f - ('A' - 'a');
		flags->capital = true;
	}
	else if (**f == 'C' || **f == 'S' || **f == 'D' || **f == 'O' || **f == 'U')
	{
		flags->format = **f - ('A' - 'a');
		if (flags->length_mod != LEN_NONE)
			flags->error = "cannot use length modifiers with this format";
		flags->length_mod == LEN_L;
	}
	else if (**f == '%')
		flags->format = '%';
	else
	{
		flags->error = "unknown format";
		return ;
	}
	(*f)++;
}

static void	check_l_mod(t_flags *flags)
{
	int ret;

	ret = 0;
	if (flags->format == 'c' || flags->format == 's')
		ret = g_cs[flags->length_mod];
	if (flags->format == 'd' || flags->format == 'i' || flags->format == 'o' ||
		flags->format == 'x' || flags->format == 'n')
		ret = g_dioxn[flags->length_mod];
	if (flags->format == 'f' || flags->format == 'e' || flags->format == 'a' ||
		flags->format == 'g')
		ret = g_feag[flags->length_mod];
	if (flags->format == 'p' || flags->format == '%')
		ret = g_pCS_pers[flags->length_mod];
	if (ret == 0)
		flags->error = "cannot use this length modifier "
				"with this format";
}

void	check_specific_f(t_flags *flags, char *format)
{
	if ((flags->format == 'c' && (flags->expl_precision || flags->sign ||
			flags->space || flags->alternative || flags->zero)) ||
		(flags->format == 's' && (flags->sign || flags->space || flags->zero ||
			flags->alternative)) ||
		((flags->format == 'd' || flags->format == 'i') && flags->alternative)
		|| ((flags->format == 'o' || flags->format == 'x' ||
		flags->format == 'u') && (flags->sign || flags->space)) ||
		(flags->format == 'u' && flags->alternative) ||
		(flags->format == 'n' && (flags->sign || flags->space || flags->zero ||
			flags->left_justified || flags->field_width != -1 ||
			flags->alternative || flags->expl_precision)) ||
		(flags->format == 'p' && (flags->sign || flags->space || flags->zero ||
			flags->alternative || flags->expl_precision))) //TODO OMG CHECK THIS SHIT
		flags->error = "undefined behavior";

}

t_flags	*read_format(int fd, char **str, va_list ap)
{
	t_flags	*flags;
	char	*format;

	format = *str;
	flags = new_flags(fd, LEN_NONE, 0, false);
	format++; //TODO maybe do it before
	check_flags(flags, &format);
	check_field_width(flags, &format, ap);
	check_precision(flags, &format, ap);
	check_length_mod(flags, &format);
	determine_format(flags, &format);
	check_l_mod(flags);
	check_specific_f(flags, format);
	if (!flags->error)
		*str = format;
	return (flags);
}