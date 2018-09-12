/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 13:30:52 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/12 15:52:14 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include "libft.h"
# include "stdint.h"
# include "stdio.h"

#define LEFT_ROTATE(X, C) ((X << C) | (X >> (32 - C)))

#define RIGHT_ROTATE(X, C) ((X >> C) | (X << (32 - C)))
#define SWAP_VALUE(X) swap_bigendian_littleendian(X, sizeof(X))
//#define INITIAL_VALUE = 0x67452301efcdab8998badcfe10325476;

// uint64_t	origin_string_to_padded_string(char **str);


void	md5(char *str);
void	sha256(char *str);

#endif
