/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 16:39:50 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/15 16:11:19 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "colors.h"

static void		loop_read_fd(t_data *info, int fd)
{
	char	*buffer;
	void	*main_buffer;
	void	*inter_buffer;
	int		len;

	main_buffer = NULL;
	buffer = ft_memalloc(BUFFER_SIZE);
	while ((len = read(fd, buffer, BUFFER_SIZE)))
	{
		if (len == -1)
			raise_error(GENERAL, READ_ERROR, (info->string == NULL) ? "(stdin)"\
				: (char*)info->string, EXIT);
		inter_buffer = ft_memalloc(info->len + BUFFER_SIZE + len);
		if (main_buffer != NULL)
			ft_memcpy(inter_buffer, main_buffer, info->len);
		ft_memcpy(inter_buffer + info->len, buffer, BUFFER_SIZE);
		free(main_buffer);
		main_buffer = inter_buffer;
		ft_bzero(buffer, len);
		info->len += len;
	}
	free(buffer);
	info->bytes = main_buffer;
}

static int		read_fd(t_data *info, int fd)
{
	loop_read_fd(info, fd);
	if (fd == STDIN_FILENO)
		info->string = (uint8_t*)ft_strdup((char*)info->bytes);
	if (info->bytes != NULL)
		return (DATA_RECEIVED);
	return (DATA_NOT_RECEIVED);
}

static t_bool	get_file_bytes(t_data *target, t_command *cmd)
{
	int		fd;

	fd = open((char*)target->string, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(2, RED_TEXT("ft_ssl: %s: %s: %s\n"), cmd->string,\
			target->string, strerror(errno));
		close(fd);
		return (ERROR);
	}
	read_fd(target, fd);
	close(fd);
	return (SUCCESS);
}

void			exec_read_stdin(t_command *cmd, int opt_flag, t_data *target)
{
	t_data stdin_input;

	ft_bzero(&stdin_input, sizeof(stdin_input));
	if (target != NULL)
		ft_memcpy(&stdin_input, target, sizeof(t_data));
	stdin_input.param_type = STDIN_;
	stdin_input.flag = opt_flag;
	if (read_fd(&stdin_input, STDIN_FILENO) == DATA_RECEIVED)
	{
		cmd->exec_command(&stdin_input);
		cmd->display(&stdin_input, cmd);
		free((char*)stdin_input.string);
	}
}

void			exec_command(t_data *target, t_command *cmd, int opt_flag)
{
	if (opt_flag & F_ECHO)
		exec_read_stdin(cmd, opt_flag, NULL);
	target->flag = opt_flag;
	if (target->param_type == FILE_)
	{
		if (get_file_bytes(target, cmd) != ERROR)
		{
			cmd->exec_command(target);
			cmd->display(target, cmd);
		}
	}
	else
	{
		cmd->exec_command(target);
		cmd->display(target, cmd);
	}
}
