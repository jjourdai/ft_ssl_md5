/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 13:30:52 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/19 14:01:02 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include "libft.h"
# include "stdint.h"
# include "stdio.h"
# include "fcntl.h"
# include "errno.h"

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

enum	e_lexer_params {
	INIT = 0,
	SHORT_OPT = 1,
	LONG_OPT = 2,
};

enum 	e_base_64 {
	F_INPUT = (1 << 4),
	F_OUPUT = (1 << 5),
	F_DECODE = (1 << 6),
	F_ENCODE = (1 << 7),
};

# define BUFFER_SIZE 512
//# define MACRO_FOR_TEST " (%s) "

# define MACRO_FOR_TEST "(%s)"


typedef struct		s_data {
	uint8_t			flag;
	uint8_t			param_type;
	uint8_t			*string;
	uint8_t			*bytes;
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

#endif
