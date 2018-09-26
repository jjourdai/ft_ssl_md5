/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 14:43:53 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/22 18:43:14 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void	display_des(t_data *info, t_command *cmd)
{
	write(info->fd, info->bytes, info->len);
}

// void run_des_parameters_and_exec(t_command *cmd, t_list *parameters, int opt_flag)
// {
// 	t_list			*tmp;
// 	t_parameters	*current;
// 	t_data	target;
//
// 	tmp = parameters;
// 	target.param_type = STDIN_;
// 	while (tmp)
// 	{
// 		/*
// 		ft_bzero(&target, sizeof(t_data));
// 		current = (t_parameters*)tmp->content;
// 		if (current->type == F_STRING)
// 		{
// 			target.bytes = (uint8_t*)current->str;
// 			target.param_type = STRING_;
// 			target.string = (uint8_t*)current->str;
// 		}
// 		else
// 		{
// 			target.string = (uint8_t*)current->str;
// 			target.param_type = FILE_;
// 		}
// 		exec_command(&target, cmd, opt_flag);
// 		tmp = tmp->next;
// 		*/
// 	}
// 	if (parameters == NULL)
// 		exec_read_stdin(cmd, opt_flag);
// 	ft_lstdel(&parameters, ft_del);
// }

static void		fill_target_struct(t_data *target, t_list *parameters, int opt_flag)
{
	t_list			*tmp;
	t_parameters	*current;

	tmp = parameters;
	target->param_type = STDIN_;
	while (tmp)
	{
		current = (t_parameters*)tmp->content;
		if (current->type == F_OUPUT)
			target->fd = open(current->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (current->type == F_INPUT || current->type == NONE_)
		{
			target->param_type = FILE_;
			target->string = current->str;
		}
		tmp = tmp->next;
	}
	ft_lstdel(&parameters, ft_del);
}

void 				run_des_parameters_and_exec(t_command *cmd, t_list *parameters, int opt_flag)
{
	t_data target;

	ft_bzero(&target, sizeof(target));
	target.fd = STDOUT_FILENO;
	fill_target_struct(&target, parameters, opt_flag);
	if (target.param_type == STDIN_)
		exec_read_stdin(cmd, opt_flag);
	else
		exec_command(&target, cmd, opt_flag);
	if (target.fd != STDOUT_FILENO && target.fd != -1)
		close(target.fd);
}


static const int ip[] = {
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

uint64_t	initial_permutation(char *bytes)
{
	uint64_t	old_block;
	uint64_t	new_block;
	uint64_t	block;


	new_block = 0;
	old_block = *((uint64_t*)bytes);
	// old_block = 0x0123456789ABCDEF;
	// old_block = 0x85e813540f0ab405;
	// old_block = 0xfe518bb41c352ee4;


	block = 0;
	for (int i = 0; i < 64; i++)
	{
		if (ip[i] - i - 1 > 0)
			block |= ((1ll << (64 - ip[i])) & old_block) << (ip[i] - i - 1);
		else
			block |= ((1ll << (64 - ip[i])) & old_block) >> (i + 1 - ip[i]);
	}
	// ft_printf("%064llb\n", block);
	return (block);
}

static const int exp[] = {
	32,	1,	2,	3,	4,	5,
	4,	5,	6,	7,	8,	9,
	8,	9,	10,	11,	12,	13,
	12,	13,	14,	15,	16,	17,
	16,	17,	18,	19,	20,	21,
	20,	21,	22,	23,	24,	25,
	24,	25,	26,	27,	28,	29,
	28,	29,	30,	31,	32,	1,
};

uint64_t	expansion(uint32_t bytes)
{
	uint64_t	block;

	block = 0;
	for (int i = 0; i < 48; i++)
	{
		if (exp[i] - i - 1 > 0)
			block |= (((1ll << (32 - exp[i])) & bytes) << 16) << (exp[i] - i - 1);
		else
			block |= (((1ll << (32 - exp[i])) & bytes) << 16) >> (i + 1 - exp[i]);
		// ft_printf("%d", ((1ll << (32 - exp[i])) & bytes) ? 1 : 0);
	}
	return (block);
}

static int substitutions_value[][4][16] = {
	[0] = {
		[0] = {14,	4,	13,	1,	2,	15,	11,	8,	3,	10,	6,	12,	5,	9,	0,	7},
		[1] = {0,	15,	7,	4,	14,	2,	13,	1,	10,	6,	12,	11,	9,	5,	3,	8},
		[2] = {4,	1,	14,	8,	13,	6,	2,	11,	15,	12,	9,	7,	3,	10,	5,	0},
		[3] = {15,	12,	8,	2,	4,	9,	1,	7,	5,	11,	3,	14,	10,	0,	6,	13},
	},
	[1] = {
		[0] = {15,	1,	8,	14,	6,	11,	3,	4,	9,	7,	2,	13,	12,	0,	5,	10},
		[1] = {3,	13,	4,	7,	15,	2,	8,	14,	12,	0,	1,	10,	6,	9,	11,	5},
		[2] = {0,	14,	7,	11,	10,	4,	13,	1,	5,	8,	12,	6,	9,	3,	2,	15},
		[3] = {13,	8,	10,	1,	3,	15,	4,	2,	11,	6,	7,	12,	0,	5,	14,	9},
	},
	[2] = {
		[0] = {10,	0,	9,	14,	6,	3,	15,	5,	1,	13,	12,	7,	11,	4,	2,	8},
		[1] = {13,	7,	0,	9,	3,	4,	6,	10,	2,	8,	5,	14,	12,	11,	15,	1},
		[2] = {13,	6,	4,	9,	8,	15,	3,	0,	11,	1,	2,	12,	5,	10,	14,	7},
		[3] = {1,	10,	13,	0,	6,	9,	8,	7,	4,	15,	14,	3,	11,	5,	2,	12},
	},
	[3] = {
		[0] = {7,	13,	14,	3,	0,	6,	9,	10,	1,	2,	8,	5,	11,	12,	4,	15},
		[1] = {13,	8,	11,	5,	6,	15,	0,	3,	4,	7,	2,	12,	1,	10,	14,	9},
		[2] = {10,	6,	9,	0,	12,	11,	7,	13,	15,	1,	3,	14,	5,	2,	8,	4},
		[3] = {3,	15,	0,	6,	10,	1,	13,	8,	9,	4,	5,	11,	12,	7,	2,	14},
	},
	[4] = {
		[0] = {2,	12,	4,	1,	7,	10,	11,	6,	8,	5,	3,	15,	13,	0,	14,	9},
		[1] = {14,	11,	2,	12,	4,	7,	13,	1,	5,	0,	15,	10,	3,	9,	8,	6},
		[2] = {4,	2,	1,	11,	10,	13,	7,	8,	15,	9,	12,	5,	6,	3,	0,	14},
		[3] = {11,	8,	12,	7,	1,	14,	2,	13,	6,	15,	0,	9,	10,	4,	5,	3},
	},
	[5] = {
		[0] = {12,	1,	10,	15,	9,	2,	6,	8,	0,	13,	3,	4,	14,	7,	5,	11},
		[1] = {10,	15,	4,	2,	7,	12,	9,	5,	6,	1,	13,	14,	0,	11,	3,	8},
		[2] = {9,	14,	15,	5,	2,	8,	12,	3,	7,	0,	4,	10,	1,	13,	11,	6},
		[3] = {4,	3,	2,	12,	9,	5,	15,	10,	11,	14,	1,	7,	6,	0,	8,	13},
	},
	[6] = {
		[0] = {4,	11,	2,	14,	15,	0,	8,	13,	3,	12,	9,	7,	5,	10,	6,	1},
		[1] = {13,	0,	11,	7,	4,	9,	1,	10,	14,	3,	5,	12,	2,	15,	8,	6},
		[2] = {1,	4,	11,	13,	12,	3,	7,	14,	10,	15,	6,	8,	0,	5,	9,	2},
		[3] = {6,	11,	13,	8,	1,	4,	10,	7,	9,	5,	0,	15,	14,	2,	3,	12},
	},
	[7] = {
		[0] = {13,	2,	8,	4,	6,	15,	11,	1,	10,	9,	3,	14,	5,	0,	12,	7},
		[1] = {1,	15,	13,	8,	10,	3,	7,	4,	12,	5,	6,	11,	0,	14,	9,	2},
		[2] = {7,	11,	4,	1,	9,	12,	14,	2,	0,	6,	10,	13,	15,	3,	5,	8},
		[3] = {2,	1,	14,	7,	4,	10,	8,	13,	15,	12,	9,	0,	3,	5,	6,	11},
	},
};


static const int perm[] = {
	16,	7,	20,	21,	29,	12,	28,	17,
	1,	15,	23,	26,	5,	18,	31,	10,
	2,	8,	24,	14,	32,	27,	3,	9,
	19,	13,	30,	6,	22,	11,	4,	25,
};

uint64_t substitutions(uint64_t d0)
{
	//int test = 0x2e;
	//int test = value & 0x3f;
	int line;
	int col;
	uint32_t value;
	uint32_t new_value;
	size_t i;
	new_value = 0;
	i = -1;
	uint64_t padding = 0xFC0000000000;
	// ft_printf("%llx\n", d0);
	while (++i < 8)
	{
		// ft_printf("--->>>>>>>>>>>%llx\n", (padding & d0));
		value = (padding & d0) >> ((7 - i) * 6);
		padding = padding >> 6;
		line = ((1 << 5) & value) >> 4 | (1 & value);
		col = (0x1e & value) >> 1;
		new_value |= (substitutions_value[i][line][col]);
		if (i != 7)
			new_value = new_value << 4;
		// ft_printf("%lld %d %llb\n", value, i, new_value);
	}
	// tour 1 11110010011110110010010011000101
	// ft_printf("new value %032llb\n", new_value);
	uint64_t	block;

	block = 0;
	for (int i = 0; i < 32; i++)
	{
		if (perm[i] - i - 1 > 0)
			block |= ((1ll << (32 - perm[i])) & new_value) << (perm[i] - i - 1);
		else
			block |= ((1ll << (32 - perm[i])) & new_value) >> (i + 1 - perm[i]);
	}
	// ft_printf("permuted value = %032llb\n", block);
	return (block);

}

uint64_t 	main_loop(uint64_t keys[16], uint32_t left, uint64_t right)
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
		// ft_putendl("==========================");
		exp = expansion(right);
		// ft_printf("expansion %048llb\n", exp);
		subkey = keys[i];
		// ft_printf("subkey %048llb\n", subkey);
		d0 = exp ^ subkey;
		// ft_printf("subkey %llx\n", subkey);
		p = substitutions(d0);
		// ft_printf("PPP %032llb\n", p);
		tmp_right = left ^ p;
		tmp_left = right;
		right = tmp_right;
		left = tmp_left;
		// ft_printf("right1 %032llb\n", right);
		// ft_printf("left1 %032llb\n", left);
		// ft_putendl("==========================");
		// if (4 == i)
		// 	break ;
	}
	return ((0xffffffff & left) | ((0xffffffff & right) << 32));
}

