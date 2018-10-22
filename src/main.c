/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 12:28:59 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/22 14:46:44 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>
#include <colors.h>

static t_command	g_cmd[][6] = {
	[MD5] = {{MD5, "md5", md5, run_parameters_and_exec, display_hash}},
	[SHA256] = {{SHA256, "sha256", sha256, run_parameters_and_exec,\
			display_hash}},
	[BASE64] = {{BASE64, "base64", base64, get_params_base64, display_base64}},
	[DES] = {{DES, "des", des_ecb, run_des_parameters_and_exec, display_des}},
	[DES_ECB] = {{DES_ECB, "des-ecb", des_ecb, run_des_parameters_and_exec,\
			display_des}},
	[DES_CBC] = {{DES_CBC, "des-cbc", des_cbc, run_des_parameters_and_exec,\
			display_des}},
	[DES3] = {{DES3, "des3", des3, run_des_parameters_and_exec,\
			display_des}},
};

t_command	*get_function(char *str)
{
	size_t				i;

	i = -1;
	while (++i < COUNT_OF(g_cmd))
	{
		if (ft_strcmp(g_cmd[i]->string, str) == 0)
			return (g_cmd[i]);
	}
	raise_error(GENERAL, INVALID_COMMAND, str, EXIT);
	return (NULL);
}

int			main(int argc, char **argv)
{
	t_command	*cmd;
	t_list		*parameters;
	int			flag;

	flag = 0;
	if (argc == 1)
		raise_error(GENERAL, USAGE, NULL, EXIT);
	else
	{
		if ((cmd = get_function(argv[1])) == NULL)
			return (EXIT_FAILURE);
		parameters = get_params(argv, argc, cmd->command, &flag);
		cmd->get_params(cmd, parameters, flag);
	}
	return (EXIT_SUCCESS);
}
