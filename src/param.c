/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 12:28:59 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/22 14:43:50 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>
#include <colors.h>

void			longname_opt(char *str)
{
	ft_putendl(str);
}

t_parameters	*store_parameters(char *str, int flag)
{
	t_parameters *new_param;

	new_param = ft_memalloc(sizeof(t_parameters));
	new_param->str = str;
	new_param->type = flag;
	return (new_param);
}

static t_option g_opts[][256] = {
	[BASE64] = {
		{"decode", 'd', F_DECODE, NULL},
		{"encode", 'e', F_ENCODE, NULL},
		{"input", 'i', F_INPUT, store_parameters},
		{"output", 'o', F_OUTPUT, store_parameters},
	},
	[MD5] = {
		{"print", 'p', F_ECHO, NULL},
		{"quiet", 'q', F_QUIET, NULL},
		{"reverse", 'r', F_REVERSE, NULL},
		{"string", 's', F_STRING, store_parameters},
	},
	[SHA256] = {
		{"print", 'p', F_ECHO, NULL},
		{"quiet", 'q', F_QUIET, NULL},
		{"reverse", 'r', F_REVERSE, NULL},
		{"string", 's', F_STRING, store_parameters},
	},
	[DES] = {
		{"base64", 'a', F_BASE64, NULL},
		{"decrypt", 'd', F_DECRYPT, NULL},
		{"encrypt", 'e', F_ENCRYPT, NULL},
		{"input", 'i', F_INPUT, store_parameters},
		{"key", 'k', F_KEY, store_parameters},
		{"output", 'o', F_OUTPUT, store_parameters},
		{"password", 'p', F_PASSWORD, store_parameters},
		{"salt", 's', F_SALT, store_parameters},
		{"initvector", 'v', F_IVECTOR, store_parameters},
	},
	[DES_ECB] = {
		{"base64", 'a', F_BASE64, NULL},
		{"decrypt", 'd', F_DECRYPT, NULL},
		{"encrypt", 'e', F_ENCRYPT, NULL},
		{"input", 'i', F_INPUT, store_parameters},
		{"key", 'k', F_KEY, store_parameters},
		{"output", 'o', F_OUTPUT, store_parameters},
		{"password", 'p', F_PASSWORD, store_parameters},
		{"salt", 's', F_SALT, store_parameters},
		{"initvector", 'v', F_IVECTOR, store_parameters},
	},
	[DES_CBC] = {
		{"base64", 'a', F_BASE64, NULL},
		{"decrypt", 'd', F_DECRYPT, NULL},
		{"encrypt", 'e', F_ENCRYPT, NULL},
		{"input", 'i', F_INPUT, store_parameters},
		{"key", 'k', F_KEY, store_parameters},
		{"output", 'o', F_OUTPUT, store_parameters},
		{"password", 'p', F_PASSWORD, store_parameters},
		{"salt", 's', F_SALT, store_parameters},
		{"initvector", 'v', F_IVECTOR, store_parameters},
	},
	[DES3] = {
		{"base64", 'a', F_BASE64, NULL},
		{"decrypt", 'd', F_DECRYPT, NULL},
		{"encrypt", 'e', F_ENCRYPT, NULL},
		{"input", 'i', F_INPUT, store_parameters},
		{"key", 'k', F_KEY, store_parameters},
		{"output", 'o', F_OUTPUT, store_parameters},
		{"password", 'p', F_PASSWORD, store_parameters},
		{"salt", 's', F_SALT, store_parameters},
		{"initvector", 'v', F_IVECTOR, store_parameters},
	},
};

t_parameters	*test_options(t_argv *info, int command, int opt_index, char c)
{
	if (g_opts[command][opt_index].f != NULL)
	{
		if (info->argv[info->i][info->j + 1] != '\0')
			return (g_opts[command][opt_index].f(&info->argv[info->i][info->j\
				+ 1], g_opts[command][opt_index].flag));
		else if (info->argv[info->i + 1] != NULL)
			return (g_opts[command][opt_index].f(info->argv[++(info->i)],\
				g_opts[command][opt_index].flag));
		else
			raise_error(command, REQUIRE_ARGUMENT, &c, EXIT);
	}
	return (NULL);
}

t_parameters	*shortname_opt(t_argv *info, int command, int *flag)
{
	int		opt_index;
	char	c;
	int		flag_has_found;
	t_parameters	*new;

	info->j = 0;
	while ((c = info->argv[info->i][++info->j]))
	{
		opt_index = -1;
		flag_has_found = 0;
		while (g_opts[command][++opt_index].shortname)
		{
			if (g_opts[command][opt_index].shortname == c)
			{
				flag_has_found = 1;
				*flag |= g_opts[command][opt_index].flag;
				if ((new = test_options(info, command, opt_index, c)) != NULL)
					return (new);
			}
		}
		if (flag_has_found != 1)
			raise_error(command, INVALID_OPTIONS, &c, EXIT);
	}
	return (NULL);
}

t_list			*get_params(char **argv, int argc, int command, int *flag)
{
	t_parameters	*new_params;
	t_list			*parameters;
	t_argv			info;

	parameters = NULL;
	ft_bzero(&info, sizeof(info));
	info.i = 1;
	info.argv = argv;
	while (++info.i < argc)
	{
		if (ft_strncmp(argv[info.i], "--", 2) == 0)
		{
			longname_opt(argv[1]);
		}
		else if (argv[info.i][0] == '-')
		{
			if ((new_params = shortname_opt(&info, command, flag)) != NULL)
				ft_lstadd_back(&parameters, ft_lstnew(new_params,\
					sizeof(t_parameters)));
		}
		else
			ft_lstadd_back(&parameters, ft_lstnew(\
			store_parameters(argv[info.i], NONE_), sizeof(t_parameters)));
	}
	return (parameters);
}
