/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 10:52:13 by jjourdai          #+#    #+#             */
/*   Updated: 2018/03/04 16:48:28 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		register_buffer(t_buf *global, t_flag *buf)
{
	if (SPE_T && T_WIDTH)
		ft_putbuf(G_BUF, STR, &G_SIZE);
	if (SPE_T)
		G_BUF[++G_SIZE] = 0;
	else
		ft_putbuf(G_BUF, STR, &G_SIZE);
}

int			read_format(const char *format, va_list ap, t_buf *global)
{
	char	*ptr;
	t_flag	*buf;
	int		len;

	len = 0;
	BUF = init_flag_tmp();
	if (*format != '%')
	{
		if ((ptr = ft_strchr(format, '%')) == NULL)
		{
			ft_putbuf(G_BUF, format, &G_SIZE);
			free_flag_tmp(BUF);
			return (0);
		}
		else
			ft_putnbuf(G_BUF, format, &G_SIZE, (len = ptr - format));
	}
	else
		len = parser(&format, ap, BUF, global);
	if (STR || SPE_T)
		register_buffer(global, buf);
	free_flag_tmp(BUF);
	if (*format)
		read_format(format + (len), ap, global);
	return (0);
}

int			ft_fprintf(int fd, const char *format, ...)
{
	va_list ap;
	int		ret;
	t_buf	*global;

	global = ft_memalloc(sizeof(t_buf));
	G_SIZE = 0;
	ft_bzero(G_BUF, BUFF_SIZE);
	va_start(ap, format);
	ret = read_format(format, ap, global);
	va_end(ap);
	write(fd, G_BUF, G_SIZE % BUFF_SIZE);
	ret = G_SIZE;
	free(global);
	return (ret);
}

int			ft_sprintf(char *str, const char *format, ...)
{
	va_list ap;
	int		ret;
	t_buf	*global;

	global = ft_memalloc(sizeof(t_buf));
	G_SIZE = 0;
	ft_bzero(G_BUF, BUFF_SIZE);
	va_start(ap, format);
	ret = read_format(format, ap, global);
	va_end(ap);
	ft_bzero(str, ft_strlen(str));
	ft_strcat(str, G_BUF);
	ret = G_SIZE;
	free(global);
	return (ret);
}

int			ft_printf(const char *format, ...)
{
	va_list ap;
	int		ret;
	t_buf	*global;

	global = ft_memalloc(sizeof(t_buf));
	G_SIZE = 0;
	ft_bzero(G_BUF, BUFF_SIZE);
	va_start(ap, format);
	ret = read_format(format, ap, global);
	va_end(ap);
	write(1, G_BUF, G_SIZE % BUFF_SIZE);
	ret = G_SIZE;
	free(global);
	return (ret);
}
