#include "ssl.h"

static char		*int_to_char(t_data *target, size_t length, int command)
{
	size_t i;
	char 	*hash_str;
	char 	*str;

	i = -1;
	hash_str = NULL;
	while (++i < length)
	{
		if (command == MD5)
			str = ft_itoa_base_ul(SWAP_VALUE(target->final_hash[i]), "0123456789abcdef");
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
		if (!hash_str)
			hash_str = str;
		else
			hash_str = ft_strjoin_free(hash_str, str, 3);
	}
	return (hash_str);
}

void		display_result(t_data *target, int command)
{
	int  j;
	char *hash_str;
	static char data[][10] = {
		[MD5] = "MD5",
		[SHA256] = "SHA256",
		[STRING_] = "\"%s\"",
		[FILE_] = "%s",
	};
	char str[20] = {0};
	j = -1;
	hash_str = int_to_char(target, (command == MD5) ? 4 : 8, command);
	if (target->param_type == STDIN_ && target->flag & F_ECHO)
		ft_printf("%s%s\n", target->string, hash_str);
	else if (target->flag & F_QUIET || target->param_type == STDIN_)
		ft_printf("%s\n", hash_str);
	else
	{
		if (target->flag & F_REVERSE)
			ft_sprintf(str, "%%s  %s\n", data[target->param_type], data[command]);
		else
			ft_sprintf(str, "%s(%s)= %%s\n", data[command], data[target->param_type]);
		if (target->flag & F_REVERSE)
			ft_printf(str, hash_str, target->string);
		else
			ft_printf(str, target->string, hash_str);
	}
}
