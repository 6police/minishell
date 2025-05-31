#include "ft_utils.h"

static size_t	size_copy(size_t size, size_t old_size)
{
	if (old_size < size)
		return (old_size);
	else
		return (size);
}

char	**ft_realloc_arr(char **ptr, size_t size, size_t old_size)
{
	char	**new_arr;
	size_t	i;
	size_t	new_size;

	if (size == 0)
		return (NULL);
	new_size = size_copy(size, old_size);
	new_arr = malloc(sizeof(char *) * (new_size + 1)); // +1 for NULL terminator
	if (!new_arr)
		return (NULL);

	// Copy old pointers
	i = 0;
	while (i < old_size && ptr && ptr[i])
	{
		new_arr[i] = ptr[i];
		i++;
	}
	// NULL the rest
	while (i <= size)
		new_arr[i++] = NULL;

	// Free old pointer array but NOT the strings it pointed to
	if (ptr)
		free(ptr);

	return (new_arr);
}

/*char	**ft_realloc_arr(char **ptr, size_t size, size_t old_size)
{
	char	**new_ptr;
	size_t	copy_size;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(size));
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	copy_size = size_copy(size, old_size);
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}*/
