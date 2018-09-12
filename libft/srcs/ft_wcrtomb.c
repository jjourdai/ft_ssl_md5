/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcrtomb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 11:46:58 by jjourdai          #+#    #+#             */
/*   Updated: 2016/12/22 09:55:36 by jjourdai         ###   ########.fr       */
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

static int	put2octet(unsigned int v, char *s)
{
	char			str[3];
	unsigned char	o1;
	unsigned char	o2;
	unsigned int	mask1;

	mask1 = 49280;
	o2 = (v << 26) >> 26;
	o1 = ((v >> 6) << 27) >> 27;
	str[0] = (mask1 >> 8 | o1);
	str[1] = ((mask1 << 24) >> 24) | o2;
	str[2] = '\0';
	ft_memcpy(s, str, 3);
	return (2);
}

static int	put3octet(unsigned int v, char *s)
{
	char			str[4];
	unsigned char	o1;
	unsigned char	o2;
	unsigned char	o3;
	unsigned int	mask2;

	mask2 = 14712960;
	o3 = (v << 26) >> 26;
	o2 = ((v >> 6) << 26) >> 26;
	o1 = ((v >> 12) << 28) >> 28;
	str[0] = (mask2 >> 16) | o1;
	str[1] = ((mask2 << 16) >> 24) | o2;
	str[2] = ((mask2 << 24) >> 24) | o3;
	str[3] = '\0';
	ft_memcpy(s, str, 4);
	return (3);
}

static int	put4octet(unsigned int v, char *s)
{
	char			str[5];
	unsigned char	o1;
	unsigned int	mask3;

	mask3 = 4034953344;
	o1 = (v << 26) >> 26;
	str[3] = ((mask3 << 24) >> 24) | o1;
	o1 = ((v >> 6) << 26) >> 26;
	str[2] = ((mask3 << 16) >> 24) | o1;
	o1 = ((v >> 12) << 26) >> 26;
	str[1] = ((mask3 << 8) >> 24) | o1;
	o1 = ((v >> 18) << 29) >> 29;
	str[0] = (mask3 >> 24) | o1;
	str[4] = '\0';
	ft_memcpy(s, str, 5);
	return (4);
}

size_t		ft_wcrtomb(char *s, wchar_t d)
{
	unsigned int v;
	unsigned int size;

	v = d;
	size = size_bin(v);
	if (size <= 7)
	{
		ft_memcpy(s, (char*)&v, 2);
	}
	else if (size <= 11)
		return (put2octet(v, s));
	else if (size <= 16)
		return (put3octet(v, s));
	else
		return (put4octet(v, s));
	return (1);
}
