/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_l.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:10:05 by jjourdai          #+#    #+#             */
/*   Updated: 2016/12/29 16:31:20 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_n_is_negativ(long *n, int *neg)
{
	if (*n < 0)
	{
		*n *= -1;
		*neg = 1;
	}
}

char			*ft_itoa_base_l(long n, char *base)
{
	char	*s_nb;
	long	len;
	long	n_cpy;
	int		neg;

	n_cpy = n;
	neg = 0;
	len = 2;
	ft_n_is_negativ(&n, &neg);
	len += neg;
	while (n_cpy /= ft_strlen(base))
		len++;
	if ((s_nb = ft_memalloc(sizeof(char) * (len))) == NULL)
		return (NULL);
	s_nb[--len] = '\0';
	while (len--)
	{
		s_nb[len] = base[n % ft_strlen(base)];
		n = n / ft_strlen(base);
	}
	if (neg)
		s_nb[0] = '-';
	return (s_nb);
}
