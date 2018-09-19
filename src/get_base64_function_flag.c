/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_base64_function_flag.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 13:16:45 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/19 14:43:34 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>
#include <colors.h>

static void		get_flag(t_data *target, char **argv, int *opt_flag)
{
	int		i;
	int		j;
	char 	c;

	i = 1;
	target->param_type = STDIN_;
	while (argv[++i])
	{
		j = 1;
		if (argv[i][0] == '-')
		{
			while ((c = argv[i][j]))
			{
				if (c == 'd')
				(*opt_flag) |= F_DECODE;
				else if (c == 'e')
				(*opt_flag) |= F_ENCODE;
				else if (c == 'i' || c == 'o')
				{
					if (argv[i + 1] == NULL)
					{
						ft_fprintf(STDERR_FILENO, RED_TEXT("ft_ssl base64: options"
						" '-%c' required an argument.\n"), c);
						exit(EXIT_FAILURE);
					}
					if (c == 'i')
					{
						target->param_type = FILE_;
						target->string = argv[i + 1];
					}
					else
					target->fd = open((char*)argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				}
				else
				{
					ft_fprintf(STDERR_FILENO, RED_TEXT("ft_ssl base64: '-%c' is an "
					"invalid option/flag.\n"), c);
					exit(EXIT_FAILURE);
				}
				j++;
			}
		}
		else
		{
			target->param_type = FILE_;
			target->string = argv[i];
		}
	}
}

void 				get_params_base64(t_command *cmd, char**argv)
{
	int	opt_flag;
	t_data target;

	opt_flag = 0;
	ft_bzero(&target, sizeof(target));
	target.fd = STDOUT_FILENO;
	get_flag(&target, argv, &opt_flag);
	if (target.param_type == STDIN_)
		exec_read_stdin(cmd, opt_flag);
	else
		exec_command(&target, cmd, opt_flag);
	if (target.fd != STDOUT_FILENO && target.fd != -1)
		close(target.fd);
}
