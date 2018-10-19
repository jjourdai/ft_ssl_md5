/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:50:24 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/15 19:53:54 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static char g_error[][256] = {
	[REQUIRE_ARGUMENT] = "%s: option requires an argument -- %s\n",
	[INVALID_OPTIONS] = "%s: invalid option -- %s\n",
	[INVALID_COMMAND] = "ft_ssl: '%s' is an invalid command.\n",
	[USAGE] = "usage: ft_ssl command [-pqrs] [command args]\n\n"
	"Standard commands:\n\nMessage Digest commands:\nmd5\nsha256\n"
	"\nCipher commands:\nbase64\ndes\ndes-ebc\ndes-cbc\n",
	[WRONG_LENGTH] = "ft_ssl %s: wrong final block length\n",
	[INVALID_KEY] = "ft_ssl des: non-hex digit\ninvalid hex key value\n",
	[READ_ERROR] = "ft_ssl: Read error in %s\n",
	[OPEN_FAILED] = "ft_ssl: %s Open failed for %s\n",
	[WRONG_PASSWD] = "ft_ssl: %s Verify failure\nbad password read\n",
};

static char g_command[][8] = {
	[BASE64] = "base64",
	[MD5] = "md5",
	[SHA256] = "sha256",
	[DES] = "des",
	[DES_ECB] = "des-ecb",
	[DES_CBC] = "des-cbc",
};

void	raise_error(int cmd, int value, char *str, int flag)
{
	if (cmd == GENERAL)
		ft_fprintf(STDERR_FILENO, g_error[value], str);
	else
	{
		if (str)
			ft_fprintf(STDERR_FILENO, g_error[value], g_command[cmd], str);
		else
			ft_fprintf(STDERR_FILENO, g_error[value], g_command[cmd]);
	}
	if (flag == EXIT)
		exit(EXIT_FAILURE);
}
