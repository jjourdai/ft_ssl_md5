/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:20:09 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/18 17:48:17 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# define BUFF_SIZE 4096

typedef struct		s_fd
{
	int				fd;
	char			*str;
	struct s_fd		*next;
}					t_fd;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_btree
{
	struct s_btree	*right;
	struct s_btree	*left;
	void			*item;
}					t_btree;

typedef int			t_bool;

void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_memcmp_ignorecase(const void *s1, const void *s2,
					size_t n);
size_t				ft_strlen(const char *s);
size_t				ft_strlen_without_char(const char *s, char c);
char				*ft_strdup(const char *s);
char				*ft_strdup_without_char(const char *s, char c);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strlcpy(char *dest, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strrnchr(const char *s, int c, size_t max);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strrstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strnstraf(const char *big, const char *little,
						size_t len);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strcmplen(const char *s1, const char *s2);
int					ft_strcmp_ignorecase(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
unsigned int		ft_atoi_u(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
t_bool				ft_is_this_char(int c, char charact);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				**ft_split(const char *s, char *charset);
void				ft_putchar(unsigned int value);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				*ft_print_memory(void *addr, unsigned int size);
void				ft_putnbr_base(int nbr, char *base);
void				ft_putlong_base(long nbr, char *base);
int					ft_atoi_base(char *str, char *base);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lststrsplit(char const *s, char c);
t_list				*ft_lstatoisplit(char const *s, char c);
void				ft_lst_merge(t_list **begin_list1, t_list *begin_list2);
char				*ft_strncat(char *dst, const char *src, size_t n);
void				ft_lstreverse(t_list **elem);
unsigned long long	ft_convert_decitooctal(unsigned long long deci);
char				*ft_strndup(const char *s, size_t size_max);
char				*ft_strnjoin(const char *s1, const char *s2, size_t size);
void				ft_del(void *content, size_t content_size);
char				*ft_itoa(int n);
char				*ft_itoa_h(short int n);
char				*ft_itoa_uh(unsigned short int n);
char				*ft_itoa_hh(char n);
char				*ft_itoa_uhh(unsigned char n);
char				*ft_itoa_u(unsigned int n);
char				*ft_itoa_ll(long long n);
char				*ft_itoa_ull(unsigned long long n);
char				*ft_itoa_l(long n);
char				*ft_itoa_ul(unsigned long n);
char				*ft_itoa_ulong(unsigned long long n);
char				*ft_itoa_base(int n, char *base);
char				*ft_itoa_base_ll(long long n, char *base);
char				*ft_itoa_base_l(long n, char *base);
char				*ft_itoa_base_ul(unsigned long n, char *base);
char				*ft_itoa_base_ull(unsigned long long n, char *base);
char				*ft_itoa_base_uint(unsigned int n, char *base);
char				*ft_itoa_0x(void *n, char *base);
char				*ft_itoa_base_h(short int n, char *base);
char				*ft_itoa_base_uh(unsigned short int n, char *base);
char				*ft_itoa_base_hh(char n, char *base);
char				*ft_itoa_base_uhh(unsigned char n, char *base);
char				*ft_strchr_base(char *str, char *base);
size_t				ft_strwlen(const wchar_t *s);
unsigned int		ft_int_size(int c);
char				*ft_strjoin_free(char *s1, char *s2, int free_s1_or_s2);
void				print_bits(int64_t octet);
size_t				ft_wcrtomb(char *s, wchar_t d);
void				ft_putnstr(char *str, size_t n);
void				ft_putbuf(char *dest, const char *src, int *len_buf);
void				ft_putnbuf(char *dest, const char *src, int *len_buf,
					int n);
char				*ft_strjoin_size(char *s1, char *s2, int len_s1,
					int len_s2);
char				*ft_strcut(char *str, char c);
int					get_next_line(const int fd, char **line);
int					ft_is_sort(int *tab, int lenght, int (*f)(int, int));
t_bool				ft_list_is_sort(t_list *p_a, t_bool order);
int					ft_lst_not_sort(t_list *p_a, t_bool order);
int					ft_list_size(t_list *begin_list);
int					ft_printf(const char *format, ...);
int					ft_fprintf(int fd, const char *format, ...);
int					ft_sprintf(char *str, const char *format, ...);
int					ft_list_find(t_list *begin_list, int nb);
int					ft_list_find_less(t_list *begin_list, int nb);
int					ft_list_find_more(t_list *begin_list, int nb);
int					ft_count_less(t_list *lst, int nb);
void				ft_insertion_sort(int *tab, size_t size);
void				ft_quick_sort(int *tab, int start, int end);
t_bool				ft_str_is_only_digit(char *str);
void				ft_error(int nb, char *str);
int					ft_count_char(char *str, char c);
void				ft_memalloc_failure(int nb, char *str);
char				**ft_parser_flag(char **argv);
void				ft_swap_tab_int(int **tab, int i, int j);
void				ft_swap_tab_char(char **tab, int i, int j);

t_btree				*btree_create_node(void *item);
void				btree_apply_prefix(t_btree *root, void (*applyf)(void*));
void				btree_apply_infix(t_btree *root, void (*applyf)(void*));
void				btree_apply_suffix(t_btree *root, void (*applyf)(void*));
void				btree_insert_data(t_btree **root, void *item,
int (cmpf)(void*, void*));
void				*btree_search_item(t_btree *root, void *data_ref,
int	(*cmpf)(void *, void*));
int					btree_level_count(t_btree *root);
uint64_t			ft_atoi_base_64(char *str, char *base);
uint64_t			swap_bigendian_littleendian(uint64_t number, \
	size_t sizeoff);
void				ft_toupper_str(char *str, size_t len);
#endif
