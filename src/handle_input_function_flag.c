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

static void		fill_target_struct(t_data *target, t_list *parameters)
{
	t_list			*tmp;
	t_parameters	*current;

	tmp = parameters;
	target->param_type = STDIN_;
	while (tmp)
	{
		current = (t_parameters*)tmp->content;
		if (current->type == F_OUTPUT)
			target->fd = open(current->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (current->type == F_INPUT || current->type == NONE_)
		{
			target->param_type = FILE_;
			target->string = (uint8_t*)current->str;
		}
		tmp = tmp->next;
	}
	ft_lstdel(&parameters, ft_del);
}

void			get_params_base64(t_command *cmd, t_list *parameters,\
	int opt_flag)
{
	t_data target;

	ft_bzero(&target, sizeof(target));
	target.fd = STDOUT_FILENO;
	fill_target_struct(&target, parameters);
	if (target.param_type == STDIN_)
		exec_read_stdin(cmd, opt_flag, &target);
	else
		exec_command(&target, cmd, opt_flag);
	if (target.fd != STDOUT_FILENO && target.fd != -1)
		close(target.fd);
}
