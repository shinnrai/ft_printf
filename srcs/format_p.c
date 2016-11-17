/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 14:50:11 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/01 14:50:12 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

int format_p(t_flags *flags, va_list ap)
{
	void	*ptr;

	ptr = va_arg(ap, void *);
	//TODO with 0-f representation
}
