/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 13:26:47 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/16 16:43:57 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "colors.h"

static int	get_parameters(char **argv, t_data *target, int *already_get,\
	int *i)
{
	if (*already_get == 0 && ft_strcmp(argv[*i], "-s") == 0)
	{
		if (!argv[*i + 1] || argv[*i + 1][0] == '-')
		{
			ft_fprintf(STDERR_FILENO, RED_TEXT("./ft_ssl opt '-s' need a "
				"string after him\n"));
			exit(EXIT_FAILURE);
		}
		*already_get = 1;
		target->bytes = (uint8_t*)argv[*i + 1];
		target->param_type = STRING_;
		target->string = (uint8_t*)argv[*i + 1];
		*i += 1;
		return (1);
	}
	else
	{
		target->string = (uint8_t*)argv[*i];
		target->param_type = FILE_;
		return (1);
	}
	return (0);
}

void		handle_parameters_and_exec(int command, int nb_opt,\
	int opt_flag, char **argv)
{
	int		i;
	int		nb_target;
	int		already_get;
	t_data	target;

	i = nb_opt + 2;
	nb_target = 0;
	already_get = 0;
	while (argv[i])
	{
		ft_bzero(&target, sizeof(t_data));
		nb_target += get_parameters(argv, &target, &already_get, &i);
		exec_command(&target, command, opt_flag);
		i++;
	}
	if (nb_target == 0)
		exec_read_stdin(command, opt_flag);
}
