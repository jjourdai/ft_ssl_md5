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

static uint64_t 	main_loop_reverse(uint64_t keys[16], uint32_t left, uint64_t right)
{
	uint64_t	subkey;
	uint64_t	exp;
	uint64_t	tmp_right;
	uint64_t	tmp_left;
	uint64_t	d0;
	uint64_t	p;
	size_t		i;

	i = 15;
	while (1)
	{
		exp = expansion(right);
		subkey = keys[i];
		d0 = exp ^ subkey;
		p = substitutions(d0);
		tmp_right = left ^ p;
		tmp_left = right;
		right = tmp_right;
		left = tmp_left;
		if (i-- == 0)
			break ;
	}
	return ((0xffffffff & left) | ((0xffffffff & right) << 32));
}

void 	check_if_corrupted(t_data *info)
{
	if (info->len % 8)
		raise_error(DES_ECB, WRONG_LENGTH, NULL, EXIT);
}

void 	check_if_corrupted_padding_after_decrypt(t_data *info)
{
	char *ptr;
	size_t	i;
	uint32_t value;
	uint32_t previous_value;
	uint32_t quantity;

	ptr = info->bytes + info->len;
	i = 0;
	quantity = 0;
	previous_value = 0;
	while (++i < 9)
	{
		value = *(ptr - i);
		// ft_printf("%d %d\n", previous_value, value);
		if (previous_value != 0 && value != previous_value)
		{
			if (previous_value != quantity)
			{
				raise_error(DES_ECB, WRONG_LENGTH, NULL, EXIT);
			}
			else
				break ;
		}
		previous_value = value;
		quantity++;
	}
	info->len = info->len - quantity;
}

void 	des_decrypt(t_data *info)
{
	uint64_t keys[16];
	size_t i;
	char *encrypted_string;

	if (info->flag & F_BASE64)
		base64_decode(info);

	// write(1, info->bytes, info->len);
	//rajouter une fonction ici pour generer la clef si info->key == NULL
	check_if_corrupted(info);
	encrypted_string = ft_memalloc(info->len + 1);
	i = 0;
	ft_bzero(keys, sizeof(keys));
	get_keys(keys, info->key, ft_strlen(info->key));
	while (i != info->len)
	{
		uint64_t block = initial_permutation(info->bytes + i);
		uint32_t left;
		uint32_t right;
		left = (0xFFFFFFFF00000000 & block) >> 32;
		right = (0xFFFFFFFF & block);
		block = main_loop_reverse(keys, left, right);
		block = SWAP_VALUE(reverse_permutation(block));
		char *result = (char*)(&block);
		ft_memcpy(encrypted_string + i, result, 8);
		i += 8;
	}
	// if (info->bytes != NULL && (info->param_type == FILE_ ||\
	// 	info->param_type == STDIN_))
	if (info->bytes != NULL)
		free(info->bytes);
	info->bytes = encrypted_string;
	check_if_corrupted_padding_after_decrypt(info);
}
