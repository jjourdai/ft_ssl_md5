/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpychar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 16:15:40 by jjourdai          #+#    #+#             */
/*   Updated: 2018/04/07 13:32:52 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_cpychar(char c, int nb)
{
	char	*str;
	int		i;

	if (nb < 1)
		return (0);
	str = ft_memalloc(sizeof(char) * (nb + 1));
	i = -1;
	while (++i != nb)
		str[i] = c;
	return (str);
}
