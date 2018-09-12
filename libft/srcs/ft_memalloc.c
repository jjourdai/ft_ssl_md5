/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 11:49:40 by jjourdai          #+#    #+#             */
/*   Updated: 2018/02/03 13:35:52 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*s;

	s = (unsigned char*)malloc(size);
	if (s == NULL)
	{
		ft_fprintf(2, "Malloc failure\n");
		exit(EXIT_FAILURE);
	}
	ft_bzero(s, size);
	return (s);
}

void	ft_memalloc_failure(int nb, char *str)
{
	ft_printf(" FILE -->%s LINE \"%d\"\n", str, nb);
	exit(EXIT_FAILURE);
}
