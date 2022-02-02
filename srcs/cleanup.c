#include "../includes/miniRT.h"

int free_array(char **strs) {
	int	i;

	i = 0;
	while (strs[i])
	{
		free (strs[i]);
		i++;
	}
	free (strs);
	return (-1);
}