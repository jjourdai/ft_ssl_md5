/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 13:26:47 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/17 16:13:04 by jjourdai         ###   ########.fr       */
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
		target->bytes = (uint8_t*)argv[*i + 1];
		target->param_type = STRING_;
		target->string = (uint8_t*)argv[*i + 1];
		*i += 1;
		return (1);
	}
	else
	{
		*already_get = 1;
				return (1);
	}
	return (0);
}

void		run_parameters_and_exec(t_command *cmd, t_list *parameters, int opt_flag)
{
	t_list			*tmp;
	t_parameters	*current;
	t_data	target;

	tmp = parameters;	
	target.param_type = STDIN_;
	while (tmp)
	{
		ft_bzero(&target, sizeof(t_data));
		current = (t_parameters*)tmp->content;
		if (current->type == F_STRING)
		{
			target.bytes = (uint8_t*)current->str;
			target.param_type = STRING_;
			target.string = (uint8_t*)current->str;
		}
		else
		{
			target.string = (uint8_t*)current->str;
			target.param_type = FILE_;
		}
		exec_command(&target, cmd, opt_flag);
		tmp = tmp->next;
	}
	if (parameters == NULL)
		exec_read_stdin(cmd, opt_flag);
	ft_lstdel(&parameters, ft_del);
}
