/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 14:43:53 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/27 11:11:54 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static int g_cp1[] = {
	57, 49, 41, 33, 25, 17, 9, 1,
	58, 50, 42, 34, 26, 18, 10, 2,
	59, 51, 43, 35, 27, 19, 11, 3,
	60, 52, 44, 36, 63, 55, 47, 39,
	31, 23, 15, 7, 62, 54, 46, 38,
	30, 22, 14, 6, 61, 53, 45, 37,
	29, 21, 13, 5, 28, 20, 12, 4,
};

static int g_cp2[] = {
	14, 17, 11, 24, 1, 5, 3, 28,
	15, 6, 21, 10, 23, 19, 12, 4,
	26, 8, 16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55, 30, 40,
	51, 45, 33, 48, 44, 49, 39, 56,
	34, 53, 46, 42, 50, 36, 29, 32,
};

static uint64_t g_ls[] = {
	1, 1, 2, 2, 2, 2, 2, 2,
	1, 2, 2, 2, 2, 2, 2, 1,
};

uint64_t	pass_cp1(uint64_t old_block)
{
	uint64_t	block;
	int			i;

	block = 0;
	i = -1;
	while (++i < 56)
	{
		if (g_cp1[i] - i - 1 > 0)
			block |= ((1ll << (64 - g_cp1[i])) & old_block)\
				<< (g_cp1[i] - i - 1);
		else
			block |= ((1ll << (64 - g_cp1[i])) & old_block)\
				>> (i + 1 - g_cp1[i]);
	}
	block = block >> 8;
	return (block);
}

uint64_t	pass_cp2(uint64_t old_block)
{
	uint64_t	block;
	int			i;

	block = 0;
	i = -1;
	while (++i < 48)
	{
		if (g_cp2[i] - i - 1 > 0)
			block |= ((1ll << (56 - g_cp2[i])) & old_block)\
				<< (g_cp2[i] - i - 1);
		else
			block |= ((1ll << (56 - g_cp2[i])) & old_block)\
				>> (i + 1 - g_cp2[i]);
	}
	block = block >> 8;
	return (block);
}

uint64_t	split_then_pass_cp2(uint64_t keys[16], uint64_t old_block)
{
	uint64_t	block;
	uint32_t	left;
	uint32_t	right;
	size_t		i;

	block = old_block;
	left = (0xFFFFFFF0000000 & block) >> 28;
	right = (0xFFFFFFF & block);
	i = -1;
	while (++i < 16)
	{
		left = (L_ROT_28(left, g_ls[i]) & 0xFFFFFFF);
		right = (L_ROT_28(right, g_ls[i]) & 0xFFFFFFF);
		block = (0xffffffff & right) | ((0xFFFFFFFFFFFFFFFF & left) << 28);
		keys[i] = pass_cp2(block);
	}
	return (block);
}

uint64_t	*get_keys(char *key, size_t len)
{
	static uint64_t	keys[16] = {0};
	uint64_t		base_key;
	uint64_t		block;

	if (keys[0] == 0)
	{
		ft_toupper_str(key, len);
		if (len < 16)
			ft_memset(key + len, '0', SIZE_KEY - len);
		key[16] = 0;
		if (!string_is_only_hexchar(key))
			raise_error(DES, INVALID_KEY, NULL, EXIT);
		base_key = ft_hexa_to_uint64_t(key);
		block = pass_cp1(base_key);
		split_then_pass_cp2(keys, block);
	}
	return (keys);
}
