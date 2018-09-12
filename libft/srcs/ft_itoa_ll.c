/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:54:32 by jjourdai          #+#    #+#             */
/*   Updated: 2016/12/30 10:09:44 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_n_is_negativ(long long *n, int *neg)
{
	if (*n < 0)
	{
		*n *= -1;
		*neg = 1;
	}
}

char			*ft_itoa_ll(long long n)
{
	char			*s_nb;
	int				neg;
	int				len;
	long long		n_cpy;

	if (n == LONG_MIN)
		return ((s_nb = ft_strdup("-9223372036854775808")));
	neg = 0;
	n_cpy = n;
	len = 1;
	ft_n_is_negativ(&n, &neg);
	while (n_cpy /= 10)
		len++;
	len += neg;
	if ((s_nb = ft_memalloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	s_nb[len] = '\0';
	while (--len > -1)
	{
		s_nb[len] = n % 10 + 48;
		n = n / 10;
	}
	if (neg)
		s_nb[0] = '-';
	return (s_nb);
}
