/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 15:29:42 by ofedorov          #+#    #+#             */
/*   Updated: 2016/11/06 15:29:43 by ofedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

static int	wr_cs(int fd, const char *str, int size)
{
	char	c;
	int		i;

	i = 0;
	while (i < size)
	{
		c = (str[i] >= 'a' && str[i] <= 'z') ? str[i] + ('A' - 'a') : str[i];
		if (write(fd, &c, 1) != 1)
			return (-1);
		i++;
	}
	return (i);
}

void		ft_write(const char *to_write, int size, t_flags *flags)
{
	if (flags->just_count == true)
		flags->chars_wr += size;
	else if (flags->capital == true)
	{
		if (wr_cs(flags->fd, to_write, size) != size)
			flags->error = "Error in writing to file descriptor";
		else
			flags->chars_wr += size;
	}
	else
	{
		if (write(flags->fd, to_write, size) != size)
			flags->error = "Error in writing to file descriptor";
		else
			flags->chars_wr += size;
	}
}