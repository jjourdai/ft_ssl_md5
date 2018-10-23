/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_rsa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 18:15:09 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/23 18:36:38 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void    random_data_generator(char *buffer, size_t len)
{
    int			fd;

	if ((fd = open("/dev/random", O_RDONLY)) == -1)
		raise_error(DES, OPEN_FAILED, "/dev/random", EXIT);
	read(fd, buffer, len);
	close(fd);
}


int    get_size(uint64_t n)
{
    int     len;
    uint64_t value;

    value = 0xFF00000000000000;
    len = sizeof(uint64_t);
    while (len)
    {
        if (value & n)
            return (len);
        value = value >> 8;
        --len;
    }
    return (0);
}

int    miller_witness(uint64_t number, int a)
{

}

int    miller_rabin(uint64_t number, size_t iter)
{
    //number must be >= 3 and iter must be > 1
    uint64_t    a;
    uint64_t    len_number;
    char        *buffer;

    len_number = get_size(number);
    buffer = ft_memalloc(sizeof(number) * sizeof(char));
    // ft_printf("%llx\n", a);
    while (iter > 0)
    {
        random_data_generator(buffer, len_number);
        a = *((uint64_t*)buffer) % number;
        if (a > 2 && a < number - 2)
            if (miller_witness(a, number))
                return (false);
        --iter;
    }
    ft_memdel((void**)&buffer);
    return (true);
}

void    genrsa(t_data *info)
{
    size_t   len = 8;
    char     *new_data;
    uint64_t value;
  
    new_data = ft_memalloc(sizeof(char) * len);
    random_data_generator(new_data, len);
    value = *((uint64_t*)new_data) | 0x8000000000000001 ;
    ft_memdel((void**)&new_data);
    miller_rabin(1, 10);
}

void    display_rsa(t_data *info, struct s_command *cmd)
{

}