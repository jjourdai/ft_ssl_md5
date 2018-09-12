/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 10:00:57 by jjourdai          #+#    #+#             */
/*   Updated: 2018/02/15 12:44:38 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include <limits.h>
# define BUF buf
# define STR (buf)->str
# define T_LEN (buf)->lenght
# define T_NB (buf)->nb
# define T_WIDTH (buf)->width
# define T_ACCU (buf)->accurate
# define FLAG_ON (buf)->flag
# define T_SPACE FLAG_ON = FLAG_ON | (1u << 0)
# define SPACE_T FLAG_ON & (1u << 0)
# define T_ACCU_0 FLAG_ON = FLAG_ON | (1u << 1)
# define ACCU_0_T FLAG_ON & (1u << 1)
# define T_MORE FLAG_ON = FLAG_ON | (1u << 2)
# define MORE_T FLAG_ON & (1u << 2)
# define T_LESS FLAG_ON = FLAG_ON | (1u << 3)
# define LESS_T FLAG_ON & (1u << 3)
# define T_SHARP FLAG_ON = FLAG_ON | (1u << 4)
# define SHARP_T FLAG_ON & (1u << 4)
# define T_ZERO FLAG_ON = FLAG_ON | (1u << 5)
# define ZERO_T FLAG_ON & (1u << 5)
# define T_SPE FLAG_ON = FLAG_ON | (1u << 6)
# define SPE_T FLAG_ON & (1u << 6)
# define FLAG FLAG_ON = FLAG_ON | (1u << 7)
# define FLAG_T FLAG_ON & (1u << 7)
# define G_BUF global->g_buf
# define G_SIZE global->g_size
# define FREE_S1 1
# define FREE_S2 2
# define FREE_S1_S2 3
# define FREE_NOTHING 0

typedef struct		s_flag
{
	char			*str;
	char			lenght;
	int				nb;
	int				width;
	int				accurate;
	char			flag;
}					t_flag;

typedef struct		s_buf
{
	int		g_size;
	char	g_buf[BUFF_SIZE];
}					t_buf;

int					ft_printf(const char *format, ...);
int					ft_fprintf(int fd, const char *format, ...);
int					ft_sprintf(char *str, const char *format, ...);
int					read_format(const char *format, va_list ap, t_buf *global);
int					parser(const char **format, va_list ap, t_flag *buf, t_buf
					*global);
int					repart(char op, t_flag *tmp, va_list ap, t_buf *global);
int					apply_lenght_arg(long long d, char op, t_flag *buf);
int					s_arg(char *d, char op, t_flag *buf);
int					double_arg(double d, char op, t_flag *buf);
int					without_lenght_arg(int d, char op, t_flag *buf);
int					addr_arg(int *d, t_flag *buf);
int					n_arg(int *d, t_buf *global);
int					read_fd(int d, t_flag *buf);
t_flag				*init_flag_tmp(void);
int					ft_flag(char op, t_flag *buf);
int					wchar_t_arg(wchar_t *d, char op, t_flag *buf);
int					wint_t_arg(wchar_t d, char op, t_flag *buf);
void				f_sharp(t_flag *buf, char op);
void				f_accu(t_flag *buf, char op);
void				f_width(t_flag *buf, char op);
void				f_more(t_flag *buf, char op);
char				*ft_cpychar(char c, int nb);
char				*ft_strcut(char *str, char c);
void				print_exit(t_buf *global, t_flag *buf);
int					flag_register(const char **format, t_flag *buf, char *flag);
void				free_flag_tmp(t_flag *buf);
void				register_simple_flag(char *flag, t_flag *buf);
void				register_buffer(t_buf *global, t_flag *buf);
int					apply_flag_op_0(t_flag *buf, const char **format,
					const char *ptr);
void				op_is_unsigned(char op, t_flag *buf, va_list ap,
					t_buf *global);
void				op_is_signed(char op, t_flag *buf, va_list ap,
					t_buf *global);
void				apply_width_flag(t_flag *buf, char car,
					int size);

#endif
