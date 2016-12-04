/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 19:45:07 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/06 19:45:09 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

size_t	ft_strncpy_count(char *dst, const char *src, size_t len)
{
	char	*cdst;

	cdst = dst;
	while (len > 0 && *src != '\0')
	{
		*cdst++ = *src++;
		len--;
	}
	return (cdst - dst);
}
