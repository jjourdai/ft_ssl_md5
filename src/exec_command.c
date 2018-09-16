/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 16:39:50 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/16 16:43:41 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "colors.h"

static void		(*g_dispatcher[]) (struct s_data *) = {
	[MD5] = md5,
	[SHA256] = sha256,
};

static int		read_fd(t_data *info, int fd)
{
	char	*buffer;
	void	*main_buffer;
	void	*inter_buffer;
	size_t	len;

	main_buffer = NULL;
	buffer = ft_memalloc(BUFFER_SIZE);
	while ((len = read(fd, buffer, BUFFER_SIZE)))
	{
		inter_buffer = ft_memalloc(info->len + BUFFER_SIZE);
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
	if (fd == STDIN_FILENO)
		info->string = main_buffer;
	if (info->bytes != NULL)
		return (DATA_RECEIVED);
	return (DATA_NOT_RECEIVED);
}

static t_bool	get_file_bytes(t_data *target, int command)
{
	int fd;

	fd = open((char*)target->string, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(2, RED_TEXT("ft_ssl: %s: %s: %s\n"), (command == MD5) ?\
			"md5" : "sha256", target->string, strerror(errno));
		close(fd);
		return (ERROR);
	}
	read_fd(target, fd);
	close(fd);
	return (SUCCESS);
}

void			exec_read_stdin(int command, int opt_flag)
{
	t_data stdin_input;

	ft_bzero(&stdin_input, sizeof(stdin_input));
	stdin_input.param_type = STDIN_;
	stdin_input.flag = opt_flag;
	if (read_fd(&stdin_input, STDIN_FILENO) == DATA_RECEIVED)
	{
		g_dispatcher[command](&stdin_input);
		display_result(&stdin_input, command);
	}
}

void			exec_command(t_data *target, int command, int opt_flag)
{
	if (opt_flag & F_ECHO)
		exec_read_stdin(command, opt_flag);
	target->flag = opt_flag;
	if (target->param_type == FILE_)
	{
		if (get_file_bytes(target, command) != ERROR)
		{
			g_dispatcher[command](target);
			display_result(target, command);
		}
	}
	else
	{
		g_dispatcher[command](target);
		display_result(target, command);
	}
}
