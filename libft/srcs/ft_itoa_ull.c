/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ull.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 16:23:33 by jjourdai          #+#    #+#             */
/*   Updated: 2017/01/02 11:55:54 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char					*ft_itoa_ull(unsigned long long n)
{
	char					*s_nb;
	int						len;
	unsigned long long		n_cpy;

	if (n == LONG_MAX)
		return (ft_strdup("777777777777777777777"));
	if ((long)n == LONG_MIN)
		return (ft_strdup("1000000000000000000000"));
	n_cpy = n;
	len = 2;
	while (n_cpy /= 10)
		len++;
	if ((s_nb = ft_memalloc(sizeof(char) * (len))) == NULL)
		return (NULL);
	s_nb[--len] = '\0';
	while (len--)
	{
		s_nb[len] = n % 10 + 48;
		n = n / 10;
	}
	return (s_nb);
}
