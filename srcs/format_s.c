/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 14:49:28 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/01 14:49:29 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

int		format_s(char *str, t_flags *flags)
{
	if (flags->precision != 0)
		return (ft_putnstr_fd(str, flags->fd, flags->precision));
	return (ft_putnstr_fd(str, flags->fd, flags->precision));
}

int		format_S(wchar_t *str, t_flags *flags)
{
	if (flags->precision != 0)
		return (ft_putnwstr_fd(str, flags->fd, flags->precision));
	return (ft_putnwstr_fd(str, flags->fd, flags->precision));
}