/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:54:32 by jjourdai          #+#    #+#             */
/*   Updated: 2016/12/19 17:09:34 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_n_is_negativ(short int *n, int *neg)
{
	if (*n < 0)
	{
		*n *= -1;
		*neg = 1;
	}
}

char			*ft_itoa_h(short int n)
{
	char			*s_nb;
	int				neg;
	int				len;
	short int		n_cpy;

	if (n == -32768)
		return (s_nb = "-32768");
	neg = 0;
	n_cpy = n;
	len = 2;
	ft_n_is_negativ(&n, &neg);
	while (n_cpy /= 10)
		len++;
	len += neg;
	if ((s_nb = ft_memalloc(sizeof(char) * (len))) == NULL)
		return (NULL);
	s_nb[--len] = '\0';
	while (len--)
	{
		s_nb[len] = n % 10 + 48;
		n = n / 10;
	}
	if (neg)
		s_nb[0] = '-';
	return (s_nb);
}
