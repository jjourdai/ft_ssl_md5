/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 12:13:57 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/22 12:13:58 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void				des3_encrypt(t_data *info, uint64_t iv,\
	char *encrypted_string)
{
	uint64_t	keys1[16];
	uint64_t	keys2[16];
	uint64_t	keys3[16];
	size_t		i;
	uint64_t	block;

	get_keys(keys3, (char*)info->key + DES_KEY_LEN * 2, DES_KEY_LEN);
	get_keys(keys2, (char*)info->key + DES_KEY_LEN, DES_KEY_LEN);
	get_keys(keys1, (char*)info->key, DES_KEY_LEN);
	i = 0;
	while (i != info->len)
	{
		block = SWAP_VALUE(*((uint64_t*)(info->bytes + i)));
		block = update_block_cbc_encrypt(keys1, iv, block);
		block = update_block_cbc_decrypt(keys2, iv, block);
		iv = update_block_cbc_encrypt(keys3, iv, block);
		block = SWAP_VALUE(iv);
		ft_memcpy(encrypted_string + i, (char*)(&block), 8);
		i += 8;
	}
	if (info->bytes != NULL)
		free(info->bytes);
	info->bytes = (uint8_t*)encrypted_string;
}

void				des3_decrypt(t_data *info, uint64_t iv,\
	char *decrypted_string)
{
	uint64_t	keys1[16];
	uint64_t	keys2[16];
	uint64_t	keys3[16];
	size_t		i;
	uint64_t	block;

	get_keys(keys3, (char*)info->key + DES_KEY_LEN * 2, DES_KEY_LEN);
	get_keys(keys2, (char*)info->key + DES_KEY_LEN, DES_KEY_LEN);
	get_keys(keys1, (char*)info->key, DES_KEY_LEN);
	i = 0;
	while (i != info->len)
	{
		block = update_block_cbc_decrypt(keys3, iv,\
			SWAP_VALUE(*((uint64_t*)(info->bytes + i))));
		block = update_block_cbc_encrypt(keys2, iv, block);
		block = update_block_cbc_decrypt(keys1, iv, block);
		iv = SWAP_VALUE(*((uint64_t*)(info->bytes + i)));
		block = SWAP_VALUE(block);
		ft_memcpy(decrypted_string + i, (char*)(&block), 8);
		i += 8;
	}
	if (info->bytes != NULL)
		free(info->bytes);
	info->bytes = (uint8_t*)decrypted_string;
}

uint64_t			init_key_des3(t_data *info)
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
	key = generate_key_des3(salt, password);
	ft_memcpy(info->key, key, DES3_KEY_LEN);
	ft_memdel((void**)&key);
	return (salt);
}

void				des3(t_data *info)
{
	uint64_t	salt;
	uint64_t	iv;

	if (info->key[0] == 0)
		salt = init_key_des3(info);
	else
		padd_key((char*)info->key, DES3_KEY_LEN, ft_strlen((char*)info->key));
	iv = (info->iv[0] == 0) ? iv_or_salt_str_to_bytes((char*)(info->key\
		+ DES3_KEY_LEN - 16)) : iv_or_salt_str_to_bytes((char*)(info->iv));
	if (info->flag & F_DECRYPT)
	{
		if (info->flag & F_BASE64)
			base64_decode(info);
		check_if_corrupted(DES3, info);
		des3_decrypt(info, iv, ft_memalloc(info->len));
		check_if_corrupted_padding_after_decrypt(info);
	}
	else
	{
		des3_encrypt(info, iv, put_padding_character(info));
		if (info->flag & F_PASSWORD)
			add_salted(info, salt);
		if (info->flag & F_BASE64)
			base64_encode(info);
	}
}
