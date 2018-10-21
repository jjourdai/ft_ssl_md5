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

void				remove_salted(t_data *info)
{
	uint64_t	salt;
	char		*salt_str;

	if (ft_strncmp(SALTED, (char*)info->bytes, ft_strlen(SALTED)) == 0)
	{
		salt = *((uint64_t*)(info->bytes + 8));
		salt_str = ft_itoa_base_ll(SWAP_VALUE(salt), "0123456789ABCDEF");
		ft_memcpy(info->salt, salt_str, 16);
		free(salt_str);
		ft_move_data((char*)info->bytes, info->len, 16);
		info->len -= 16;
	}
}

void				add_salted(t_data *info, uint64_t salt)
{
	char	*new_ptr;
	size_t	size;

	size = ft_strlen(SALTED);
	new_ptr = ft_memalloc(info->len + 24);
	salt = SWAP_VALUE(salt);
	ft_memcpy(new_ptr, SALTED, size);
	ft_memcpy(new_ptr + size, (char*)&salt, 8);
	ft_memcpy(new_ptr + 16, (char*)info->bytes, info->len);
	free(info->bytes);
	info->bytes = (uint8_t*)new_ptr;
	info->len += 16;
}

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
	char		*key;

	iv = (info->iv[0] == 0) ? iv_or_salt_generator() :\
		iv_or_salt_str_to_bytes((char*)(info->iv));
	if (info->key[0] == 0)
	{
		if (info->flag & F_DECRYPT)
			remove_salted(info);
		salt = (info->salt[0] == 0) ? iv_or_salt_generator() :\
			iv_or_salt_str_to_bytes((char*)(info->salt));
		password = (info->password[0] == 0) ? ft_memcpy(info->password,\
			wrap_getpass(), PASSWORD_LEN) : info->password;
		key = generate_key(salt, password);
		ft_memcpy(info->key, key, SIZE_KEY);
		ft_memdel((void**)&key);
	}
	else 
		padd_key((char*)info->key, SIZE_KEY);
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

void			des_ecb(t_data *info)
{
	uint64_t	salt;
	char		*password;
	char		*key;

	if (info->key[0] == 0)
	{
		if (info->flag & F_DECRYPT)
			remove_salted(info);
		salt = (info->salt[0] == 0) ? iv_or_salt_generator() :\
			iv_or_salt_str_to_bytes((char*)(info->salt));
		password = (info->password[0] == 0) ? ft_memcpy(info->password,\
			wrap_getpass(), PASSWORD_LEN) : info->password;
		key = generate_key(salt, password);
		ft_memcpy(info->key, key, SIZE_KEY);
		ft_memdel((void**)&key);
	}
	else 
		padd_key((char*)info->key, SIZE_KEY);
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

void			des3(t_data *info)
{
	uint64_t	salt;
	uint64_t	iv;
	char		*password;
	char		*key;

	if (info->key[0] == 0)
	{
		if (info->flag & F_DECRYPT)
			remove_salted(info);
		salt = (info->salt[0] == 0) ? iv_or_salt_generator() :\
			iv_or_salt_str_to_bytes((char*)(info->salt));
		password = (info->password[0] == 0) ? ft_memcpy(info->password,\
			wrap_getpass(), PASSWORD_LEN) : info->password;
		key = generate_key_des3(salt, password);
		ft_memcpy(info->key, key, DES3_KEY_LEN);
		ft_memdel((void**)&key);
	}
	else
		padd_key((char*)info->key, DES3_KEY_LEN);
	iv = (info->iv[0] == 0) ? iv_or_salt_str_to_bytes((char*)(info->key + DES3_KEY_LEN - 16)) :\
		iv_or_salt_str_to_bytes((char*)(info->iv));
	if (info->flag & F_DECRYPT)
	{
		if (info->flag & F_BASE64)
			base64_decode(info);
		check_if_corrupted(DES3, info);
		des3_decrypt(info, iv);
		check_if_corrupted_padding_after_decrypt(info);
	}
	else
	{
		des3_encrypt(info, iv);
		if (info->flag & F_PASSWORD)
			add_salted(info, salt);
		if (info->flag & F_BASE64)
			base64_encode(info);
	}
}
