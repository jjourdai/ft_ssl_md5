/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 16:22:49 by jjourdai          #+#    #+#             */
/*   Updated: 2016/12/29 16:22:59 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa_u(unsigned int n)
{
	char				*s_nb;
	int					neg;
	int					len;
	unsigned int		n_cpy;

	neg = 0;
	n_cpy = n;
	len = 2;
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
