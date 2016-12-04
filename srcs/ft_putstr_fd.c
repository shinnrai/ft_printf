/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 20:02:46 by ofedorov          #+#    #+#             */
/*   Updated: 2016/09/26 20:03:33 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

int	ft_putstr_fd(char const *s, int fd)
{
	int i;
	int	ret;

	i = 0;
	while (s && *s && i != -1)
		i = ((ret = ft_putchar_fd(*s++, fd)) != -1) ? i + ret : -1;
	return (s == NULL) ? -1 : i;
}
