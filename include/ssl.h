/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 13:30:52 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/22 14:50:40 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include "libft.h"
# include "stdint.h"
# include "stdio.h"
# include "fcntl.h"
# include "errno.h"

# define L_ROT_64(X, C) ((X << C) | (X >> (64 - C)))
# define R_ROT_64(X, C) ((X >> C) | (X << (64 - C)))

# define L_ROT_56(X, C) ((X << C) | (X >> (56 - C)))
# define R_ROT_56(X, C) ((X >> C) | (X << (56 - C)))

# define L_ROT_28(X, C) ((X << C) | (X >> (28 - C)))
# define R_ROT_28(X, C) ((X >> C) | (X << (28 - C)))

# define L_ROT(X, C) ((X << C) | (X >> (32 - C)))
# define R_ROT(X, C) ((X >> C) | (X << (32 - C)))
# define SWAP_VALUE(X) swap_bigendian_littleendian(X, sizeof(X))

# define CH(X) ((X[4] & X[5]) ^ ((~X[4]) & X[6]))
# define MAJ(X) ((X[0] & X[1]) ^ (X[0] & X[2]) ^ (X[1] & X[2]))
# define S1(X) ((R_ROT(X[4], 6)) ^ (R_ROT(X[4], 11)) ^ (R_ROT(X[4], 25)))
# define S0(X) ((R_ROT(X[0], 2)) ^ (R_ROT(X[0], 13)) ^ (R_ROT(X[0], 22)))

//fd stderr sur l'usage
enum	e_macro {
	ERROR,
	SUCCESS,
	DATA_RECEIVED,
	DATA_NOT_RECEIVED,
};

enum	e_param_type {
	MD5 = 0,
	SHA256 = 1,
	BASE64 = 2,
	DES,
	END,
	FILE_,
	STDIN_,
	STRING_,
	NONE_,
};

enum 	e_hash_function {
	F_ECHO  = (1 << 0),
	F_QUIET  = (1 << 1),
	F_REVERSE  = (1 << 2),
	F_STRING  = (1 << 3),
};

enum 	e_base_64 {
	F_INPUT = (1 << 4),
	F_OUPUT = (1 << 5),
	F_DECODE = (1 << 6),
	F_ENCODE = (1 << 7),
};

enum 	e_des {
	F_BASE64 = (1 << 8),
	F_DECRYPT = (1 << 9),
	F_ENCRYPT = (1 << 10),
	F_KEY = (1 << 11),
	F_PASSWORD = (1 << 12),
	F_SALT = (1 << 13),
	F_VECTOR = (1 << 14),
};

# define BUFFER_SIZE 512
//# define MACRO_FOR_TEST " (%s) "

# define MACRO_FOR_TEST "(%s)"


typedef struct		s_data {
	uint16_t			flag;
	uint8_t			param_type;
	uint8_t			*string;
	uint8_t			*bytes;
	uint8_t			*key;
	uint64_t		len;
	int				fd;
	uint32_t		final_hash[8];
}					t_data;

typedef struct		s_command {
	int				command;
	char			*string;
	void			(*exec_command)(struct s_data*);
	void			(*get_params)(struct s_command*, t_list*, int);
	void			(*display)(struct s_data*, struct s_command *);
}					t_command;

typedef struct		s_parameters {
	char 			*str;
	int			type;
}			t_parameters;

typedef struct		s_option {
	char 			*longname;
	char 			shortname;
	int				flag;
	t_parameters	*(*f) (char*, int);
}			t_option;

void				md5(t_data *info);
void				sha256(t_data *info);

void				display_hash(t_data *target, t_command *cmd);
void 				get_params_hash_function(t_command *, t_list*, int);
void				run_parameters_and_exec(t_command *cmd, t_list *parameters, int opt_flag);
void				exec_command(t_data *target, t_command *cmd, int opt_flag);
void				exec_read_stdin(t_command *cmd, int opt_flag);

void				base64(t_data *info);

void	display_base64(t_data *info, t_command *cmd);
void 				get_params_base64(t_command *, t_list*, int);
void		base64_handle_parameters_and_exec(t_command *cmd, int nb_opt,\
int opt_flag, char **argv);
t_list	*get_params(char **argv, int argc, int index, int *flag);

void				des(t_data *info);

void	display_des(t_data *info, t_command *cmd);
void	run_des_parameters_and_exec(t_command *, t_list *, int opt_flag);

void get_keys(uint64_t keys[16], char *key, size_t len);
void 	des_encrypt(t_data *info);
void 	des_decrypt(t_data *info);

// char *put_padding_character(t_data *info);
uint64_t reverse_permutation(uint64_t old_block);
uint64_t substitutions(uint64_t d0);
uint64_t	initial_permutation(char *bytes);
uint64_t	expansion(uint32_t bytes);

#endif
