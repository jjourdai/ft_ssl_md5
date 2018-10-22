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

void				display_des(t_data *info, t_command *cmd)
{
	(void)cmd;
	write(info->fd, info->bytes, info->len);
	free(info->bytes);
}

uint64_t			init_key_des(t_data *info)
{
	uint64_t	salt;
	char		*password;
	char		*key;

	if (info->flag & (F_DECRYPT | F_PASSWORD))
		remove_salted(info);
	salt = (info->salt[0] == 0) ? iv_or_salt_generator() :\
		iv_or_salt_str_to_bytes((char*)(info->salt));
	password = (info->password[0] == 0) ? ft_memcpy(info->password,\
		wrap_getpass(info), PASSWORD_LEN) : info->password;
	key = generate_key(salt, password);
	ft_memcpy(info->key, key, DES_KEY_LEN);
	ft_memdel((void**)&key);
	return (salt);
}

void				des_cbc(t_data *info)
{
	uint64_t	iv;
	uint64_t	salt;

	iv = (info->iv[0] == 0) ? iv_or_salt_generator() :\
		iv_or_salt_str_to_bytes((char*)(info->iv));
	if (info->key[0] == 0)
		salt = init_key_des(info);
	else
		padd_key((char*)info->key, DES_KEY_LEN, ft_strlen((char*)info->key));
	if (info->flag & F_DECRYPT)
	{
		if (info->flag & F_BASE64)
			base64_decode(info);
		check_if_corrupted(DES_CBC, info);
		des_cbc_decrypt(info, iv);
		check_if_corrupted_padding_after_decrypt(info);
	}
	else
	{
		des_cbc_encrypt(info, iv, put_padding_character(info));
		if (info->flag & F_PASSWORD)
			add_salted(info, salt);
		if (info->flag & F_BASE64)
			base64_encode(info);
	}
}

void				des_ecb(t_data *info)
{
	uint64_t	salt;

	salt = 0;
	if (info->key[0] == 0)
		salt = init_key_des(info);
	else
		padd_key((char*)info->key, DES_KEY_LEN, ft_strlen((char*)info->key));
	if (info->flag & F_DECRYPT)
	{
		if (info->flag & F_BASE64)
			base64_decode(info);
		check_if_corrupted(DES_ECB, info);
		des_ecb_decrypt(info);
		check_if_corrupted_padding_after_decrypt(info);
	}
	else
	{
		des_ecb_encrypt(info, put_padding_character(info));
		if (info->flag & F_PASSWORD)
			add_salted(info, salt);
		if (info->flag & F_BASE64)
			base64_encode(info);
	}
}
