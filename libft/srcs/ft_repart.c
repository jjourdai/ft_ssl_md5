/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_repart.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 15:24:09 by jjourdai          #+#    #+#             */
/*   Updated: 2017/01/18 12:08:22 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_exit(t_buf *global, t_flag *buf)
{
	write(1, G_BUF, G_SIZE);
	write(1, "-1", 2);
	free(global);
	free_flag_tmp(buf);
	exit(-1);
}

void	op_is_unsigned(char op, t_flag *buf, va_list ap, t_buf *global)
{
	int ret;

	if (T_LEN == 'L' || T_LEN == 'z')
		ret = apply_lenght_arg(va_arg(ap, unsigned long long), op, buf);
	else if (T_LEN == 'l' || op == 'U' || op == 'O' || T_LEN == 'j')
		ret = apply_lenght_arg(va_arg(ap, unsigned long), op, buf);
	else if (T_LEN == 'H')
		ret = apply_lenght_arg((unsigned char)va_arg(ap, unsigned int),
		op, buf);
	else if (T_LEN == 'h')
		ret = apply_lenght_arg((unsigned short)va_arg(ap, unsigned int),
		op, buf);
	else
		ret = apply_lenght_arg(va_arg(ap, unsigned int), op, buf);
	if (ret == -1)
		print_exit(global, buf);
}

void	op_is_signed(char op, t_flag *buf, va_list ap, t_buf *global)
{
	int ret;

	if (T_LEN == 'L' || T_LEN == 'z')
		ret = apply_lenght_arg(va_arg(ap, long long), op, buf);
	else if (T_LEN == 'l' || op == 'D' || T_LEN == 'j')
		ret = apply_lenght_arg(va_arg(ap, long), op, buf);
	else if (T_LEN == 'H')
		ret = apply_lenght_arg((char)va_arg(ap, int), op, buf);
	else if (T_LEN == 'h')
		ret = apply_lenght_arg((short)va_arg(ap, int), op, buf);
	else
		ret = apply_lenght_arg(va_arg(ap, int), op, buf);
	if (ret == -1)
		print_exit(global, buf);
}

int		ft_flag(char op, t_flag *buf)
{
	if (ZERO_T && T_ACCU)
		FLAG_ON = FLAG_ON & ~(1u << 5);
	if (T_ACCU || (ACCU_0_T && op != 'p'))
		f_accu(buf, op);
	if (SHARP_T && (!(ZERO_T) || (ZERO_T && LESS_T)))
		f_sharp(buf, op);
	if (MORE_T && ft_strchr("di", op) && STR[0] != '-' && T_NB >= 0 && op)
		f_more(buf, op);
	if ((T_WIDTH && T_WIDTH > T_ACCU && T_WIDTH >= (int)ft_strlen(STR)) ||
	(T_WIDTH >= (int)ft_strlen(STR) && T_WIDTH && T_ACCU > T_WIDTH && (op == 's'
	|| op == 'S')))
		f_width(buf, op);
	if (op && SPACE_T && ft_strchr("di", op))
	{
		if (STR[0] == '0' || STR[0] == ' ')
			STR[0] = ' ';
		else if (ft_strchr("+-", STR[0]) == NULL)
			STR = ft_strjoin_free(" ", STR, FREE_S2);
	}
	return (0);
}

int		repart(char op, t_flag *buf, va_list ap, t_buf *global)
{
	int ret;

	ret = 0;
	if (op == 'C' || (op == 'c' && T_LEN == 'l'))
		ret = wint_t_arg(va_arg(ap, wchar_t), op, buf);
	else if (op == '%')
		STR = ft_strdup("%");
	else if (ft_strchr("diD", op))
		op_is_signed(op, buf, ap, global);
	else if (ft_strchr("oOxXuUb", op))
		op_is_unsigned(op, buf, ap, global);
	else if (op == 'S' || (op == 's' && T_LEN == 'l'))
		ret = wchar_t_arg(va_arg(ap, wchar_t*), op, buf);
	else if (op == 'p')
		ret = addr_arg(va_arg(ap, void*), buf);
	else if (op == 'n')
		ret = n_arg(va_arg(ap, int*), global);
	else if (op == 's')
		ret = s_arg(va_arg(ap, char*), op, buf);
	else
		ret = without_lenght_arg(va_arg(ap, int), op, buf);
	return (ret);
}
