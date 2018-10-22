/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_key_generator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 10:49:27 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/22 10:49:29 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static char	*return_md5_hash(t_data *get_md5_key, char *str, size_t len)
{
	char *tmp;

	ft_bzero(get_md5_key, sizeof(get_md5_key));
	get_md5_key->bytes = (uint8_t*)str;
	get_md5_key->len = len;
	md5(get_md5_key);
	tmp = int_to_char(get_md5_key, 4, MD5);
	return (tmp);
}

char		*generate_key_des3(uint64_t salt, char *password)
{
	char	*result;
	char	*str;
	char	*concat;
	char	*tmp;
	t_data	get_md5_key;

	result = ft_memalloc(DES3_KEY_LEN + 1);
	salt = SWAP_VALUE(salt);
	str = ((char*)&salt);
	concat = ft_memalloc(PASSWORD_LEN + DES3_KEY_LEN);
	ft_memcpy(concat, password, ft_strlen(password));
	ft_memcpy(concat + ft_strlen(password), str, 8);
	tmp = return_md5_hash(&get_md5_key, concat, ft_strlen(password) + 8);
	ft_memcpy(result, tmp, 32);
	ft_memdel((void**)&tmp);
	ft_bzero(concat, PASSWORD_LEN + DES3_KEY_LEN);
	ft_memcpy(concat, (char*)get_md5_key.final_hash, 16);
	ft_memcpy(concat + 16, password, ft_strlen(password));
	ft_memcpy(concat + 16 + ft_strlen(password), str, 8);
	tmp = return_md5_hash(&get_md5_key, concat, 16 + ft_strlen(password) + 8);
	ft_memcpy(result + 32, tmp, 32);
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&concat);
	return (result);
}
