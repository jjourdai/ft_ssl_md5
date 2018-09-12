/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 10:52:13 by jjourdai          #+#    #+#             */
/*   Updated: 2017/03/03 13:59:17 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flag		*init_flag_tmp(void)
{
	t_flag *buf_tmp;

	buf_tmp = ft_memalloc(sizeof(t_flag));
	return (buf_tmp);
}

int			apply_flag_op_0(t_flag *buf, const char **format, const char *ptr)
{
	STR = ft_strndup(*format, 1);
	if (FLAG_ON || T_ACCU || T_WIDTH)
		ft_flag(0, buf);
	return ((*format - ptr) / 2);
}

void		register_simple_flag(char *flag, t_flag *buf)
{
	if (*flag == ' ')
		T_SPACE;
	else if (*flag == '-')
		T_LESS;
	else if (*flag == '+')
		T_MORE;
	else if (*flag == '#')
		T_SHARP;
	else if (*flag == '0')
		T_ZERO;
}

int			flag_register(const char **format, t_flag *buf, char *flag)
{
	char		*tmp;

	if (flag)
		FLAG;
	if (T_LEN == 0 && (tmp = ft_strchr("hljz", *flag)))
		T_LEN = *tmp;
	else
		T_LEN = ft_toupper((T_LEN));
	if (*flag == '.')
		if (*(*format + 1) <= '9' && *(*format + 1) >= '0')
		{
			if (*(*format + 1) == '0')
				T_ACCU_0;
			return (ft_int_size(T_ACCU = ft_atoi(++(*format))));
		}
		else
			T_ACCU_0;
	else if (ft_strchr(" -+#0", *flag))
		register_simple_flag(flag, buf);
	else if (ft_strchr("0123456789", *flag))
		return (ft_int_size(T_WIDTH = ft_atoi(*format)));
	return (0);
}

int			parser(const char **format, va_list ap, t_flag *buf, t_buf *global)
{
	char		*op;
	char		*flag;
	int			len;
	const char	*ptr;

	ptr = ++(*format);
	while (**format && (op = ft_strchr("bsSpdDioOuUxXcCneEfFgGaA%",
	**format)) == NULL)
	{
		len = 0;
		if ((flag = ft_strchr("hljz.#0123456789-+ *$L’", **format)) != NULL)
			len = flag_register(format, buf, flag);
		if (flag == NULL && !T_WIDTH)
			return (0);
		else if (flag == NULL && FLAG_T)
			return (apply_flag_op_0(buf, format, ptr));
		(*format) += (len + 1);
	}
	if (**format && op)
		if (repart(*op, buf, ap, global) == -1)
			print_exit(global, buf);
	if (op && (FLAG_ON || T_ACCU || T_WIDTH))
		ft_flag(*op, buf);
	return (1);
}
