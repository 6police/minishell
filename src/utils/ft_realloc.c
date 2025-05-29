#include "ft_utils.h"

static size_t	size_copy(size_t size, size_t old_size)
{
	if (old_size < size)
		return (old_size);
	else
		return (size);
}

void	*ft_realloc(void *ptr, size_t size, size_t old_size)
{
	void	*new_ptr;
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
}
