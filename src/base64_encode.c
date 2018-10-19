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

static void	pad_result_and_free(t_data *info, char *new_str, size_t new_len)
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
