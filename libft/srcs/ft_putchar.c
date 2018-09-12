/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 11:46:58 by jjourdai          #+#    #+#             */
/*   Updated: 2017/02/20 10:16:47 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_bin(unsigned int value)
{
	unsigned int size;

	size = 0;
	if (value <= 127)
		size = 7;
	else if (value <= 2047)
		size = 11;
	else if (value <= 65535)
		size = 16;
	else if (value <= 2097151)
		size = 20;
	return (size);
}

static void	put2octet(unsigned int v, unsigned char octet)
{
	unsigned char	o1;
	unsigned char	o2;
	unsigned int	mask1;

	mask1 = 49280;
	o2 = (v << 26) >> 26;
	o1 = ((v >> 6) << 27) >> 27;
	octet = (mask1 >> 8 | o1);
	write(1, &octet, 1);
	octet = ((mask1 << 24) >> 24) | o2;
	write(1, &octet, 1);
}

static void	put3octet(unsigned int v, unsigned char octet)
{
	unsigned char	o1;
	unsigned char	o2;
	unsigned char	o3;
	unsigned int	mask2;

	mask2 = 14712960;
	o3 = (v << 26) >> 26;
	o2 = ((v >> 6) << 26) >> 26;
	o1 = ((v >> 12) << 28) >> 28;
	octet = (mask2 >> 16) | o1;
	write(1, &octet, 1);
	octet = ((mask2 << 16) >> 24) | o2;
	write(1, &octet, 1);
	octet = ((mask2 << 24) >> 24) | o3;
	write(1, &octet, 1);
}

static void	put4octet(unsigned int v, unsigned char octet)
{
	unsigned char	o1;
	unsigned int	mask3;

	mask3 = 4034953344;
	o1 = (v << 26) >> 26;
	octet = ((mask3 << 24) >> 24) | o1;
	write(1, &octet, 1);
	o1 = ((v >> 6) << 26) >> 26;
	octet = ((mask3 << 16) >> 24) | o1;
	write(1, &octet, 1);
	o1 = ((v >> 12) << 26) >> 26;
	octet = ((mask3 << 8) >> 24) | o1;
	write(1, &octet, 1);
	o1 = ((v >> 18) << 29) >> 29;
	octet = (mask3 >> 24) | o1;
	write(1, &octet, 1);
}

void		ft_putchar(unsigned int value)
{
	unsigned int	v;
	unsigned int	size;
	unsigned char	octet;

	octet = 0;
	v = value;
	size = size_bin(value);
	if (size <= 7)
	{
		octet = value;
		write(1, &octet, 1);
	}
	else if (size <= 11)
		put2octet(v, octet);
	else if (size <= 16)
		put3octet(v, octet);
	else
		put4octet(v, octet);
}
