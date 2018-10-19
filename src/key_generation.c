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
