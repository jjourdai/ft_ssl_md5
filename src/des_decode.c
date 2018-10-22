/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_decode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 17:13:41 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/26 17:14:24 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static uint64_t		main_loop_reverse(uint64_t keys[16], uint32_t left,\
	uint64_t right)
{
	uint64_t	exp;
	uint64_t	tmp_left;
	uint64_t	d0;
	size_t		i;

	i = 15;
	while (1)
	{
		exp = expansion(right);
		d0 = exp ^ keys[i];
		tmp_left = right;
		right = left ^ substitutions(d0);
		left = tmp_left;
		if (i-- == 0)
			break ;
	}
	return ((0xffffffff & left) | ((0xffffffff & right) << 32));
}

void				des_ecb_decrypt(t_data *info)
{
	size_t		i;
	char		*encrypted_string;
	uint64_t	block;
	uint64_t	old_block;
	uint64_t	keys[16];

	get_keys(keys, (char*)info->key, ft_strlen((char*)info->key));
	encrypted_string = ft_memalloc(info->len);
	i = 0;
	while (i != info->len)
	{
		old_block = SWAP_VALUE(*((uint64_t*)(info->bytes + i)));
		block = initial_permutation(old_block);
		block = main_loop_reverse(keys, (0xFFFFFFFF00000000 & block)\
			>> 32, (0xFFFFFFFF & block));
		block = SWAP_VALUE(reverse_permutation(block));
		ft_memcpy(encrypted_string + i, (char*)(&block), 8);
		i += 8;
	}
	if (info->bytes != NULL)
		free(info->bytes);
	info->bytes = (uint8_t*)encrypted_string;
}

uint64_t			update_block_cbc_decrypt(uint64_t keys[16],\
	uint64_t iv, uint64_t old_block)
{
	uint64_t	block;
	uint64_t	intermediate;

	block = initial_permutation(old_block);
	block = main_loop_reverse(keys, (0xFFFFFFFF00000000 & block)\
		>> 32, (0xFFFFFFFF & block));
	intermediate = reverse_permutation(block) ^ iv;
	return (intermediate);
}

void				des_cbc_decrypt(t_data *info, uint64_t iv)
{
	size_t		i;
	char		*encrypted_string;
	uint64_t	block;
	uint64_t	old_block;
	uint64_t	keys[16];

	get_keys(keys, (char*)info->key, ft_strlen((char*)info->key));
	encrypted_string = ft_memalloc(info->len + 8);
	i = 0;
	while (i != info->len)
	{
		old_block = SWAP_VALUE(*((uint64_t*)(info->bytes + i)));
		block = update_block_cbc_decrypt(keys, iv, old_block);
		iv = old_block;
		block = SWAP_VALUE(block);
		ft_memcpy(encrypted_string + i, (char*)(&block), 8);
		i += 8;
	}
	if (info->bytes != NULL)
		free(info->bytes);
	info->bytes = (uint8_t*)encrypted_string;
}
