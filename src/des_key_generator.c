/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 14:25:37 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/22 10:35:20 by jjourdai         ###   ########.fr       */
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
	close(fd);
	return (*(uint64_t*)buffer);
}

uint64_t	iv_or_salt_str_to_bytes(char *str)
{
	size_t		len_key;
	uint64_t	data;

	ft_toupper_str(str, 16);
	if ((len_key = ft_strlen(str)) > 16)
		str[16] = 0;
	else if (len_key < 16)
	{
		ft_memset(str + len_key, '0', DES_KEY_LEN - len_key);
		str[16] = 0;
	}
	if (!string_is_only_hexchar(str))
		raise_error(DES, INVALID_KEY, NULL, EXIT);
	data = ft_hexa_to_uint64_t(str);
	return (data);
}

char		*wrap_getpass(t_data *info)
{
	char		password0[PASSWORD_LEN];
	char		password1[PASSWORD_LEN];
	char		*ret0;

	ft_bzero(password0, sizeof(password0));
	ft_bzero(password1, sizeof(password1));
	ft_putendl("enter encryption password:");
	ret0 = getpass(password0);
	ft_memcpy(password0, ret0, ft_strlen(ret0));
	if (!(info->flag & F_DECRYPT))
	{
		ft_putendl("Verifying - enter encryption password:");
		if ((strcmp(ret0 = getpass(password1), password0)) != 0)
			raise_error(DES, WRONG_PASSWD, NULL, EXIT);
	}
	return (ret0);
}

char		*generate_key(uint64_t salt, char *password)
{
	t_data	get_md5_key;
	char	*str;
	char	*concat;
	char	*hash_str;

	ft_bzero(&get_md5_key, sizeof(get_md5_key));
	salt = SWAP_VALUE(salt);
	str = ((char*)&salt);
	concat = ft_memalloc(PASSWORD_LEN + DES_KEY_LEN);
	ft_memcpy(concat, password, ft_strlen(password));
	ft_memcpy(concat + ft_strlen(password), str, 8);
	get_md5_key.bytes = (uint8_t*)concat;
	get_md5_key.len = ft_strlen(password) + 8;
	md5(&get_md5_key);
	hash_str = int_to_char(&get_md5_key, 4, MD5);
	ft_memdel((void**)&concat);
	return (hash_str);
}
