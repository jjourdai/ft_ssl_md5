/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 15:29:34 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/17 16:13:21 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

static char		g_data[][10] = {
	[MD5] = "MD5",
	[SHA256] = "SHA256",
	[STRING_] = "\"%s\"",
	[FILE_] = "%s",
};

char		*int_to_char(t_data *target, size_t length, int command)
{
	size_t	i;
	char	*hash_str;
	char	*str;

	i = -1;
	hash_str = NULL;
	while (++i < length)
	{
		if (command == MD5)
			str = ft_itoa_base_ul(SWAP_VALUE(target->final_hash[i]),\
				"0123456789abcdef");
		else
			str = ft_itoa_base_ul(target->final_hash[i], "0123456789abcdef");
		if (str[4] == 0)
			ft_sprintf(str, "0000%s", str);
		else if (str[5] == 0)
			ft_sprintf(str, "000%s", str);
		else if (str[6] == 0)
			ft_sprintf(str, "00%s", str);
		else if (str[7] == 0)
			ft_sprintf(str, "0%s", str);
		hash_str = (!hash_str) ? str : ft_strjoin_free(hash_str, str, 3);
	}
	return (hash_str);
}

void		display_hash(t_data *target, t_command *cmd)
{
	int				j;
	char			*hash_str;
	char			str[32];

	j = -1;
	ft_bzero(str, sizeof(str));
	hash_str = int_to_char(target, (cmd->command == MD5) ? 4 : 8, cmd->command);
	if (target->param_type == STDIN_ && target->flag & F_ECHO)
		ft_printf("%s%s\n", target->string, hash_str);
	else if (target->flag & F_QUIET || target->param_type == STDIN_)
		ft_printf("%s\n", hash_str);
	else
	{
		if (target->flag & F_REVERSE)
			ft_sprintf(str, "%%s %s\n", g_data[target->param_type],\
					g_data[cmd->command]);
		else
			ft_sprintf(str, "%s" MACRO_FOR_TEST "= %%s\n",\
				g_data[cmd->command], g_data[target->param_type]);
		if (target->flag & F_REVERSE)
			ft_printf(str, hash_str, target->string);
		else
			ft_printf(str, target->string, hash_str);
	}
	free(hash_str);
}
