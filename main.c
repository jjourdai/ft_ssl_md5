#include <stdint.h>
#include <stdio.h>

#define LEFT_ROTATE(X, C) ((X << C) | (X >> (32 - C)))

void print_hex(uint64_t *ptr, size_t len)
{
	size_t i;

	i = -1;
	while (++i < len)
		printf("%llu\n", ptr[i]);
}

uint64_t	swap_bigendian_littleendian(uint64_t number, size_t sizeoff)
{
	uint64_t	nb_swapped;
	int			i;
	int			j;
	int			i_max;

	if (sizeoff == 1)
		return ((number & 0xF0) >> 4 | (number & 0x0F) << 4);
	i = 0;
	j = sizeoff - 1;
	i_max = sizeoff / 2;
	nb_swapped = 0;
	while (i < i_max)
	{
		nb_swapped |= ((((size_t)0xFF << (8 * i)) & number) << (8 * (j - i)));
		nb_swapped |= ((((size_t)0xFF << (8 * j)) & number) >> (8 * (j - i)));
		i++;
		j--;
	}
	return (nb_swapped);
}

void		display_hex_md5(uint32_t a,uint32_t b,uint32_t c,uint32_t d)
{
	printf("%2.2x%2.2x%2.2x%2.2x\n",
	(uint32_t)swap_bigendian_littleendian(a, sizeof(a)),
	(uint32_t)swap_bigendian_littleendian(b, sizeof(b)),
	(uint32_t)swap_bigendian_littleendian(c, sizeof(c)),
	(uint32_t)swap_bigendian_littleendian(d, sizeof(d)));
}

static uint32_t s[64] = {
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,
};

static uint32_t k[64] = {
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

uint64_t	origin_string_to_padded_string(char **str)
{
	uint64_t len = strlen(*str);
	uint64_t new_len = len + (64 - len % 64);
	char *new_str = malloc(new_len);
	bzero(new_str, new_len);
	memcpy(new_str, *str, len);

	new_str[len] = 0x80;
	uint64_t *ll = (uint64_t*)new_str;
	ll[new_len / 8 - 1] = len * 8;
	*str = new_str;
	//dont forget to free this string;
	return (new_len);
}

void		md5(char *str)
{
	uint32_t a0 = 0x67452301;
	uint32_t b0 = 0xefcdab89;
	uint32_t c0 = 0x98badcfe;
	uint32_t d0 = 0x10325476;

	uint64_t len = origin_string_to_padded_string(&str);
	uint32_t *m = (uint32_t*)str;
	while (len > 0)
	{
	uint32_t a = a0;
	uint32_t b = b0;
	uint32_t c = c0;
	uint32_t d = d0;

	size_t i = -1;
	uint32_t f,g;
	while (++i < 64)
	{
		if (i <= 15)
		{
			f = (b & c) | ((~b) & d);
			g = i;
		}
		else if (i >= 16 && i <= 31)
		{
			f = (d & b) | ((~d) & c);
			g = (5 * i + 1) % 16;
		}
		else if (i >= 32 && i <= 47)
		{
			f = b ^ c ^ d;
			g = (3 * i + 5) % 16;
		}
		else if (i >= 48 && i <= 63)
		{
			f = c ^ (b | (~d));
			g = (7 * i) % 16;
		}
		f = f + a + k[i] + m[g];
		a = d;
		d = c;
		c = b;
		b = b + LEFT_ROTATE(f, s[i]);
	}
	a0 = a0 + a;
	b0 = b0 + b;
	c0 = c0 + c;
	d0 = d0 + d;
	m = m + 16;
	len -= 64;
	}
	display_hex_md5(a0, b0, c0, d0);
}

int main(int argc, char **argv)
{
	char *str = argv[1];
	if (str == NULL)
		return(0);
	else
		md5(str);
	return(0);
}
