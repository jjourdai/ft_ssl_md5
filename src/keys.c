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

static int cp1[] = {
	57,	49,	41,	33,	25,	17,	9,	1,
	58, 50,	42,	34,	26,	18, 10,	2,
	59,	51, 43,	35,	27,	19,	11,	3,
	60,	52,	44,	36, 63,	55,	47,	39,
	31,	23,	15,	7, 62, 54, 46, 38,
	30,	22, 14,	6,	61, 53, 45, 37,
	29,	21,	13,	5,	28,	20,	12,	4,
};

static int cp2[] = {
	14, 17,	11,	24,	1,	5,	3,	28,
	15,	6,	21,	10, 23,	19,	12,	4,
	26,	8,	16,	7,	27,	20,	13,	2,
	41,	52,	31,	37,	47,	55,	30,	40,
	51,	45,	33,	48, 44,	49,	39,	56,
	34,	53,	46,	42,	50,	36,	29,	32,
};

static uint64_t ls[] = {
	1, 1, 2, 2, 2, 2, 2, 2,
	1, 2, 2, 2, 2, 2, 2, 1,
};

uint64_t 	pass_cp1(uint64_t old_block)
{
	uint64_t	block;

	block = 0;
	for (int i = 0; i < 56; i++)
	{
		if (cp1[i] - i - 1 > 0)
			block |= ((1ll << (64 - cp1[i])) & old_block) << (cp1[i] - i - 1);
		else
			block |= ((1ll << (64 - cp1[i])) & old_block) >> (i + 1 - cp1[i]);
		// ft_printf("%d", ((1ll << (64 - cp1[i])) & old_block) ? 1 : 0);
	}
	block = block >> 8;
	return (block);
}

uint64_t 	pass_cp2(uint64_t old_block)
{
	uint64_t	block;

	block = 0;
	for (int i = 0; i < 48; i++)
	{
		if (cp2[i] - i - 1 > 0)
			block |= ((1ll << (56 - cp2[i])) & old_block) << (cp2[i] - i - 1);
		else
			block |= ((1ll << (56 - cp2[i])) & old_block) >> (i + 1 - cp2[i]);
		// ft_printf("%d", ((1ll << (64 - cp1[i])) & old_block) ? 1 : 0);
	}
	block = block >> 8;
	return (block);
}

uint64_t	split_then_pass_cp2(uint64_t keys[16], uint64_t old_block)
{
	uint64_t	block;
	uint32_t	left;
	uint32_t	right;
	size_t 		i;

	block = old_block;
	left = (0xFFFFFFF0000000 & block) >> 28;
	right = (0xFFFFFFF & block);
	i = -1;
	while (++i < 16)
	{
		left = (L_ROT_28(left, ls[i]) & 0xFFFFFFF);
		right = (L_ROT_28(right, ls[i]) & 0xFFFFFFF);
		// ft_printf("C = %028llb\n", left);
		// ft_printf("D = %028llb\n\n", right);
		block = (0xffffffff & right) | ((0xFFFFFFFFFFFFFFFF & left) << 28);
		keys[i] = pass_cp2(block);
		// ft_printf("%048llb\n", keys[i]);
	}
	return (block);
}

void	get_keys(uint64_t keys[16], char *key, size_t len)
{
	uint64_t	base_key;
	uint64_t	block;
	size_t		len_key;

	if (key == NULL)
	{
		ft_fprintf(STDERR_FILENO, "ft_ssl des: key == NULLL\n");
			exit(-1);
	}
	if ((len_key = ft_strlen(key)) > 16)
		key[16] = 0;
	else if (len_key < 16)
	{
		ft_memset(key + len_key, '0', SIZE_KEY - len_key);
		key[16] = 0;
	}
	if (!(base_key = ft_atoi_base_64(key, "0123456789ABCDEF")))
	{
		ft_fprintf(STDERR_FILENO, "ft_ssl des: non-hex digit\n"
			"invalid hex key value");
			exit(-1);
	}
	block = pass_cp1(base_key);
	split_then_pass_cp2(keys, block);
	// ft_printf("%056llb\n", block);
}
