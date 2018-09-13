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

static void		display_hex_sha256(uint32_t bytes[8])
{
//some problems with my ft_printf
	size_t i;
	i = -1;
	while (++i < 8)
		printf("%8.8x", bytes[i]);
	printf("\n");
}

static uint64_t	put_padding_character_sha256(char **str)
{
	uint64_t	len;
	uint64_t	new_len;
	uint64_t	*ll;
	char		*new_str;

	len = (uint64_t)ft_strlen(*str);
	new_len = len + (64 - len % 64);
	if (new_len - len < 9)
		new_len += 64;
	new_str = ft_memalloc(new_len);
	size_t i;
	memcpy(new_str, *str, len);
	new_str[len] = 0x80;
	i = -1;
	ll = (uint64_t*)new_str;
	ll[new_len / 8 - 1] = SWAP_VALUE(len * 8);
	*str = new_str;
	return (new_len);
}

static void 	prepare_message_schedule(uint8_t *msg, uint32_t *w)
{
	size_t i;
	size_t j;
	uint32_t st0;
	uint32_t st1;

	i = -1;
	j = 0;
	ft_bzero(w, sizeof(w));
	while (++i < 16)
	{
		w[i] = ((msg[j]) << 24) | ((msg[j + 1]) << 16) | \
			((msg[j + 2]) << 8) | ((msg[j + 3]));
		j += 4;
	}
	i = 15;
	while (++i < 64)
	{
		st0 =  (R_ROT(w[i - 15], 7)) ^ (R_ROT(w[i - 15], 18)) ^\
			(w[i - 15] >> 3);
		st1 =  (R_ROT(w[i - 2], 17)) ^ (R_ROT(w[i - 2], 19)) ^\
			(w[i - 2] >> 10);
		w[i] = w[i - 16] + st0 + w[i - 7] + st1;
	}
}

static void compute_inter_hash(uint32_t *w, uint32_t *inter_hash)
{
	size_t i;
	uint32_t temp1;
	uint32_t temp2;

	i = -1;
	while (++i < 64)
	{
		temp1 = inter_hash[7] + S1(inter_hash) + CH(inter_hash) + k[i] + w[i];
		temp2 = S0(inter_hash) + MAJ(inter_hash);
		inter_hash[7] = inter_hash[6];
		inter_hash[6] = inter_hash[5];
		inter_hash[5] = inter_hash[4];
		inter_hash[4] = inter_hash[3] + temp1;
		inter_hash[3] = inter_hash[2];
		inter_hash[2] = inter_hash[1];
		inter_hash[1] = inter_hash[0];
		inter_hash[0] = temp1 + temp2;
	}
}

static void 	update_hash(uint32_t hash[8], uint32_t inter_hash[8])
{
	hash[0] += inter_hash[0];
	hash[1] += inter_hash[1];
	hash[2] += inter_hash[2];
	hash[3] += inter_hash[3];
	hash[4] += inter_hash[4];
	hash[5] += inter_hash[5];
	hash[6] += inter_hash[6];
	hash[7] += inter_hash[7];
}

void	sha256(char *str)
{
	uint32_t	inter_hash[8] = {0};
	uint64_t	len;
	uint32_t	w[64] = {0};
	uint8_t		*bytes_string;
	uint32_t	hash[8] = {
		0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
		0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
	};

	len = put_padding_character_sha256(&str);
  bytes_string = (uint8_t*)str;
	while (len > 0)
	{
		ft_memcpy(inter_hash, hash, sizeof(hash));
		prepare_message_schedule(bytes_string, w);
		compute_inter_hash(w, inter_hash);
		update_hash(hash, inter_hash);
		bytes_string += 64;
		len -= 64;
	}
	display_hex_sha256(hash);
	free(str);
}
