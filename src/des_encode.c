/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_encode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 17:09:36 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/27 11:13:22 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static uint64_t		main_loop(uint64_t keys[16], uint32_t left, uint64_t right)
{
	uint64_t	tmp_right;
	uint64_t	tmp_left;
	uint64_t	d0;
	size_t		i;

	i = -1;
	while (++i < 16)
	{
		d0 = expansion(right) ^ keys[i];
		tmp_right = left ^ substitutions(d0);
		tmp_left = right;
		right = tmp_right;
		left = tmp_left;
	}
	return ((0xffffffff & left) | ((0xffffffff & right) << 32));
}

static char			*put_padding_character(t_data *info)
{
	size_t	len;
	size_t	new_len;
	char	*padded_string;

	len = info->len;
	if (len % 8)
	{
		new_len = info->len + 8 - (len % 8);
	}
	else
		new_len = info->len + 8;
	padded_string = ft_memalloc(new_len + 1);
	if (info->len == 0)
		info->bytes = ft_memalloc(8);
	ft_memset(info->bytes + len, new_len - len, new_len - len);
	info->len = new_len;
	return (padded_string);
}

void				des_ecb_encrypt(t_data *info)
{
	uint64_t	keys[16];
	size_t		i;
	char		*encrypted_string;
	uint64_t	block;
	uint64_t	old_block;

	encrypted_string = put_padding_character(info);
	i = 0;
	ft_bzero(keys, sizeof(keys));
	get_keys(keys, (char*)info->key, ft_strlen((char*)info->key));
	while (i != info->len)
	{
		old_block = SWAP_VALUE(*((uint64_t*)(info->bytes + i)));
		block = initial_permutation(old_block);
		block = main_loop(keys, (0xFFFFFFFF00000000 & block) >> 32,\
			(0xFFFFFFFF & block));
		block = SWAP_VALUE(reverse_permutation(block));
		ft_memcpy(encrypted_string + i, (char*)(&block), 8);
		i += 8;
	}
	if (info->bytes != NULL)
		free(info->bytes);
	info->bytes = (uint8_t*)encrypted_string;
	if (info->flag & F_BASE64)
		base64_encode(info);
}

void				des_cbc_encrypt(t_data *info,  uint64_t iv)
{
	uint64_t	keys[16];
	size_t		i;
	char		*encrypted_string;
	uint64_t	block;
	uint64_t	old_block;

	encrypted_string = put_padding_character(info);
	i = 0;
	ft_bzero(keys, sizeof(keys));
	get_keys(keys, (char*)info->key, ft_strlen((char*)info->key));
	while (i != info->len)
	{
		old_block = SWAP_VALUE(*((uint64_t*)(info->bytes + i)));
		old_block = iv ^ old_block;
		block = initial_permutation(old_block);
		block = main_loop(keys, (0xFFFFFFFF00000000 & block) >> 32,\
			(0xFFFFFFFF & block));
		iv = reverse_permutation(block);
		block = SWAP_VALUE(iv);
		ft_memcpy(encrypted_string + i, (char*)(&block), 8);
		i += 8;
	}
	if (info->bytes != NULL)
		free(info->bytes);
	info->bytes = (uint8_t*)encrypted_string;
	if (info->flag & F_BASE64)
		base64_encode(info);
}
