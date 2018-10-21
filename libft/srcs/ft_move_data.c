#include "libft.h"

void	ft_move_data(char *data, int len, int size)
{
	int i;

	i = size;
	while (i < len)
	{
		data[i - size] = data[i];
		++i;
	}
}
