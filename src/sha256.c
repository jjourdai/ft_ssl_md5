/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:23:23 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/12 19:09:30 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"


uint32_t k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void		display_hex_sha256(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f, uint32_t g, uint32_t h)
{
//some problems with my ft_printf
	printf("%8.8x%8.8x%8.8x%8.8x%8.8x%8.8x%8.8x%8.8x\n",
	(uint32_t)a,
	(uint32_t)b,
	(uint32_t)c,
	(uint32_t)c,
	(uint32_t)c,
	(uint32_t)c,
	(uint32_t)c,
	(uint32_t)c);
}

static uint64_t	origin_string_to_padded_string(char **str)
{
	uint64_t	len;
	uint64_t	new_len;
	uint64_t	*ll;
	char		*new_str;

	len = (uint64_t)ft_strlen(*str);
	new_len = len + (64 - len % 64);
	if (new_len - len < 9)
		new_len += 64;
	new_str = (char*)ft_memalloc(new_len);

	size_t i;
	memcpy(new_str, *str, len);
	new_str[len] = 0x80;
	i = -1;
	uint32_t *cast = (uint32_t*)new_str;
	ll = (uint64_t*)new_str;
	ll[new_len / 8 - 1] = SWAP_VALUE(len * 8);
	*str = new_str;
	i = -1;
	while (++i < new_len / 4)
	{
		cast[i] = SWAP_VALUE(cast[i]);
		printf("%8.8llx\n", cast[i]);
	}
	return (new_len);
}

void	sha256(char *str)
{
	uint32_t h0 = 0x6a09e667;
	uint32_t h1 = 0xbb67ae85;
	uint32_t h2 = 0x3c6ef372;
	uint32_t h3 = 0xa54ff53a;
	uint32_t h4 = 0x510e527f;
	uint32_t h5 = 0x9b05688c;
	uint32_t h6 = 0x1f83d9ab;
	uint32_t h7 = 0x5be0cd19;

	uint64_t len;
	uint32_t *m;

	len = origin_string_to_padded_string(&str);

	m = (uint32_t*)str;
	while (len > 0)
	{
		uint32_t a = h0;
		uint32_t b = h1;
		uint32_t c = h2;
		uint32_t d = h3;
		uint32_t e = h4;
		uint32_t f = h5;
		uint32_t g = h6;
		uint32_t h = h7;
		size_t i;
		int32_t w[64] = {0};
		i = -1;
		int j = 0;
		while (++i < 16)
		{
			w[i] = m[i];
		}
		//ft_bzero(w, 64);
		//ft_memcpy(w, m, 16);
		i = 15;
		while (++i < 64)
		{
			uint32_t st0 =  (RIGHT_ROTATE(w[i - 15], 7)) ^ (RIGHT_ROTATE(w[i - 15], 18)) ^ (w[i - 15] >> 3);
			uint32_t st1 =  (RIGHT_ROTATE(w[i - 2], 17)) ^ (RIGHT_ROTATE(w[i - 2], 19)) ^ (w[i - 2] >> 10);
			w[i] = w[i - 16] + st0 + w[i - 7] + st1;
		}
		i = -1;
		while (++i < 64)
		{
			uint32_t s1 = (RIGHT_ROTATE(e, 6)) ^ (RIGHT_ROTATE(e, 11)) ^ (RIGHT_ROTATE(e, 25));
			uint32_t ch = (e & f) ^ ((~e) & g);
			uint32_t temp1 = h + s1 + ch + k[i] + w[i];
			uint32_t s0 = (RIGHT_ROTATE(a, 2)) ^ (RIGHT_ROTATE(a, 13)) ^ (RIGHT_ROTATE(a, 22));
			uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
			uint32_t temp2 = s0 + maj;
			h = g;
			g = f;
			f = e;
			e = d + temp1;
			d = c;
			c = b;
			b = a;
			a = temp1 + temp2;
		}
		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;
		h4 += e;
		h5 += f;
		h6 += g;
		h7 += h;
		//========================
		m = m + 16;
		len -= 64;
	}
	display_hex_sha256(h0,h1,h2,h3,h4,h5,h6,h7);
	free(str);
}
