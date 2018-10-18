/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 14:43:53 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/15 16:11:43 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void	display_des(t_data *info, t_command *cmd)
{
	write(info->fd, info->bytes, info->len);
	free(info->bytes);
}

static void		fill_target_struct(t_data *target, t_list *parameters,\
	int opt_flag)
{
	t_list			*tmp;
	t_parameters	*current;

	tmp = parameters;
	target->param_type = STDIN_;
	while (tmp)
	{
		current = (t_parameters*)tmp->content;
		if (current->type == F_OUTPUT)
			target->fd = open(current->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (current->type == F_INPUT || current->type == NONE_)
		{
			target->param_type = FILE_;
			target->string = current->str;
		}
		else if (current->type & F_KEY)
		{
			ft_memcpy(target->key, current->str, SIZE_KEY);
		}
		else if (current->type & F_IVECTOR)
		{
			ft_memcpy(target->iv, current->str, SIZE_KEY);
		}
		else if (current->type & F_SALT)
		{
			ft_memcpy(target->salt, current->str, SIZE_KEY);
		}
		else if (current->type & F_PASSWORD)
		{
			target->password = ft_strdup(current->str);
			// ft_memcpy(target->password, current->str, SIZE_KEY);
		}
		// else if (current->type & F_PASSWORD)
		// 	target->password = current->str;
		tmp = tmp->next;
	}
	ft_lstdel(&parameters, ft_del);
}

void			run_des_parameters_and_exec(t_command *cmd, t_list *parameters,\
	int opt_flag)
{
	t_data target;

	ft_bzero(&target, sizeof(target));
	target.fd = STDOUT_FILENO;
	fill_target_struct(&target, parameters, opt_flag);
	if (target.param_type == STDIN_)
		exec_read_stdin(cmd, opt_flag, &target);
	else
		exec_command(&target, cmd, opt_flag);
	if (target.fd != STDOUT_FILENO && target.fd != -1)
		close(target.fd);
}

void			pbkdf2(char *password, uint64_t salt, uint64_t iteration_count, uint64_t derived_key_length)
{
	// srand(time(NULL));

	// ft_printf("%llx\n", rand());
	// fprintf(stdout, "%llx\n", (unsigned long long)time(NULL));
}

void			des_cbc(t_data *info)
{
	uint64_t	iv;
	size_t		len_key;
	if ((len_key = ft_strlen((char*)info->iv)) > 16)
		info->iv[16] = 0;
	else if (len_key < 16)
	{
		ft_memset(info->iv + len_key, '0', SIZE_KEY - len_key);
		info->iv[16] = 0;
	}
	if (!(iv = ft_atoi_base_64((char*)info->iv, "0123456789ABCDEF")))
		raise_error(DES, INVALID_KEY, NULL ,EXIT);
	if (info->flag & F_DECRYPT)
		des_cbc_decrypt(info, iv);
	else
		des_cbc_encrypt(info, iv);
}

void			des_ecb(t_data *info)
{
	// if (info->password[0] == 0)
	// {
	// 	//getch passowrd in stdin
	// }
	// if (info->salt[0] == 0)
	// {
	// 	//generate salt
	// }
	// if (info->key[0] == 0)
	// {
	// 	//generate key
	// 	// pbkdf2(NULL, 0, 0, 0);

	// }
	if (info->flag & F_DECRYPT)
		des_ecb_decrypt(info);
	else
		des_ecb_encrypt(info);
}
