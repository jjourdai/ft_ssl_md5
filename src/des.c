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
	(void)cmd;
	write(info->fd, info->bytes, info->len);
	free(info->bytes);
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
		exit(0);
	}
	if (info->flag & F_DECRYPT)
	{
		if (info->flag & F_BASE64)
			base64_decode(info);
		check_if_corrupted(info);
		des_cbc_decrypt(info, iv);
	}
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
	{
		if (info->flag & F_BASE64)
			base64_decode(info);
		check_if_corrupted(info);
		des_ecb_decrypt(info);
	}
	else
		des_ecb_encrypt(info);
}
