/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freelist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:51:04 by jjourdai          #+#    #+#             */
/*   Updated: 2017/09/13 11:51:08 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	freelist(t_list *list)
{
	t_list *tmp;

	if (list)
	{
		while (list)
		{
			tmp = list;
			list = list->next;
			ft_memdel((void**)&tmp);
		}
	}
}
