/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_uhh.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:10:05 by jjourdai          #+#    #+#             */
/*   Updated: 2016/12/15 10:44:58 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa_base_uhh(unsigned char n, char *base)
{
	char			*s_nb;
	int				n_cpy;
	int				len;

	n_cpy = n;
	len = 2;
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
	return (s_nb);
}
