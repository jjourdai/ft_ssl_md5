/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_crypto_function.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:56:03 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/19 15:56:05 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

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
		else if (current->type & F_KEY)
			ft_memcpy(target->key, current->str, SIZE_KEY);
		else if (current->type & F_IVECTOR)
			ft_memcpy(target->iv, current->str, SIZE_KEY);
		else if (current->type & F_SALT)
			ft_memcpy(target->salt, current->str, SIZE_KEY);
		else if (current->type & F_PASSWORD)
			ft_memcpy(target->password, current->str, PASSWORD_LEN);
		tmp = tmp->next;
	}
}

void			run_des_parameters_and_exec(t_command *cmd, t_list *parameters,\
	int opt_flag)
{
	t_data target;

	ft_bzero(&target, sizeof(target));
	target.fd = STDOUT_FILENO;
	fill_target_struct(&target, parameters);
	ft_lstdel(&parameters, ft_del);
	if (target.param_type == STDIN_)
		exec_read_stdin(cmd, opt_flag, &target);
	else
		exec_command(&target, cmd, opt_flag);
	if (target.fd != STDOUT_FILENO && target.fd != -1)
		close(target.fd);
}
