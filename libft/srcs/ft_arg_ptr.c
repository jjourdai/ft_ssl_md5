/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 16:50:25 by jjourdai          #+#    #+#             */
/*   Updated: 2017/01/02 11:14:16 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		addr_arg(int *d, t_flag *buf)
{
	if (d == 0 && ACCU_0_T)
		STR = ft_strdup("0x");
	else if (d == 0 && !T_ACCU && !(ZERO_T))
		STR = ft_strdup("0x0");
	else if ((!(ZERO_T) && T_ACCU) || (ZERO_T && T_WIDTH && !d))
	{
		STR = ft_itoa_base((long int)d, "0123456789abcdef");
		if (!(ZERO_T) && T_ACCU)
		{
			if ((int)ft_strlen(STR) > T_ACCU)
			{
				STR = ft_strjoin_free("0x", STR, FREE_S2);
				return (0);
			}
			STR = ft_strjoin(ft_cpychar('0', T_ACCU + 2 - ft_strlen(STR)), STR);
		}
		else if (ZERO_T && T_WIDTH && !d)
			STR = ft_strjoin_free(ft_cpychar('0', T_WIDTH - ft_strlen(STR)),
			STR, FREE_S2);
		ft_memcpy(STR, "0x", 2);
	}
	else
		STR = ft_strcut(ft_itoa_0x(d, "0123456789abcdef"), '0');
	return (0);
}

int		n_arg(int *d, t_buf *global)
{
	if (d)
		*d = G_SIZE;
	return (0);
}

int		s_arg(char *d, char op, t_flag *buf)
{
	if (op == 's')
	{
		if (d == NULL)
			STR = ft_strdup("(null)");
		else
			STR = ft_strdup(d);
	}
	return (0);
}

int		wchar_t_arg(wchar_t *d, char op, t_flag *buf)
{
	char	str[5];
	int		len;
	int		accurate;

	ft_bzero(str, 5);
	accurate = (T_ACCU > 0) ? T_ACCU : 0;
	if (!d)
		STR = ft_strdup("(null)");
	if (d && (op == 'S' || op == 's'))
	{
		while (*d)
		{
			len = ft_wcrtomb(str, *(d++));
			if (T_ACCU != 0)
			{
				if ((accurate -= len) < 0)
					return (0);
			}
			if (STR == NULL)
				STR = ft_strdup(str);
			else
				STR = ft_strjoin_free(STR, str, FREE_S1);
		}
	}
	return (0);
}

int		wint_t_arg(wchar_t d, char op, t_flag *buf)
{
	char str[5];

	ft_bzero(str, 5);
	if (d == 0)
		T_SPE;
	else if (op == 'C' || op == 'c')
	{
		ft_wcrtomb(str, d);
		if (STR == NULL)
			STR = ft_strdup(str);
		else
			STR = ft_strjoin_free(STR, str, FREE_S1);
	}
	return (0);
}
