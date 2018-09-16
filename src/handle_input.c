#include "ssl.h"
#include "colors.h"


static void	(*dispatcher[]) (struct s_data *) = {
	[MD5] = md5,
	[SHA256] = sha256,
};

int get_parameters(char **argv, int nb_opt, t_data *info)
{
	int		i;
	int		nb_target;
	int		already_get;

	i = nb_opt + 2;
	nb_target = 0;
	already_get = 0;
	while (argv[i])
	{
		if (already_get == 0 && ft_strcmp(argv[i], "-s") == 0)
		{
			if (!argv[i + 1] || argv[i + 1][0] == '-')
			{
				ft_fprintf(STDERR_FILENO, RED_TEXT("./ft_ssl opt '-s' need a string after him\n"));
				exit(EXIT_FAILURE);
			}
			already_get = 1;
			info[nb_target].bytes = (uint8_t*)argv[i + 1];
			info[nb_target].param_type = STRING_;
			info[nb_target].string = (uint8_t*)argv[i + 1];
			nb_target++;
			++i;
		}
		else
		{
			info[nb_target].string = (uint8_t*)argv[i];
			info[nb_target].param_type = FILE_;
			nb_target++;
		}
		i++;
	}
	return (nb_target);
}

static int read_fd(t_data *info, int fd)
{
		char	*buffer;
		void	*main_buffer;
		void	*inter_buffer;
		size_t	i;
		size_t	len;

		i = 0;
		main_buffer = NULL;
		buffer = ft_memalloc(sizeof(char) * BUFFER_SIZE);
		while ((len = read(fd, buffer, BUFFER_SIZE)))
		{
			inter_buffer = ft_memalloc(sizeof(char) * BUFFER_SIZE * (i + 1));
			if (main_buffer != NULL)
				ft_memcpy(inter_buffer, main_buffer, sizeof(char) * BUFFER_SIZE * i);
			ft_memcpy(inter_buffer + sizeof(char) * BUFFER_SIZE * i, buffer, BUFFER_SIZE);
			free(main_buffer);
			main_buffer = inter_buffer;
			ft_bzero(buffer, len);
			info->len += len;
			i++;
		}
		free(buffer);
		info->bytes = main_buffer;
		if (fd == STDIN_FILENO)
			info->string = main_buffer;
		if (info->bytes != NULL)
			return (DATA_RECEIVED);
		return (DATA_NOT_RECEIVED);
}

// t_bool test_if_stdin_input(void)
// {
// 	fd_set rd;
// 	struct timeval tv;
// 	int ret;
//
// 	ft_bzero(&tv, sizeof(tv));
// 	FD_ZERO(&rd);
// 	FD_SET(STDIN_FILENO, &rd);
// 	ret = select(1, &rd, NULL, NULL, &tv);
// 	if (ret > 0)
// 		return (DATA_RECEIVED);
// 	return (DATA_NOT_RECEIVED);
// }


t_bool get_file_bytes(t_data *target, int command)
{
	int fd;

	fd = open((char*)target->string, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(2, RED_TEXT("ft_ssl: %s: %s: %s\n"), (command == MD5) ? "md5" : "sha256", target->string, strerror(errno));
		close(fd);
		return (ERROR);
	}
	read_fd(target, fd);
	close(fd);
	return (SUCCESS);
}

void exec_read_stdin(int command, int opt_flag)
{
	t_data stdin_input;
	ft_bzero(&stdin_input, sizeof(stdin_input));
	stdin_input.param_type = STDIN_;
	stdin_input.flag = opt_flag;

	if (read_fd(&stdin_input, STDIN_FILENO) == DATA_RECEIVED)
	{
		dispatcher[command](&stdin_input);
		display_result(&stdin_input, command);
	}
}

void handle_parameters_and_exec(int command, int nb_opt, int opt_flag, char**argv)
{
	t_data target[10];
	int nb_target;
	int i;

	ft_bzero(target, sizeof(target));
	nb_target = get_parameters(argv, nb_opt, target);
	if (nb_target == 0)
		exec_read_stdin(command, opt_flag);
	else
	{
		if (opt_flag & F_ECHO)
			exec_read_stdin(command, opt_flag);
		i = -1;
		while (++i < nb_target)
		{
			target[i].flag = opt_flag;
			if (target[i].param_type == FILE_)
			{
				if (get_file_bytes(&target[i], command) != ERROR)
				{
					dispatcher[command](&target[i]);
					display_result(&target[i], command);
				}
			}
			else
			{
				dispatcher[command](&target[i]);
				display_result(&target[i], command);
			}
		}
	}
}
