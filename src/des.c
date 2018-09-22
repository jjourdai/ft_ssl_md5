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


}

void run_des_parameters_and_exec(t_command *cmd, t_list *parameters, int opt_flag)
{
	t_list			*tmp;
	t_parameters	*current;
	t_data	target;

	tmp = parameters;	
	target.param_type = STDIN_;
	while (tmp)
	{
		/*
		ft_bzero(&target, sizeof(t_data));
		current = (t_parameters*)tmp->content;
		if (current->type == F_STRING)
		{
			target.bytes = (uint8_t*)current->str;
			target.param_type = STRING_;
			target.string = (uint8_t*)current->str;
		}
		else
		{
			target.string = (uint8_t*)current->str;
			target.param_type = FILE_;
		}
		exec_command(&target, cmd, opt_flag);
		tmp = tmp->next;
		*/
	}
	if (parameters == NULL)
		exec_read_stdin(cmd, opt_flag);
	ft_lstdel(&parameters, ft_del);


}

static int initial_permutation[] = {
	58, 50, 42, 34, 26, 18, 10, 2, // 2 
	60, 52, 44, 36, 28, 20, 12, 4, // 4
	62, 53, 46, 38, 30, 22, 14, 6, // 6
	64, 56, 48, 40, 32, 24, 16, 8, // 8
	57, 49, 41, 33, 25, 17, 9, 1, //  1
	59, 51, 43, 35, 27, 19, 11, 3, // 3
	61, 53, 45, 37, 29, 21, 13, 5, // 5
	63, 55, 47, 39, 31, 23, 15, 7 //  7
};

void	padding_on_key(char *key, size_t len)
{

}

void 	des(t_data *info)
{
	/*
	char *string = "bon";
	block = (uint32_t*)string;
	for (int i = 0; i < 8; i++)
		ft_printf("%08b", string[i]);
	*/

	uint32_t *block;
	char *string = "exemple de cryptage en DES";
	block = (uint32_t*)string;
	char string_modify[8] = {0};
	for (int i = 0; i < 8; i++)
		ft_printf("%08b", string[i]);

	block = (uint64_t*)string_modify;
	for (int i = 0; i < 64; i++)
	{
		*block |= (1 << i & *((uint64_t*)string)) << 58;
	}

	//(1 << 0) | (1 << 8) | (1 << 16) | (1 << 24) | (1 << 32) |
	//(1 << 40) | (1 << 48) | (1 << 56)

	for (int i = 0; i < 8; i++)
		ft_printf("%08b", string_modify[i]);
}


01100010011011110110111000000000 	//bon without padding
00100101001100000011100001100010

01100010011011110110111000100000    //bon with padding
00100000001000000010000000100000


01100101011110000110010101101101
01110000011011000110010100100000

01100101011110000110010101101101
01110000011011000110010100100000

http://www.univ-bouira.dz/fr/images/uamob/fichiers/Cours/Nourine/algorithme%20de%20chiffrement_DES.pdf

























//
