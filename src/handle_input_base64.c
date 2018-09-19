/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_base64.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 13:24:43 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/19 14:10:56 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "colors.h"

// static int	get_parameters(char **argv, t_data *target, int *already_get,\
// 	int *i)
// {
// 	if (ft_strcmp(argv[*i], "-i") == 0)
// 	{
// 		if (!argv[*i + 1] || argv[*i + 1][0] == '-')
// 		{
// 			ft_fprintf(STDERR_FILENO, RED_TEXT("./ft_ssl opt '%s' need a "
// 				"string after him\n"), argv[*i]);
// 			exit(EXIT_FAILURE);
// 		}
// 		target->bytes = (uint8_t*)argv[*i + 1];
// 		target->param_type = FILE_;
// 		target->string = (uint8_t*)argv[*i + 1];
// 		ft_putendl(target->string);
// 		*i += 1;
// 		return (1);
// 	}
// 	else if (ft_strcmp(argv[*i], "-o") == 0)
// 	{
// 		if (!argv[*i + 1] || argv[*i + 1][0] == '-')
// 		{
// 			ft_fprintf(STDERR_FILENO, RED_TEXT("./ft_ssl opt '%s' need a "
// 				"string after him\n"), argv[*i]);
// 			exit(EXIT_FAILURE);
// 		}
// 		target->string = (uint8_t*)argv[*i];
// 		target->param_type = FILE_;
// 		target->fd = open((char*)argv[*i + 1], O_WRONLY | O_CREAT | O_TRUNC);
// 		*i += 1;
// 		return (1);
// 	}
// 	else
// 	{
// 		ft_putendl("EROOR");
// 	}
// 	return (0);
// }

// void		base64_handle_parameters_and_exec(t_command *cmd, int nb_opt,\
// 	int opt_flag, char **argv)
// {
// 	int		i;
// 	int		nb_target;
// 	int		already_get;
// 	t_data	target;
//
// 	i = nb_opt + 2;
// 	nb_target = 0;
// 	already_get = 0;
// 	while (argv[i])
// 	{
// 		ft_bzero(&target, sizeof(t_data));
// 		target.fd = STDOUT_FILENO;
// 		// nb_target += get_parameters(argv, &target, &already_get, &i);
// 		exec_command(&target, cmd, opt_flag);
// 		if (target.fd != STDOUT_FILENO)
// 			close(target.fd);
// 		i++;
// 	}
// 	if (nb_target == 0)
// 		exec_read_stdin(cmd, opt_flag);
// }
