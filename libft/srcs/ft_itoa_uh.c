/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_uh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:54:32 by jjourdai          #+#    #+#             */
/*   Updated: 2016/12/15 17:27:54 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa_uh(unsigned short int n)
{
	char					*s_nb;
	int						neg;
	int						len;
	unsigned short int		n_cpy;

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
	return (s_nb);
}
