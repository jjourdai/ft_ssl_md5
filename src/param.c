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

void	longname_opt(char *str)
{
	ft_putendl(str);
}

t_parameters *store_parameters(char *str, int flag)
{
	t_parameters *new_param;

	new_param = ft_memalloc(sizeof(t_parameters));
	new_param->str = str;
	new_param->type = flag;
//	ft_putendl(str);
	return (new_param);
}

static t_option base64_opt[][256] = {
	[BASE64] = {
		{"decode", 'd', F_DECODE, NULL},
		{"encode", 'e', F_ENCODE, NULL},
		{"input", 'i', F_INPUT, store_parameters},
		{"ouput", 'o', F_OUPUT, store_parameters},
		{NULL, 0, 0, NULL},
	},
	[MD5] = {
		{"print", 'p', F_ECHO, NULL},
		{"quiet", 'q', F_QUIET, NULL},
		{"reverse", 'r', F_REVERSE, NULL},
		{"string", 's', F_STRING, store_parameters},
		{NULL, 0, 0, NULL},
	},
	[SHA256] = {
		{"print", 'p', F_ECHO, NULL},
		{"quiet", 'q', F_QUIET, NULL},
		{"reverse", 'r', F_REVERSE, NULL},
		{"string", 's', F_STRING, store_parameters},
		{NULL, 0, 0, NULL},
	},
	[DES] = {
		{"", 'a', F_LOL, NULL},
		{"decrypt", 'd', F_DECRYPT, NULL},
		{"encrypt", 'e', F_ENCRYPT, NULL},
		{"input", 'i', F_INPUT, store_parameters},
		{"key", 'k', F_KEY, store_parameters},
		{"output", 'o', F_OUPUT, store_parameters},
		{"password", 'p', F_PASSWORD, store_parameters},
		{"salt", 's', F_SALT, store_parameters},
		{"initvector", 'v', F_VECTOR, store_parameters},
		{NULL, 0, 0, NULL},
	},
};

t_parameters *shortname_opt(char **argv, int *i, int command, int *flag)
{
	int		j;
	int		opt_index;
	char	c;
	int		flag_has_found;

	j = 0;
	while ((c = argv[*i][++j]))
	{
		opt_index = -1;
		flag_has_found = 0;
		while (base64_opt[command][++opt_index].shortname)
		{
			if (base64_opt[command][opt_index].shortname == c)
			{
				flag_has_found = 1;
				*flag |= base64_opt[command][opt_index].flag;
				//ft_printf("%c\n", c);
				if (base64_opt[command][opt_index].f != NULL)
				{
					if (argv[*i][j + 1] != '\0')
						return (base64_opt[command][opt_index].f(&argv[*i][j + 1], base64_opt[command][opt_index].flag));
					else if (argv[*i + 1] != NULL)
						return (base64_opt[command][opt_index].f(argv[++(*i)], base64_opt[command][opt_index].flag));
					else
					{
						ft_fprintf(STDERR_FILENO, "base64: option requires an argument -- %c\n", c);
						exit(EXIT_FAILURE);
					}
					return (NULL);
				}
			}
		}
		if (flag_has_found != 1)
		{
			ft_fprintf(STDERR_FILENO, "base64: invalid option -- %c\n", c);
			exit(EXIT_FAILURE);
		}
		//ft_printf("%c\n", argv[i][j]);
	}
	return (NULL);
}

t_list		*get_params(char **argv, int argc, int command, int *flag)
{
	int i;
	t_parameters *new_params;
	t_list *parameters;

	i = 1;
	parameters = NULL;
	while (++i < argc)
	{
		if (ft_strncmp(argv[i], "--", 2) == 0)
		{
			longname_opt(argv[1]);
		}
		else if (argv[i][0] == '-')
		{
			if ((new_params = shortname_opt(argv, &i, command, flag)) != NULL)
				ft_lstadd_back(&parameters, ft_lstnew(new_params, sizeof(t_parameters)));
		}
		else
			ft_lstadd_back(&parameters, ft_lstnew(store_parameters(argv[i], NONE_), sizeof(t_parameters)));
	}
	//ft_printf("%b\n", *flag);
	return (parameters);
}
