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

void				check_if_corrupted(int cmd, t_data *info)
{
	if (info->len % 8)
		raise_error(cmd, WRONG_LENGTH, NULL, EXIT);
}

void			check_if_corrupted_padding_after_decrypt(t_data *info)
{
	unsigned char		*ptr;
	size_t		i;
	uint32_t	value;
	uint32_t	previous_value;
	uint32_t	quantity;

	ptr = (unsigned char*)info->bytes + info->len;
	quantity = 0;
	previous_value = 0;
	i = *(ptr - 1);
	while (i)
	{
		value = *(ptr - i);
		if (previous_value != 0 && value != previous_value)
		{
			if (previous_value != quantity)
				raise_error(DES_ECB, WRONG_LENGTH, NULL, EXIT);
			else
				break ;
		}
		previous_value = value;
		quantity++;
		i--;
	}
	info->len = info->len - quantity;
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

uint64_t			update_block_cbc_decrypt(t_data *info, uint64_t keys[16], uint64_t iv, uint64_t old_block)
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
		block = update_block_cbc_decrypt(info, keys, iv, old_block);
		iv = old_block;
		block = SWAP_VALUE(block);
		ft_memcpy(encrypted_string + i, (char*)(&block), 8);
		i += 8;
	}
	if (info->bytes != NULL)
		free(info->bytes);
	info->bytes = (uint8_t*)encrypted_string;
}

void				des3_decrypt(t_data *info, uint64_t iv, char *decrypted_string)
{
	uint64_t keys1[16];
	uint64_t keys2[16];
	uint64_t keys3[16];

	// ft_putendl_fd((char*)info->key, 2);
	// ft_putendl_fd((char*)info->key + DES_KEY_LEN, 2);
	// ft_putendl_fd((char*)info->key + DES_KEY_LEN * 2, 2);

	get_keys(keys3, (char*)info->key + DES_KEY_LEN * 2, DES_KEY_LEN);
	get_keys(keys2, (char*)info->key + DES_KEY_LEN, DES_KEY_LEN);
	get_keys(keys1, (char*)info->key, DES_KEY_LEN);

	size_t		i;
	uint64_t	block;
	uint64_t	old_block;

	i = 0;
	while (i != info->len)
	{
		old_block = SWAP_VALUE(*((uint64_t*)(info->bytes + i)));
		block = update_block_cbc_decrypt(info, keys3, iv, old_block);
		block = update_block_cbc_encrypt(info, keys2, iv, block);
		block = update_block_cbc_decrypt(info, keys1, iv, block);
		iv = old_block;
		block = SWAP_VALUE(block);
		ft_memcpy(decrypted_string + i, (char*)(&block), 8);
		i += 8;
	}
	if (info->bytes != NULL)
		free(info->bytes);
	info->bytes = (uint8_t*)decrypted_string;
}