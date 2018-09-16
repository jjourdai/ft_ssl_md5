/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 12:27:25 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/12 14:39:40 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

static uint32_t g_s[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21,
};

static uint32_t g_k[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

static uint64_t	put_padding_character_md5(t_data *info)
{
	uint64_t	new_len;
	uint64_t	*ll;
	char		*new_str;

	if (info->len == 0)
		info->len = (uint64_t)ft_strlen((char*)info->bytes);
	new_len = info->len + (64 - info->len % 64);
	if (new_len - info->len < 9)
		new_len += 64;
	new_str = (char*)ft_memalloc(new_len);
	ft_memcpy(new_str, info->bytes, info->len);
	new_str[info->len] = 0x80;
	ll = (uint64_t*)new_str;
	ll[new_len / 8 - 1] = info->len * 8;
	// if (info->bytes != NULL)
	// free(info->bytes);
	info->bytes = (uint8_t*)new_str;
	return (new_len);
}

static void		compute_hash(uint32_t *current, size_t i, uint32_t *g, uint32_t *f)
{
	if (i <= 15)
	{
		*f = (current[1] & current[2]) | ((~current[1]) & current[3]);
		*g = i;
	}
	else if (i >= 16 && i <= 31)
	{
		*f = (current[3] & current[1]) | ((~current[3]) & current[2]);
		*g = (5 * i + 1) % 16;
	}
	else if (i >= 32 && i <= 47)
	{
		*f = current[1] ^ current[2] ^ current[3];
		*g = (3 * i + 5) % 16;
	}
	else if (i >= 48 && i <= 63)
	{
		*f = current[2] ^ (current[1] | (~current[3]));
		*g = (7 * i) % 16;
	}
}

static void		loop_in_current_512_bits(uint32_t *current, uint32_t *m)
{
	size_t		i;
	uint32_t	g;
	uint32_t	f;

	i = -1;
	while (++i < 64)
	{
		compute_hash(current, i, &g, &f);
		f = f + current[0] + g_k[i] + m[g];
		current[0] = current[3];
		current[3] = current[2];
		current[2] = current[1];
		current[1] = current[1] + L_ROT(f, g_s[i]);
	}
}

void			md5(t_data *info)
{
	uint32_t hash[4];
	uint64_t len;
	uint32_t *m;
	uint32_t current[4];

	len = put_padding_character_md5(info);
	m = (uint32_t*)info->bytes;
	hash[0] = 0x67452301;
	hash[1] = 0xefcdab89;
	hash[2] = 0x98badcfe;
	hash[3] = 0x10325476;
	while (len > 0)
	{
		ft_memcpy(current, hash, sizeof(current));
		loop_in_current_512_bits(current, m);
		hash[0] = hash[0] + current[0];
		hash[1] = hash[1] + current[1];
		hash[2] = hash[2] + current[2];
		hash[3] = hash[3] + current[3];
		m = m + 16;
		len -= 64;
	}
	free(info->bytes);
	ft_memcpy(info->final_hash, hash, sizeof(hash));
}