static const int ipr[] = {
	40,	8,	48,	16,	56,	24,	64,	32,
	39,	7,	47,	15,	55,	23,	63,	31,
	38,	6,  46,	14,	54,	22,	62,	30,
	37,	5,	45,	13,	53,	21,	61,	29,
	36,	4,	44,	12,	52,	20,	60,	28,
	35,	3,	43,	11,	51,	19,	59,	27,
	34,	2,	42,	10,	50,	18,	58,	26,
	33,	1,	41,	9,	49,	17,	57,	25,
};

uint64_t reverse_permutation(uint64_t old_block)
{
	uint64_t block;

	block = 0;
	for (int i = 0; i < 64; i++)
	{
		if (ipr[i] - i - 1 > 0)
			block |= ((1ll << (64 - ipr[i])) & old_block) << (ipr[i] - i - 1);
		else
			block |= ((1ll << (64 - ipr[i])) & old_block) >> (i + 1 - ipr[i]);
	}
	return (block);
}

void put_padding_character(t_data *info)
{
	if (info->len % 8)
		info->len += 8 - (info->len % 8);
}

void 	des_encrypt(t_data *info)
{
	char *key = "bon";
	uint64_t keys[16];

	size_t i;
	// size_t len = ft_strlen("exemple de cryptage en D");
	char *encrypted_string;

	// ft_printf("%lld\n", info->len);
	// ft_putendl(info->bytes);
	put_padding_character(info);
	encrypted_string = ft_memalloc(info->len + 1);
	i = 0;
	while (i != info->len)
	{
		ft_bzero(keys, sizeof(keys));
		get_keys(keys, key, 3);
		// char *string = "exemple de cryptage en D";

		uint64_t block = initial_permutation(info->bytes + i);
		uint32_t left;
		uint32_t right;

		left = (0xFFFFFFFF00000000 & block) >> 32;
		right = (0xFFFFFFFF & block);
		block = main_loop(keys, left, right);
		// ft_printf("bef ipr = %064llb\n", block);
		block = reverse_permutation(block);
		char *result = (char*)(&block);
		// ft_printf("result = %064llb\n", block);
		// ft_printf("result = %llx\n", block);
		// ft_putendl(result);
		ft_memcpy(encrypted_string + i, result, 8);
		i += 8;
	}
	info->bytes = encrypted_string;
	// write(1, encrypted_string, info->len);
}

