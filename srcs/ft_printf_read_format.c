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

static int	was_before(char c, char *format)
{
	if (*(format - 1) == c && c != '0')
		return (1);
	return (0);
}

static int	check_flags(t_flags *flags, char **format)
{
	while (**format == '-' || **format == '+' || **format == ' ' ||
			**format == '#' || **format == '0')
	{
		if (was_before(**format, *format))
		{
			flags->error = "Error: flag was used before";
			return (0);
		}
		if (**format == '-')
			flags->left_justified = true;
		else if (**format == '+')
			flags->sign = true;
		else if (**format == ' ' && flags->sign == false)
			flags->space = true;
		else if (**format == '#')
			flags->alternative = true;
		else if (**format == '0' && flags->left_justified == false)
			flags->zero = true;
		(*format)++;
	}
	return (1);
}

static int	check_precision(t_flags *flags, char **format, va_list ap)
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
	return (1);
}

int	check_length_mod(t_flags *flags, char **format)
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
	return (1);
}

int	check_field_width(t_flags *flags, char **format, va_list ap)
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
	return (1);
}

int	determine_format(t_flags *flags, char **format)
{
	if (**format == 'c' || **format == 's' || **format == 'd' ||
		**format == 'i' || **format == 'o' || **format == 'x' ||
		**format == 'u' || **format == 'f' || **format == 'e' ||
		**format == 'a' || **format == 'g' || **format == 'n' ||
		**format == 'p')
	{
		flags->format = **format;
		(*format)++;
	}
	else if (**format == 'X' || **format == 'F' || **format == 'E' ||
			**format == 'A' || **format == 'G')
	{
		flags->format = **format - ('A' - 'a');
		flags->capital = true;
		(*format)++;
	}
	else if (**format == 'C' || **format == 'S')
	{
		flags->format = **format - ('A' - 'a');
		if (flags->length_mod != LEN_NONE)
			flags->error = "Error: cannot use length modifiers with "
					"this format";
		(*format)++;
	}
	else
	{
		flags->error = "Error: unknown format";
		return (0);
	}
	return (1);
}

t_flags	*read_format(int fd, char **str, va_list ap) //0 flag is ignored for floats and ints
{
	t_flags	*flags;
	char	*format;

	format = *str;
	flags = new_flags(fd, LEN_NONE, 0, false);
	format++;
	if (!check_flags(flags, &format)) //TODO do this functions return void
		return (flags);
	if (!check_field_width(flags, &format, ap))
		return (flags);
	if (!check_precision(flags, &format, ap)) //for c it should return error if precision exists
		return (flags);
	if (!check_length_mod(flags, &format))
		return (flags);
	if (!determine_format(flags, &format))
		return (flags);
	if (flags->format == 'c' && flags->expl_precision == true)
		flags->error = "Error: undefined behavior";
	if (flags->format == 'n' && (flags->sign || flags->left_justified ||
		flags->space || flags->zero || flags->alternative ||
		flags->field_width != -1 || flags->expl_precision))
		flags->error = "Error: cannot use any flag, field width or "
				"precision with this format";
	if (!flags->error)
		*str = format;
	return (flags);
}