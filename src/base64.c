/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 10:23:13 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/17 16:16:00 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static char value_base64[] = {
	'A','B','C','D','E','F','G','H',
	'I','J','K','L','M','N','O','P',
	'Q','R','S','T','U','V','W','X',
	'Y','Z','a','b','c','d','e','f',
	'g','h','i','j','k','l','m','n',
	'o','p','q','r','s','t','u','v',
	'w','x','y','z','0','1','2','3',
	'4','5','6','7','8','9','+','/'
};

static char return_value(char c)
{
	size_t i;

	i = -1;
	while (++i < 65)
	{
		if (c == '=')
			return ('\0');
		else if (c == value_base64[i])
			return (i);
	}
}

void	base64_decode(t_data *info)
{
	char	*new_str;
	size_t		new_len;
	size_t		i;
	size_t		j;
	uint32_t intermediate;
	uint32_t test;


	i = -1;
	while (++i < info->len)
		info->bytes[i] = return_value(info->bytes[i]);
	new_len = info->len / 4 * 3;
	size_t padding = (info->len % 4 > 0) ? 3 - info->len % 4 : 0;
	new_str = ft_memalloc(new_len + 1);
	i = 0;
	j = 0;
	while (j < info->len)
	{
		// ft_printf("%d\n", j);
		// ft_printf("%d\n", i);
		intermediate = SWAP_VALUE(*((uint32_t*)&info->bytes[j]));
		// ft_printf("binary %032b\n", intermediate);
		test = (0x3f000000 & intermediate) >> 6 | (0x3f0000 & intermediate) >> 4 | (0x3f00 & intermediate) >> 2 | (0x3f & intermediate);
		// ft_printf("binary %024b\n", test);
		new_str[i] = ((0xff0000 & test)) >> 16;
		new_str[i + 1] = ((0xff00 & test) >> 8);
		new_str[i + 2] = ((0xff & test));
		// new_str[i + 3] = 0;
		i += 3;
		j += 4;
	}
	// new_str[i - 1] = '\n';
	write(1, new_str, new_len - padding);
	exit(0);
}

void	base64_encode(t_data *info)
{
	char	*new_str;
	size_t		new_len;
	size_t		i;
	size_t		j;
	uint32_t intermediate;
	size_t padding = (info->len % 3 > 0) ? 3 - info->len % 3 : 0;


	new_len = info->len / 3 * 4;
	new_len = (info->len % 3 != 0) ? new_len += 4 : new_len;
	new_str = ft_memalloc(new_len + 1);
	i = 0;
	j = 0;
	while (j < info->len)
	{
		intermediate = SWAP_VALUE(*((uint32_t*)&info->bytes[j]));
		new_str[i] = ((0xfc000000 & intermediate) >> 26);
		new_str[i + 1] = ((0x3f00000 & intermediate) >> 20);
		new_str[i + 2] = ((0xfc000 & intermediate) >> 14);
		new_str[i + 3] = ((0x3f00 & intermediate) >> 8);
		i += 4;
		j += 3;
	}
	i = -1;
	while (++i < new_len - padding)
		new_str[i] = value_base64[new_str[i]];
	while (padding)
	{
		new_str[i++] = '=';
		padding--;
	}
	new_str[new_len] = '\n';
	write(1, new_str, new_len + 1);
	exit(0);
}

void 	base64(t_data *info)
{
	base64_decode(info);
}



















//
