/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_encode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 17:09:36 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/26 17:12:53 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static uint64_t 	main_loop(uint64_t keys[16], uint32_t left, uint64_t right)
{
	uint64_t	subkey;
	uint64_t	exp;
	uint64_t	tmp_right;
	uint64_t	tmp_left;
	uint64_t	d0;
	uint64_t	p;
	size_t		i;

	i = -1;
	while (++i < 16)
	{
		exp = expansion(right);
		subkey = keys[i];
		d0 = exp ^ subkey;
		p = substitutions(d0);
		tmp_right = left ^ p;
		tmp_left = right;
		right = tmp_right;
		left = tmp_left;
	}
	return ((0xffffffff & left) | ((0xffffffff & right) << 32));
}

void 	des_encrypt(t_data *info)
{
	char *key = "bon";
	uint64_t keys[16];

	size_t i;
	char *encrypted_string;

	put_padding_character(info);
	encrypted_string = ft_memalloc(info->len + 1);
	i = 0;
	while (i != info->len)
	{
		ft_bzero(keys, sizeof(keys));
		get_keys(keys, key, 3);

		uint64_t block = initial_permutation(info->bytes + i);
		uint32_t left;
		uint32_t right;

		left = (0xFFFFFFFF00000000 & block) >> 32;
		right = (0xFFFFFFFF & block);
		block = main_loop(keys, left, right);
		block = reverse_permutation(block);
		char *result = (char*)(&block);
		ft_memcpy(encrypted_string + i, result, 8);
		i += 8;
	}
	info->bytes = encrypted_string;
}
