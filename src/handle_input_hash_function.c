/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 13:26:47 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/15 16:10:58 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void		fill_struct_for_f_string(t_data *target, char *str)
{
	target->bytes = (uint8_t*)str;
	target->param_type = STRING_;
	target->string = (uint8_t*)str;
}

void		run_parameters_and_exec(t_command *cmd, t_list *parameters,\
	int opt_flag)
{
	t_list			*tmp;
	t_parameters	*current;
	t_data			target;

	tmp = parameters;
	target.param_type = STDIN_;
	while (tmp)
	{
		ft_bzero(&target, sizeof(t_data));
		current = (t_parameters*)tmp->content;
		if (current->type == F_STRING)
			fill_struct_for_f_string(&target, current->str);
		else
		{
			target.string = (uint8_t*)current->str;
			target.param_type = FILE_;
		}
		exec_command(&target, cmd, opt_flag);
		tmp = tmp->next;
	}
	if (parameters == NULL)
		exec_read_stdin(cmd, opt_flag, NULL);
	ft_lstdel(&parameters, ft_del);
}
