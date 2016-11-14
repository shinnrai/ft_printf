/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 14:47:59 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/01 14:48:00 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

int	format_c(int c, t_flags *flags)
{
	return (ft_putchar_fd((unsigned char)c, flags->fd));
}

int	format_C(wint_t c, t_flags *flags)
{
	return (ft_putwchar_fd(c, flags->fd));
}
