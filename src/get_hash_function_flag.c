/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hash_function_flag.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 13:14:36 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/19 13:25:36 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>
#include <colors.h>

static t_bool	store_flag(t_command *cmd, char *str, int *opt_flag, int j)
{
	char	c;

	if ((c = str[j]))
	{
		if (store_flag(cmd, str, opt_flag, j + 1) == ERROR)
			return (ERROR);
		if (c == 'p')
			(*opt_flag) |= F_ECHO;
		else if (c == 'q')
			(*opt_flag) |= F_QUIET;
		else if (c == 'r')
			(*opt_flag) |= F_REVERSE;
		else if (c == 's')
			return (ERROR);
		else
		{
			ft_fprintf(STDERR_FILENO, RED_TEXT("ft_ssl %s: '-%c' is an "
						"invalid option/flag.\n"), cmd->string,c);
			exit(EXIT_FAILURE);
		}
	}
	return (SUCCESS);
}

static int		get_flag(t_command *cmd, char **argv, int *opt_flag)
{
	int		i;
	int		nb_opt;

	i = 1;
	nb_opt = 0;
	while (argv[++i] && argv[i][0] == '-')
	{
		if (store_flag(cmd, argv[i], opt_flag, 1) == SUCCESS)
			nb_opt++;
		else
			break ;
	}
	return (nb_opt);
}

void 				get_params_hash_function(t_command *cmd, char**argv)
{
	int	nb_opt;
	int	opt_flag;

	opt_flag = 0;
	nb_opt = get_flag(cmd, argv, &opt_flag);
	hash_f_handle_parameters_and_exec(cmd, nb_opt, opt_flag, argv);
}
