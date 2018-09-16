/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 12:28:59 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/12 15:24:36 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <ssl.h>
#include <colors.h>

int		get_flag(char **argv, int *opt_flag)
{
	int		i;
	int		j;
	char		c;
	int		nb_opt;

	i = 1;
	nb_opt = 0;
	while (argv[++i] && argv[i][0] == '-')
		if (argv[i][0] == '-')
		{
			j = 0;
			while ((c = argv[i][++j]))
			{
				if (c == 'p')
					(*opt_flag) |= F_ECHO;
				else if (c == 'q')
					(*opt_flag) |= F_QUIET;
				else if (c == 'r')
					(*opt_flag) |= F_REVERSE;
				else if (c == 's')
					break ;
				else
				{
					ft_fprintf(STDERR_FILENO, RED_TEXT("ft_ssl: '-%c' is an invalid option/flag.\n"), c);
					exit(EXIT_FAILURE);
				}
				nb_opt++;
			}
		}
	return (nb_opt);
}

t_bool		get_function(char *str, int *flag)
{
	static char command[END][6] = {
		[MD5] = "md5",
		[SHA256] = "sha256",
	};
	size_t i;

	i = -1;
	while (++i < END)
	{
		if (ft_strcmp(command[i], str) == 0)
		{
			*flag = i;
			return (SUCCESS);
		}
	}
	ft_fprintf(STDERR_FILENO, RED_TEXT("ft_ssl: '%s' is an invalid command.\n"), str);
	return (ERROR);
}

int		main(int argc, char **argv)
{
	int	command;
	int	opt_flag;
	int	nb_opt;
	//dont forget to handle malloc_realloc on tab ! ! !

	command = 0;
	if (argc == 1)
		ft_putendl(RED_TEXT("usage: ft_ssl command [-pqrs] [command args]\n\n"
		"Standard commands:\n\nMessage Digest commands:\nmd5\nsha256\n"));
	else
	{
		if (get_function(argv[1], &command) == ERROR)
			return (EXIT_FAILURE);
		nb_opt = get_flag(argv, &opt_flag);
		handle_parameters_and_exec(command, nb_opt, opt_flag, argv);
	}
	return(EXIT_SUCCESS);
}
