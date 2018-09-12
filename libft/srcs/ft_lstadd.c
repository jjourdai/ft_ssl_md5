/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:51:35 by jjourdai          #+#    #+#             */
/*   Updated: 2018/02/10 17:12:18 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}

t_list	*ft_lstnew(void	const *content, size_t content_size)
{
	t_list *new;

	if ((new = ft_memalloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content != NULL)
	{
		new->content_size = content_size;
		new->content = ft_memalloc(content_size);
		ft_memcpy(new->content, content, content_size);
	}
	else
	{
		new->content_size = 0;
		new->content = NULL;
	}
	new->next = NULL;
	return (new);
}

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	tmp = *alst;
	while (tmp)
	{
		tmp = tmp->next;
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = tmp;
	}
	*alst = NULL;
}

void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}

void	ft_lstreverse(t_list **lst)
{
	t_list *tmp;
	t_list *bef;
	t_list *nex;

	tmp = *lst;
	bef = NULL;
	if (tmp)
	{
		while (tmp)
		{
			nex = tmp->next;
			tmp->next = bef;
			bef = tmp;
			tmp = nex;
		}
		*lst = bef;
	}
}
