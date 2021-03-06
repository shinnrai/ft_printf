/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 11:51:07 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/24 11:51:15 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

size_t	ft_wstrlen(wchar_t *str)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		len += ft_wcharlen(*str);
		str++;
	}
	return (len);
}
