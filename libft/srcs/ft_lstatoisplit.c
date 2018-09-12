/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstatoisplit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 12:34:43 by jjourdai          #+#    #+#             */
/*   Updated: 2017/02/18 19:38:56 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define VRAI 1
#define FAUX 0

static size_t	ft_nb_word(const char *str, char c)
{
	size_t i;
	size_t nb_word;

	i = 0;
	nb_word = 0;
	while (str[i + 1])
	{
		if ((str[i] == c && str[i + 1] != c))
			nb_word++;
		i++;
	}
	if (str[0] != c && str[0])
		nb_word++;
	return (nb_word);
}

static int		ft_notdigit(long *nb, char *s, int i, t_list **new)
{
	if (((*nb = ft_atoi(&s[i])) > INT_MAX || *nb < INT_MIN))
	{
		if (*new)
			ft_lstdel(new, ft_del);
		return (0);
	}
	if ((!ft_isdigit(s[i]) && (s[i] != '-' && s[i] != '+'))
	|| (!ft_isdigit(s[i + 1]) && (s[i] == '-' && s[i] == '+')))
		return (0);
	i++;
	while (s[i] && s[i] != ' ')
	{
		if (!(ft_isdigit(s[i])))
			return (0);
		i++;
	}
	return (1);
}

t_list			*ft_lstatoisplit(char const *s, char c)
{
	t_list		*new;
	size_t		i;
	size_t		size;
	long		nb;

	new = NULL;
	if (!s)
		return (NULL);
	size = ft_nb_word(s, c);
	i = 0;
	while (size--)
	{
		while (s[i] && s[i] == c)
			i++;
		if (ft_notdigit(&nb, (char*)s, i, &new) == 0)
			return (NULL);
		ft_lstadd(&new, ft_lstnew(&nb, sizeof(int)));
		while (s[i] && s[i] != c)
			i++;
		i++;
	}
	return (new);
}
