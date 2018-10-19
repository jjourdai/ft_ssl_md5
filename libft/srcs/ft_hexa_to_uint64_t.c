/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 18:46:24 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/19 14:44:03 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	caract(char c, char *base)
{
	int i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

int	string_is_only_hexchar(char *str)
{
	int i;
	int j;
	char 	*base = "0123456789ABCDEFabcdef";

	i = 0;
	while ((str[i] == '\n') || (str[i] == '\t') || (str[i] == '\v') ||
		(str[i] == ' ') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	while (str[i])
	{
		j = 0;
		while (base[j] != str[i])
		{
			if (base[j + 1] == '\0' && str[i] != base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

uint64_t	ft_hexa_to_uint64_t(char *str)
{
	int			i;
	uint64_t	nbr;
	uint64_t	prev_nbr;
	char		*base = "0123456789ABCDEF";

	nbr = 0;
	prev_nbr = 0;
	i = 0;
	while ((str[i] == '\n') || (str[i] == '\t') || (str[i] == '\v') ||
			(str[i] == ' ') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	while (str[i])
	{
		nbr = nbr * ft_strlen(base) + caract(str[i], base);
		if (prev_nbr > nbr)
			return (prev_nbr);
		prev_nbr = nbr;
		i++;
	}
	return (nbr);
}
