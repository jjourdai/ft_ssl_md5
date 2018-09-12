/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 18:37:51 by jjourdai          #+#    #+#             */
/*   Updated: 2017/02/20 10:23:17 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_list_size(t_list *begin_list)
{
	int		size;
	t_list	*tmp;

	if (!begin_list)
		return (0);
	size = 0;
	tmp = begin_list;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}

int		ft_list_find(t_list *begin_list, int nb)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = begin_list;
	while (tmp)
	{
		if (*((int*)tmp->content) == nb)
			return (i);
		i++;
		tmp = tmp->next;
	}
	return (0);
}

int		ft_list_find_less(t_list *begin_list, int nb)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = begin_list;
	while (tmp)
	{
		if (*((int*)tmp->content) < nb)
			return (i);
		i++;
		tmp = tmp->next;
	}
	return (0);
}

int		ft_list_find_more(t_list *begin_list, int nb)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = begin_list;
	while (tmp)
	{
		if (*((int*)tmp->content) > nb)
			return (i);
		i++;
		tmp = tmp->next;
	}
	return (0);
}

t_bool	ft_list_is_sort(t_list *lst, t_bool order)
{
	t_list *tmp;

	if (lst)
	{
		tmp = lst;
		while (tmp->next)
		{
			if (order == 1 && !((*(int*)tmp->content) <
			(*(int*)tmp->next->content)))
				return (0);
			if (order == 0 && !((*(int*)tmp->content) >
			(*(int*)tmp->next->content)))
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}
