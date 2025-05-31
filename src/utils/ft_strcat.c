#include "ft_utils.h"

char	*ft_strcat(char *dest, const char *src)
{
	char		*d;
	const char	*s;

	if (!dest || !src)
		return (NULL);
	d = dest;
	s = src;
	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = '\0';
	return (dest);
}
