#include "ft_utils.h"

// function to copy an array of strings
char	**copy_array(char **array)
{
	int		i;
	char	**new_array;

	i = 0;
	if (!array || !(*array))
		return (NULL);
	while (array[i])
		i++;
	new_array = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}
