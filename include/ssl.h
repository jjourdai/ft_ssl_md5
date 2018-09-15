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
# include "fcntl.h"

# define L_ROT(X, C) ((X << C) | (X >> (32 - C)))
# define R_ROT(X, C) ((X >> C) | (X << (32 - C)))
# define SWAP_VALUE(X) swap_bigendian_littleendian(X, sizeof(X))

# define CH(X) ((X[4] & X[5]) ^ ((~X[4]) & X[6]))
# define MAJ(X) ((X[0] & X[1]) ^ (X[0] & X[2]) ^ (X[1] & X[2]))
# define S1(X) ((R_ROT(X[4], 6)) ^ (R_ROT(X[4], 11)) ^ (R_ROT(X[4], 25)))
# define S0(X) ((R_ROT(X[0], 2)) ^ (R_ROT(X[0], 13)) ^ (R_ROT(X[0], 22)))

enum e_macro {
  ERROR,
  SUCCESS,
  DATA_RECEIVED,
  DATA_NOT_RECEIVED
};

enum e_command {
  MD5 = 0,
  SHA256 = 1,
  END = 2,
};

enum e_param_type {
  FILE_,
  STDIN_,
  STRING_,
};

# define F_ECHO (1 << 0)
# define F_QUIET (1 << 1)
# define F_REVERSE (1 << 2)

// # define PARAM_TYPE_STRING (1 << 0)
// # define PARAM_TYPE_FILE (1 << 1)
// # define PARAM_TYPE_STDIN (1 << 2)

# define BUFFER_SIZE 4096

typedef struct   s_data {
    uint8_t     flag;
    uint8_t     param_type;
    uint8_t     *string;
    uint8_t     *bytes;
    uint64_t    len;
    uint32_t    *final_hash;
}                t_data;

void	md5(t_data *info);
void	sha256(t_data *info);

#endif
