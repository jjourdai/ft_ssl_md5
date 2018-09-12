/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:54:36 by jjourdai          #+#    #+#             */
/*   Updated: 2018/04/07 16:46:48 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	unsigned char	*new_ptr;
	unsigned char	*old_ptr;

	old_ptr = ptr;
	new_ptr = ft_memalloc(new_size);
	ft_memcpy(new_ptr, old_ptr, old_size);
	ft_memdel((void**)&ptr);
	return (new_ptr);
}
