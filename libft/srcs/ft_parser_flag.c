/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 13:28:41 by jjourdai          #+#    #+#             */
/*   Updated: 2017/03/03 18:29:13 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_parser_flag(char **argv)
{
	int		i;
	int		j;
	char	**str;

	i = 1;
	if (!argv[i])
		return (NULL);
	while (argv[i] && argv[i][0] == '-')
		i++;
	str = ft_memalloc(sizeof(char*) * (i));
	str[i - 1] = 0;
	j = 0;
	while (j < i - 1)
	{
		str[j] = argv[j + 1];
		j++;
	}
	return (str);
}
