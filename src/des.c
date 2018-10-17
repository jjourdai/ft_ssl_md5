/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 14:43:53 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/15 16:11:43 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void	display_des(t_data *info, t_command *cmd)
{
	write(info->fd, info->bytes, info->len);
	free(info->bytes);
}

static void		fill_target_struct(t_data *target, t_list *parameters,\
	int opt_flag)
{
	t_list			*tmp;
	t_parameters	*current;

	tmp = parameters;
	target->param_type = STDIN_;
	while (tmp)
	{
		current = (t_parameters*)tmp->content;
		if (current->type == F_OUTPUT)
			target->fd = open(current->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (current->type == F_INPUT || current->type == NONE_)
		{
			target->param_type = FILE_;
			target->string = current->str;
		}
		else if (current->type & F_KEY)
		{
			ft_memcpy(target->key, current->str, SIZE_KEY);
		}
		else if (current->type & F_IVECTOR)
		{
			ft_memcpy(target->iv, current->str, SIZE_KEY);
		}
		else if (current->type & F_SALT)
		{
			ft_memcpy(target->salt, current->str, SIZE_KEY);
		}
		else if (current->type & F_PASSWORD)
		{
			target->password = ft_strdup(current->str);
			// ft_memcpy(target->password, current->str, SIZE_KEY);
		}
		// else if (current->type & F_PASSWORD)
		// 	target->password = current->str;
		tmp = tmp->next;
	}
	ft_lstdel(&parameters, ft_del);
}

void			run_des_parameters_and_exec(t_command *cmd, t_list *parameters,\
	int opt_flag)
{
	t_data target;

	ft_bzero(&target, sizeof(target));
	target.fd = STDOUT_FILENO;
	fill_target_struct(&target, parameters, opt_flag);
	if (target.param_type == STDIN_)
		exec_read_stdin(cmd, opt_flag, &target);
	else
		exec_command(&target, cmd, opt_flag);
	if (target.fd != STDOUT_FILENO && target.fd != -1)
		close(target.fd);
}

void			pbkdf2(char *password, uint64_t salt, uint64_t iteration_count, uint64_t derived_key_length)
{
	// srand(time(NULL));

	// ft_printf("%llx\n", rand());
	// fprintf(stdout, "%llx\n", (unsigned long long)time(NULL));
}

void			des_cbc(t_data *info)
{
	uint64_t	iv;
	size_t		len_key;
	if ((len_key = ft_strlen((char*)info->iv)) > 16)
		info->iv[16] = 0;
	else if (len_key < 16)
	{
		ft_memset(info->iv + len_key, '0', SIZE_KEY - len_key);
		info->iv[16] = 0;
	}
	if (!(iv = ft_atoi_base_64((char*)info->iv, "0123456789ABCDEF")))
		raise_error(DES, INVALID_KEY, NULL ,EXIT);
	if (info->flag & F_DECRYPT)
		des_cbc_decrypt(info, iv);
	else
		des_cbc_encrypt(info, iv);
}

void			des_ecb(t_data *info)
{
	#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/crypto.h>>

	ft_putendl(info->password);
	ft_putendl(info->salt);
// salt=99682010C28DC209
// key=27959D4D9D69EF08
	
	 const EVP_CIPHER *cipher;
    const EVP_MD *dgst = NULL;
    unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];
    const char *password = info->password;
	uint64_t lol = SWAP_VALUE(ft_atoi_base_64(info->salt, "0123456789ABCDEF"));
    const unsigned char *salt = (unsigned char*)&lol;
    int i;

    OpenSSL_add_all_algorithms();

    cipher = EVP_get_cipherbyname("des-ecb");
    // if(!cipher) { fprintf(stderr, "no such cipher\n"); return 1; }

    dgst=EVP_get_digestbyname("md5");
    // if(!dgst) { fprintf(stderr, "no such digest\n"); return 1; }

    if(!EVP_BytesToKey(cipher, dgst, salt,
        (unsigned char *) password,
        strlen(password), 1, key, iv))
    {
        fprintf(stderr, "EVP_BytesToKey failed\n");
        // return 1;
    }
    printf("Key: "); for(i=0; i<cipher->key_len; ++i) { printf("%02x", key[i]); } printf("\n");
	// unsigned char *ptr = malloc(16);
	// i = 1;
	// PKCS5_PBKDF2_HMAC(password, strlen(password), NULL, 0, i, EVP_md5(), 16, ptr);
    // printf("Key: "); for(i=0; i<cipher->key_len; ++i) { printf("%02x", ptr[i]); } printf("\n");
	// ft_fprintf(2, "Swap with i = %d %llX\n", i, SWAP_VALUE(*((uint64_t*)ptr)));
	// ft_putendl(NULL);
	// }
	if (info->password[0] == 0)
	{
		//getch passowrd in stdin
	}
	if (info->salt[0] == 0)
	{
		//generate salt
	}
	if (info->key[0] == 0)
	{
		//generate key
		// pbkdf2(NULL, 0, 0, 0);

	}
	if (info->flag & F_DECRYPT)
		des_ecb_decrypt(info);
	else
		des_ecb_encrypt(info);
}
