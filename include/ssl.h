/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 13:30:52 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/22 16:24:35 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include "libft.h"
# include "stdint.h"
# include "stdio.h"
# include "fcntl.h"
# include "errno.h"

# define COUNT_OF(ptr) (sizeof(ptr) / sizeof((ptr)[0]))

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

# define BUFFER_SIZE 512
# define MACRO_FOR_TEST "(%s)"
# define SALTED "Salted__"

enum	e_macro {
	ERROR,
	SUCCESS,
	true,
	false,
	DATA_RECEIVED,
	DATA_NOT_RECEIVED,
};

enum	e_param_type {
	MD5 = 0,
	SHA256 = 1,
	BASE64 = 2,
	DES,
	DES_ECB,
	DES_CBC,
	DES3,
	GENRSA,
	END,
	FILE_,
	STDIN_,
	STRING_,
	NONE_,
};

enum	e_error {
	REQUIRE_ARGUMENT,
	INVALID_OPTIONS,
	INVALID_COMMAND,
	WRONG_LENGTH,
	INVALID_KEY,
	OPEN_FAILED,
	USAGE,
	GENERAL,
	READ_ERROR,
	WRONG_PASSWD,
	BAD_MAGIC_NUMBER,
	EXIT,
};

enum	e_hash_function {
	F_ECHO = (1 << 0),
	F_QUIET = (1 << 1),
	F_REVERSE = (1 << 2),
	F_STRING = (1 << 3),
};

enum	e_base_64 {
	F_INPUT = (1 << 4),
	F_OUTPUT = (1 << 5),
	F_DECODE = (1 << 6),
	F_ENCODE = (1 << 7),
};

enum	e_des {
	F_BASE64 = (1 << 8),
	F_DECRYPT = (1 << 9),
	F_ENCRYPT = (1 << 10),
	F_KEY = (1 << 11),
	F_PASSWORD = (1 << 12),
	F_SALT = (1 << 13),
	F_IVECTOR = (1 << 14),
	DES3_KEY_LEN = 64,
	DES_KEY_LEN = 16,
	PASSWORD_LEN = 128,
};

enum	e_rsa {
	F_RANDOM = (1 << 15),

};

typedef struct		s_argv {
	int				i;
	int				j;
	char			**argv;
}					t_argv;

typedef struct		s_data {
	uint16_t		flag;
	uint8_t			param_type;
	uint8_t			*string;
	uint8_t			*bytes;
	uint8_t			key[DES3_KEY_LEN + 1];
	uint8_t			iv[DES_KEY_LEN + 1];
	uint8_t			salt[DES_KEY_LEN + 1];
	uint8_t			password[PASSWORD_LEN + 1];
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
	char			*str;
	int				type;
}					t_parameters;

typedef struct		s_option {
	char			*longname;
	char			shortname;
	int				flag;
	t_parameters	*(*f) (char*, int);
}					t_option;

void				md5(t_data *info);
void				sha256(t_data *info);
void				display_hash(t_data *target, t_command *cmd);
void				get_params_hash_function(t_command *cmd,\
	t_list *list, int nb);
void				run_parameters_and_exec(t_command *cmd,\
	t_list *parameters, int opt_flag);
void				exec_command(t_data *target, t_command *cmd, int opt_flag);
void				exec_read_stdin(t_command *cmd,\
	int opt_flag, t_data *target);

void				base64(t_data *info);

void				display_base64(t_data *info, t_command *cmd);
void				get_params_base64(t_command *cmd, t_list *list, int nb);
void				base64_handle_parameters_and_exec(t_command *cmd,\
	int nb_opt,\
	int opt_flag, char **argv);
t_list				*get_params(char **argv, int argc, int index, int *flag);
void				des_ecb(t_data *info);
void				des_cbc(t_data *info);
void				display_des(t_data *info, t_command *cmd);
void				run_des_parameters_and_exec(t_command *cmd,\
	t_list *list, int opt_flag);
void				get_keys(uint64_t keys[16], char *key, size_t len);
void				des_ecb_encrypt(t_data *info, char *result);
void				des_ecb_decrypt(t_data *info);
void				des_cbc_encrypt(t_data *info, uint64_t iv, char *result);
void				des_cbc_decrypt(t_data *info, uint64_t iv);
void				des3_encrypt(t_data *info, uint64_t iv,\
	char *encrypted_string);
void				des3_decrypt(t_data *info, uint64_t iv,\
	char *decrypted_string);
uint64_t			reverse_permutation(uint64_t old_block);
uint64_t			substitutions(uint64_t d0);
uint64_t			initial_permutation(uint64_t block);
uint64_t			expansion(uint32_t bytes);
void				raise_error(int cmd, int value, char *str, int flag);
void				base64_decode(t_data *info);
void				base64_encode(t_data *info);
uint64_t			iv_or_salt_generator(void);
uint64_t			iv_or_salt_str_to_bytes(char str[17]);
char				*wrap_getpass(t_data *info);
t_command			*get_function(char *str);
char				*int_to_char(t_data *target, size_t length, int command);
void				check_if_corrupted(int cmd, t_data *info);
char				*generate_key(uint64_t salt, char *password);
char				*generate_key_des3(uint64_t salt, char *password);
void				des3(t_data *info);
void				check_if_corrupted_padding_after_decrypt(t_data *info);
void				padd_key(char *key, size_t klen, size_t len);
char				*put_padding_character(t_data *info);
void				remove_salted(t_data *info);
uint64_t			update_block_cbc_encrypt(uint64_t keys[16],\
	uint64_t iv, uint64_t block);
uint64_t			update_block_cbc_decrypt(uint64_t keys[16],\
	uint64_t iv, uint64_t block);
void				add_salted(t_data *info, uint64_t salt);
void    genrsa(t_data *info);
void    display_rsa(t_data *info, struct s_command *cmd);

#endif
