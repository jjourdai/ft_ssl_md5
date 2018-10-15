/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 10:23:13 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/15 16:55:15 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static char g_value_base64[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/',
	0,
};

static char	return_value(char c, size_t *equal)
{
	size_t i;

	if (c == '=')
	{
		*equal += 1;
		return (0);
	}
	i = -1;
	while (++i < 65)
	{
		if (c == g_value_base64[i])
			return (i);
	}
	return (0);
}

size_t		clean_bytes(t_data *info, char *new_str)
{
	size_t		nb_discarded_char;
	size_t		i;
	size_t		j;
	size_t		equal;
	size_t		new_len;

	i = -1;
	j = 0;
	equal = 0;
	nb_discarded_char = 0;
	while (++i < info->len)
		if (info->bytes[i] == '\n' || info->bytes[i] == '\t' ||\
			info->bytes[i] == ' ')
		{
			nb_discarded_char++;
			continue ;
		}
		else
			new_str[j++] = info->bytes[i];
	new_len = (info->len - nb_discarded_char) / 4 * 3;
	i = -1;
	while (++i < info->len)
		new_str[i] = return_value(new_str[i], &equal);
	return (new_len - equal);
}

void		base64_decode(t_data *info)
{
	size_t		new_len;
	size_t		i;
	size_t		j;
	uint32_t	intermediate;
	char		*new_str;

	new_str = ft_memalloc(info->len + 4);
	new_len = clean_bytes(info, new_str);
	i = 0;
	j = 0;
	while (j < info->len)
	{
		intermediate = SWAP_VALUE(*((uint32_t*)&new_str[j]));
		intermediate = (0x3f000000 & intermediate) >> 6 |\
		(0x3f0000 & intermediate) >> 4 |\
		(0x3f00 & intermediate) >> 2 | (0x3f & intermediate);
		new_str[i] = ((0xff0000 & intermediate)) >> 16;
		new_str[i + 1] = ((0xff00 & intermediate) >> 8);
		new_str[i + 2] = ((0xff & intermediate));
		i += 3;
		j += 4;
	}
	info->len = new_len;
	free(info->bytes);
	info->bytes = (uint8_t*)new_str;
}

void		pad_result_and_free(t_data *info, char *new_str, size_t new_len)
{
	size_t		padding;
	size_t		i;

	i = new_len;
	padding = (info->len % 3 > 0) ? 3 - info->len % 3 : 0;
	while (padding--)
		new_str[--i] = '=';
	new_str[new_len] = '\n';
	info->len = new_len + 1;
	free(info->bytes);
	info->bytes = (uint8_t*)new_str;
}

void		base64_encode(t_data *info)
{
	char		*new_str;
	size_t		new_len;
	size_t		i;
	size_t		j;
	uint32_t	intermediate;

	new_len = (info->len % 3 != 0) ? info->len / 3 * 4 + 4 : info->len / 3 * 4;
	new_str = ft_memalloc(new_len + 1);
	i = 0;
	j = 0;
	while (j < info->len)
	{
		intermediate = SWAP_VALUE(*((uint32_t*)&info->bytes[j]));
		new_str[i] = g_value_base64[((0xfc000000 & intermediate) >> 26)];
		new_str[i + 1] = g_value_base64[((0x3f00000 & intermediate) >> 20)];
		new_str[i + 2] = g_value_base64[((0xfc000 & intermediate) >> 14)];
		new_str[i + 3] = g_value_base64[((0x3f00 & intermediate) >> 8)];
		i += 4;
		j += 3;
	}
	pad_result_and_free(info, new_str, new_len);
}

void		display_base64(t_data *info, t_command *cmd)
{
	if (info != NULL && cmd != NULL)
		write(info->fd, info->bytes, info->len);
}

void		base64(t_data *info)
{
	if (info->len == 0)
		return ;
	if (info->flag & F_DECODE)
		base64_decode(info);
	else
		base64_encode(info);
}
