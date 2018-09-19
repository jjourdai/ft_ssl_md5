/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 12:28:59 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/19 14:01:29 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>
#include <colors.h>

static t_command *get_function(char *str)
{
	size_t		i;
	static t_command cmd[][6] = {
		[MD5] = {{MD5, "md5", md5, get_params_hash_function, display_hash}},
		[SHA256] = {{SHA256, "sha256", sha256, get_params_hash_function, display_hash}},
		[BASE64] = {{BASE64, "base64", base64, get_params_base64, display_base64}},
		[END] = {{0, NULL, NULL, NULL, NULL}},
	};

	i = -1;
	while (++i < END)
	{
		if (ft_strcmp(cmd[i]->string, str) == 0)
			return (cmd[i]);
	}
	ft_fprintf(STDERR_FILENO, RED_TEXT("ft_ssl: '%s' is an invalid "
				"command.\n"), str);
	return (NULL);
}

int				main(int argc, char **argv)
{
	t_command *cmd;
	int	command;

	command = 0;
	if (argc == 1)
		ft_putendl(RED_TEXT("usage: ft_ssl command [-pqrs] [command args]\n\n"
			"Standard commands:\n\nMessage Digest commands:\nmd5\nsha256\n"));
	else
	{
		if ((cmd = get_function(argv[1])) == NULL)
			return (EXIT_FAILURE);
		cmd->get_params(cmd, argv);
	}
	return (EXIT_SUCCESS);
}
