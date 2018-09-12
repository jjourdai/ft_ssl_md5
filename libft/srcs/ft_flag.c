/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 18:07:41 by jjourdai          #+#    #+#             */
/*   Updated: 2017/01/02 11:15:06 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		f_sharp(t_flag *buf, char op)
{
	if ((op == 'o' || op == 'O') && STR[0] != '0')
		STR = ft_strjoin_free("0", STR, FREE_S2);
	if (op == 'x' && T_NB != 0)
	{
		if (ZERO_T && !(LESS_T))
			ft_memcpy(STR, "0x", 2);
		else
			STR = ft_strjoin_free("0x", STR, FREE_S2);
	}
	if (op == 'X' && T_NB != 0)
	{
		if (ZERO_T)
			ft_memcpy(STR, "0X", 2);
		else
			STR = ft_strjoin_free("0X", STR, FREE_S2);
	}
	if (ft_strchr("aAeEfFgG", op))
		STR = ft_strjoin_free("0.", STR, FREE_S2);
	if (op == 'b' && T_NB != 0)
	{
		if (ZERO_T)
			ft_memcpy(STR, "0b", 2);
		else
			STR = ft_strjoin_free("0b", STR, FREE_S2);
	}
}

void		f_accu(t_flag *buf, char op)
{
	char	*str;
	int		neg;

	if (ACCU_0_T && T_NB == 0 && ((op != 'o' && op != 'O') || ((op == 'o'
	|| op == 'O') && !(SHARP_T))) && op != '%' && op)
	{
		ft_strdel(&STR);
		STR = ft_strdup("");
		return ;
	}
	neg = (T_NB < 0) ? 1 : 0;
	if (ft_strchr("dioOuxXb", op) && (int)ft_strlen(STR) < T_ACCU + neg &&
	!(ACCU_0_T))
		STR = ft_strjoin_free(ft_cpychar('0', T_ACCU + neg - ft_strlen(STR)),
		STR, FREE_S1_S2);
	else if (ft_strchr("aAeEfF", op))
	{
	}
	else if (ft_strchr("s", op) && !(ACCU_0_T) && T_ACCU < (int)ft_strlen(STR))
	{
		str = STR;
		STR = ft_strndup(STR, T_ACCU);
		free(str);
	}
}

void		apply_width_flag(t_flag *buf, char car, int size)
{
	char	*cpy;

	if (T_NB < 0 && ZERO_T)
	{
		cpy = ft_cpychar(car, ++T_WIDTH - size);
		STR = ft_strjoin_size(cpy, STR + 1, T_WIDTH - size, size);
	}
	else
	{
		cpy = ft_cpychar(car, T_WIDTH - size);
		STR = ft_strjoin_size(cpy, STR, T_WIDTH - size, size);
	}
	ft_strdel(&cpy);
}

void		f_width(t_flag *buf, char op)
{
	int		size;
	char	*ptr;
	char	*str;
	char	car;

	str = STR;
	car = (!(ZERO_T) || LESS_T) ? ' ' : '0';
	size = (STR) ? ft_strlen(STR) : 1;
	if (STR && SPE_T)
		size++;
	if (LESS_T)
		STR = ft_strjoin_free(STR, ft_cpychar(car, T_WIDTH - size), FREE_S1_S2);
	else
	{
		apply_width_flag(buf, car, size);
		if (STR && (ptr = ft_strchr(STR, '+')) && ZERO_T)
			*ptr = '0';
		STR[0] = (T_NB < 0 && ZERO_T) ? '-' : STR[0];
		STR[0] = (T_NB >= 0 && MORE_T && ZERO_T) ? '+' : STR[0];
		if (T_NB > 0)
			ft_strdel(&str);
	}
	if (ZERO_T && SHARP_T && !(LESS_T))
		f_sharp(buf, op);
}

void		f_more(t_flag *buf, char op)
{
	if (ft_strchr("diouxX", op))
	{
		if ((ft_strchr(" ", STR[0]) && T_NB > 0) || (T_WIDTH && !(LESS_T) &&
		!(T_ACCU) && !(ZERO_T)))
			STR[0] = '+';
		else
			STR = ft_strjoin_free("+", STR, FREE_S2);
	}
	else
	{
		if (ft_strchr(" ", STR[0]) || ft_strchr("0", STR[0]))
			STR[0] = '+';
		else
			STR = ft_strjoin_free("+", STR, FREE_S2);
	}
}