uint64_t 	main_loop_reverse(uint64_t keys[16], uint32_t left, uint64_t right)
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
		// ft_putendl("==========================");
		exp = expansion(right);
		// ft_printf("expansion %048llb\n", exp);
		subkey = keys[i];
		// ft_printf("subkey %048llb\n", subkey);
		d0 = exp ^ subkey;
		// ft_printf("subkey %llx\n", subkey);
		p = substitutions(d0);
		// ft_printf("PPP %032llb\n", p);
		tmp_right = left ^ p;
		tmp_left = right;
		right = tmp_right;
		left = tmp_left;
		// ft_printf("right1 %032llb\n", right);
		// ft_printf("left1 %032llb\n", left);
		// ft_putendl("==========================");
		if (i-- == 0)
			break ;
	}
	return ((0xffffffff & left) | ((0xffffffff & right) << 32));
}

void 	des_decrypt(t_data *info)
{
	char *key = "bon";
	uint64_t keys[16];

	size_t i;
	// size_t len = ft_strlen("exemple de cryptage en D");
	char *encrypted_string;

	// ft_printf("%lld\n", info->len);
	// ft_putendl(info->bytes);
	put_padding_character(info);
	encrypted_string = ft_memalloc(info->len + 1);
	i = 0;
	while (i != info->len)
	{
		ft_bzero(keys, sizeof(keys));
		get_keys(keys, key, 3);
		// char *string = "exemple de cryptage en D";

		uint64_t block = initial_permutation(info->bytes + i);
		uint32_t left;
		uint32_t right;

		left = (0xFFFFFFFF00000000 & block) >> 32;
		right = (0xFFFFFFFF & block);
		block = main_loop_reverse(keys, left, right);
		// ft_printf("bef ipr = %064llb\n", block);
		block = reverse_permutation(block);
		char *result = (char*)(&block);
		// ft_printf("result = %064llb\n", block);
		// ft_printf("result = %llx\n", block);
		// ft_putendl(result);
		ft_memcpy(encrypted_string + i, result, 8);
		i += 8;
	}
	info->bytes = encrypted_string;
}
void 	des(t_data *info)
{
	if (info->flag & F_DECRYPT)
	{
		des_decrypt(info);
	}
	else if (info->flag & F_ENCRYPT)
	{
		des_encrypt(info);
	}
}











//
