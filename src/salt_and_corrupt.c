/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   salt_and_corrupt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 12:17:40 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/22 14:12:56 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void				check_if_corrupted(int cmd, t_data *info)
{
	if (info->len % 8)
		raise_error(cmd, WRONG_LENGTH, NULL, EXIT);
}

void				check_if_corrupted_padding_after_decrypt(t_data *info)
{
	unsigned char		*ptr;
	size_t				i;
	uint32_t			value;
	uint32_t			previous_value;
	uint32_t			quantity;

	ptr = (unsigned char*)info->bytes + info->len;
	quantity = 0;
	previous_value = 0;
	i = *(ptr - 1);
	while (i)
	{
		value = *(ptr - i);
		if (previous_value != 0 && value != previous_value)
		{
			if (previous_value != quantity)
				raise_error(DES_ECB, WRONG_LENGTH, NULL, EXIT);
			else
				break ;
		}
		previous_value = value;
		quantity++;
		i--;
	}
	info->len = info->len - quantity;
}

void				remove_salted(t_data *info)
{
	uint64_t	salt;
	char		*salt_str;
	size_t		size;

	if (info->len <= 0)
		raise_error(GENERAL, BAD_MAGIC_NUMBER, NULL, EXIT);
	if (ft_strncmp(SALTED, (char*)info->bytes, ft_strlen(SALTED)) == 0)
	{
		salt = *((uint64_t*)(info->bytes + 8));
		salt_str = ft_itoa_base_ull(SWAP_VALUE(salt), "0123456789ABCDEF");
		if ((size = ft_strlen(salt_str)) != 16)
		{
			ft_memset(info->salt, '0', DES_KEY_LEN - size);
			ft_memcpy(info->salt + DES_KEY_LEN - size, salt_str, size);
		}
		else
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
	new_ptr = ft_memalloc(info->len + 16);
	salt = SWAP_VALUE(salt);
	ft_memcpy(new_ptr, SALTED, size);
	ft_memcpy(new_ptr + size, (char*)&salt, 8);
	ft_memcpy(new_ptr + 16, (char*)info->bytes, info->len);
	free(info->bytes);
	info->bytes = (uint8_t*)new_ptr;
	info->len += 16;
}
