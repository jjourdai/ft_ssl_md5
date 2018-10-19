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

char			*generate_key(uint64_t salt, char *password)
{
	t_data	get_md5_key;
	char	*str;
	char	*concat;
	char	*hash_str;

	ft_bzero(&get_md5_key, sizeof(get_md5_key));
	salt = SWAP_VALUE(salt);
	str = ((char*)&salt);
	concat = ft_memalloc(128);
	ft_memcpy(concat, password, ft_strlen(password));
	ft_memcpy(concat + ft_strlen(password), str, 8);
	get_md5_key.bytes = (uint8_t*)concat;
	get_md5_key.len = ft_strlen(concat);
	md5(&get_md5_key);
	hash_str = int_to_char(&get_md5_key, 4, MD5);
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
