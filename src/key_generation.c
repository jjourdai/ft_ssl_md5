/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 14:25:37 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/18 14:25:41 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

uint64_t	iv_or_salt_generator(void)
{
	int			fd;
	static char	buffer[8];

	if ((fd = open("/dev/random", O_RDONLY)) == -1)
		raise_error(DES, OPEN_FAILED, "/dev/random", EXIT);
	read(fd, buffer, 8);
	return (*(uint64_t*)buffer);
}

uint64_t	iv_or_salt_str_to_bytes(char str[17])
{
	size_t		len_key;
	uint64_t	data;

	if ((len_key = ft_strlen(str)) > 16)
		str[16] = 0;
	else if (len_key < 16)
	{
		ft_memset(str + len_key, '0', SIZE_KEY - len_key);
		str[16] = 0;
	}
	if (!string_is_only_hexchar(str))
		raise_error(DES, INVALID_KEY, NULL, EXIT);
	data = ft_hexa_to_uint64_t(str);
	return (data);
}

char		*wrap_getpass(void)
{
	char		password0[PASSWORD_LEN];
	char		password1[PASSWORD_LEN];
	char		*ret0;

	ft_putendl("enter encryption password:");
	ret0 = getpass(password0);
	ft_memcpy(password0, ret0, ft_strlen(ret0));
	ft_putendl("Verifying - enter encryption password:");
	if ((strcmp(ret0 = getpass(password1), password0)) != 0)
		raise_error(DES, WRONG_PASSWD, NULL, EXIT);
	return (ret0);
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
	concat = ft_memalloc(PASSWORD_LEN + SIZE_KEY);
	ft_memcpy(concat, password, ft_strlen(password));
	ft_memcpy(concat + ft_strlen(password), str, 8);
	get_md5_key.bytes = (uint8_t*)concat;
	get_md5_key.len = ft_strlen(password) + 8;
	md5(&get_md5_key);
	hash_str = int_to_char(&get_md5_key, 4, MD5);
	return (hash_str);
}


char			*generate_key_des3(uint64_t salt, char *password)
{
	t_data	get_md5_key;
	char	*key_concat;
	char	*str;
	char	*concat;
	char	*hash_str;

	key_concat = ft_memalloc(DES3_KEY_LEN + 1000);

	ft_bzero(&get_md5_key, sizeof(get_md5_key));
	salt = SWAP_VALUE(salt);
	str = ((char*)&salt);
	concat = ft_memalloc(PASSWORD_LEN + DES3_KEY_LEN);
	ft_memcpy(concat, password, ft_strlen(password));
	ft_memcpy(concat + ft_strlen(password), str, 8);
	get_md5_key.bytes = (uint8_t*)concat;
	get_md5_key.len = ft_strlen(password) + 8;
	md5(&get_md5_key);
	ft_memcpy(key_concat, int_to_char(&get_md5_key, 4, MD5), 32);
	char *test = (char*)get_md5_key.final_hash;
	ft_bzero(concat, PASSWORD_LEN + DES3_KEY_LEN);
	ft_memcpy(concat, test, 16);
	ft_memcpy(concat + 16, password, ft_strlen(password));
	ft_memcpy(concat + 16 + ft_strlen(password), str, 8);
	get_md5_key.bytes = (uint8_t*)concat;
	get_md5_key.len = 16 + ft_strlen(password) + 8;
	md5(&get_md5_key);
	ft_memcpy(key_concat + 32, int_to_char(&get_md5_key, 4, MD5), 32);
	ft_memdel((void**)&concat);
	return (key_concat);
}