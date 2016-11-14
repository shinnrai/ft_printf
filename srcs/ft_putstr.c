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

int	ft_putstr_fd(char const *str, int fd)
{
	int i;

	i = 0;
	while (str && *str && i != -1)
		i = (ft_putchar_fd(*str++, fd) == 1) ? i + 1 : -1;
	return (str == NULL) ? -1 : i;
}
