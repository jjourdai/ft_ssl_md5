/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_0x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 16:27:26 by jjourdai          #+#    #+#             */
/*   Updated: 2016/12/29 16:27:28 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa_0x(void *n, char *base)
{
	char			*s_nb;
	int				len;
	unsigned long	n_cpy;

	len = 15;
	n_cpy = (unsigned long)n;
	if ((s_nb = ft_memalloc(sizeof(char) * 15)) == NULL)
		return (NULL);
	s_nb[--len] = '\0';
	while (len--)
	{
		s_nb[len] = base[n_cpy % ft_strlen(base)];
		n_cpy = n_cpy / ft_strlen(base);
	}
	s_nb[0] = '0';
	s_nb[1] = 'x';
	return (s_nb);
}
