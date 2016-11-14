/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 13:17:11 by ofedorov          #+#    #+#             */
/*   Updated: 2016/09/26 22:29:42 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

size_t	ft_strlen(const char *s)
{
	const char	*cs;

	cs = s;
	while (cs && *cs)
		cs++;
	return (cs - s);
}
