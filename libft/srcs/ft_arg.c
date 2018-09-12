/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 16:14:26 by jjourdai          #+#    #+#             */
/*   Updated: 2017/01/18 15:59:42 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		apply_lenght_arg(long long d, char op, t_flag *buf)
{
	if (op == 'U' || op == 'u')
		STR = ft_itoa_ul(d);
	else if (op == 'O' && (d == LONG_MAX || d == LONG_MIN))
		STR = ft_itoa_ull(d);
	else if (op == 'O')
		STR = ft_itoa_ull(ft_convert_decitooctal(d));
	else if (op == 'x')
		STR = ft_itoa_base_ull(d, "0123456789abcdef");
	else if (op == 'X')
		STR = ft_itoa_base_ull(d, "0123456789ABCDEF");
	else if (op == 'd' || op == 'i' || op == 'u' || op == 'D')
		STR = ft_itoa_ll(d);
	else if (op == 'o')
	{
		if ((unsigned long)d == ULONG_MAX)
			STR = ft_strdup("1777777777777777777777");
		else
			STR = ft_itoa_ll(ft_convert_decitooctal(d));
	}
	else if (op == 'b')
		STR = ft_itoa_base_ull(d, "01");
	T_NB = d;
	return (0);
}

int		double_arg(double d, char op, t_flag *buf)
{
	if (op == 'E' || op == 'e')
		d = 2;
	op = 'w';
	buf = NULL;
	T_NB = d;
	return (0);
}

int		without_lenght_arg(int d, char op, t_flag *buf)
{
	if (op == 'd' || op == 'i')
	{
		if (d == 0)
			STR = ft_strdup("0");
		else
			STR = ft_itoa(d);
	}
	else if (op == 'o')
		STR = ft_itoa_l(ft_convert_decitooctal((unsigned int)d));
	else if (op == 'u')
		STR = ft_itoa_u(d);
	else if (op == 'x')
		STR = ft_itoa_base_uint(d, "0123456789abcdef");
	else if (op == 'X')
		STR = ft_itoa_base_uint(d, "0123456789ABCDEF");
	else if (op == 'c' && d == '\0')
		T_SPE;
	else if (op == 'c')
		STR = ft_strdup((char*)&d);
	else if (op == 'b')
		STR = ft_itoa_base_uint(d, "01");
	T_NB = d;
	return (0);
}

void	free_flag_tmp(t_flag *buf)
{
	if (STR)
		free(STR);
	if (BUF)
		free(BUF);
}
