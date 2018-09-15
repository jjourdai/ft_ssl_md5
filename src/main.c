/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 12:28:59 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/12 15:24:36 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <ssl.h>
#include <colors.h>

t_bool		get_flag(char **argv, int *opt_flag)
{
	int		i;
	int		j;
	char		c;

	i = 2;
	while (argv[i] && argv[i][0] == '-')
	{
		if (argv[i][0] == '-')
		{
			j = 0;
			while ((c = argv[i][++j]))
				if (c == 'p')
					(*opt_flag) |= F_ECHO;
				else if (c == 'q')
					(*opt_flag) |= F_QUIET;
				else if (c == 'r')
					(*opt_flag) |= F_REVERSE;
				else if (c == 's')
					continue ;
				else
				{
					ft_fprintf(STDERR_FILENO, RED_TEXT("ft_ssl: Error: '-%c' is an invalid option/flag.\n"), c);
					return (ERROR);
				}
		}
		i++;
	}
	return (SUCCESS);
}

int get_parameters(char **argv, t_data *info)
{
	int		i;
	int		nb_target;

	i = 2;
	nb_target = 0;
	while (argv[i])
	{
		if (argv[i][0] != '-')
		{
			info[nb_target].string = (uint8_t*)argv[i];
			info[nb_target].param_type = FILE_;
			nb_target++;
		}
		else if (ft_strcmp(argv[i], "-s") == 0)
		{
			if (!argv[i + 1] || argv[i + 1][0] == '-')
			{
				ft_fprintf(STDERR_FILENO, RED_TEXT("./ft_ssl opt '-s' need a string after him\n"));
				exit(EXIT_FAILURE);
			}
			info[nb_target].bytes = (uint8_t*)argv[i + 1];
			info[nb_target].param_type = STRING_;
			nb_target++;
			++i;
		}
		i++;
	}
	return (nb_target);
}

t_bool		get_function(char *str, int *flag)
{
	static char command[END][6] = {
		[MD5] = "md5",
		[SHA256] = "sha256",
	};
	size_t i;

	i = -1;
	while (++i < END)
	{
		if (ft_strcmp(command[i], str) == 0)
		{
			*flag = i;
			return (SUCCESS);
		}
	}
	ft_fprintf(STDERR_FILENO, RED_TEXT("ft_ssl: Error: '%s' is an invalid command.\n"), str);
	return (ERROR);
}

int read_fd(t_data *info, int fd)
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
		if (info->bytes != NULL)
			return (DATA_RECEIVED);
		return (DATA_NOT_RECEIVED);
}

int		main(int argc, char **argv)
{
	void	(*dispatcher[]) (struct s_data *) = {
		[MD5] = md5,
		[SHA256] = sha256,
	};
	int	command;
	int	opt_flag;
	//dont forget to handle malloc_realloc on tab ! ! !
	t_data target[5];

	ft_bzero(target, sizeof(target));
	command = 0;
	if (argc == 1)
		ft_putendl(RED_TEXT("usage: ft_ssl command [-pqrs] [command args]\n\n"
		"Standard commands:\n\nMessage Digest commands:\nmd5\nsha256\n"));
	else
	{
		if (get_function(argv[1], &command) == ERROR)
			return (EXIT_FAILURE);
		if (argc == 2)
		{

		}
		if (get_flag(argv, &opt_flag) == ERROR)
			return (EXIT_FAILURE);
		int nb_target;
		//printf("%x\n", opt_flag);
		if ((nb_target = get_parameters(argv, target)) != 0)
		{
			int i;
			i = -1;
			int fd;
			while (++i < nb_target)
			{
				target[i].flag = opt_flag;
				if (target[i].param_type == FILE_)
				{
					fd = open(target[i].string, O_RDONLY);
					if (fd == -1)
					{
						perror(RED_TEXT("ft_ssl Error:"));
						exit(EXIT_FAILURE);
					}
					read_fd(&target[i], fd);
					close(fd);
				}
				dispatcher[command](&target[i]);
			}
		}
		t_data stdin;
		ft_bzero(&stdin, sizeof(stdin));
		stdin.param_type = STDIN_;
		stdin.flag = opt_flag;
		if (read_fd(&stdin, STDIN_FILENO) == DATA_RECEIVED)
			dispatcher[command](&stdin);
	}
	return(EXIT_SUCCESS);
}
