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

void			display_des(t_data *info, t_command *cmd)
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
			target->string = (uint8_t*)current->str;
		}
		else if (current->type & F_KEY)
			ft_memcpy(target->key, current->str, SIZE_KEY);
		else if (current->type & F_IVECTOR)
			ft_memcpy(target->iv, current->str, SIZE_KEY);
		else if (current->type & F_SALT)
			ft_memcpy(target->salt, current->str, SIZE_KEY);
		else if (current->type & F_PASSWORD)
			ft_memcpy(target->password, current->str, PASSWORD_LEN);
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

char			*generate_key(uint64_t salt, char *password)
{
	t_data get_md5_key;

	ft_bzero(&get_md5_key, sizeof(get_md5_key));
	salt = SWAP_VALUE(salt);
	char *str = ((char*)&salt);
	char *concat = ft_memalloc(128);
	ft_memcpy(concat, password, ft_strlen(password));
	ft_memcpy(concat + ft_strlen(password), str, 8);
	get_md5_key.bytes = (uint8_t*)concat;
	get_md5_key.len = ft_strlen(concat);
	md5(&get_md5_key);
	char *hash_str = int_to_char(&get_md5_key, 4, MD5);
	hash_str[16] = 0;
	return (hash_str);
}

void			des_cbc(t_data *info)
{
	uint64_t	salt;
	uint64_t	iv;
	char		*password;

	iv = (info->iv[0] == 0) ? iv_or_salt_generator() :\
		iv_or_salt_str_to_bytes((char*)(info->iv));
	if (info->key[0] == 0)
	{
		salt = (info->salt[0] == 0) ? iv_or_salt_generator() :\
			iv_or_salt_str_to_bytes((char*)(info->salt));
		password = (info->password[0] == 0) ? ft_memcpy(info->password,\
			wrap_getpass(), PASSWORD_LEN) : info->password;
		ft_memcpy(info->key, generate_key(salt, password), SIZE_KEY);
	}
	if (info->flag & F_DECRYPT)
		des_cbc_decrypt(info, iv);
	else
		des_cbc_encrypt(info, iv);
}

void			des_ecb(t_data *info)
{
	uint64_t	salt;
	char		*password;

	if (info->key[0] == 0)
	{
		salt = (info->salt[0] == 0) ? iv_or_salt_generator() :\
			iv_or_salt_str_to_bytes((char*)(info->salt));
		password = (info->password[0] == 0) ? ft_memcpy(info->password,\
			wrap_getpass(), PASSWORD_LEN) : info->password;
		ft_memcpy(info->key, generate_key(salt, password), SIZE_KEY);
	}
	if (info->flag & F_DECRYPT)
		des_ecb_decrypt(info);
	else
		des_ecb_encrypt(info);
}
