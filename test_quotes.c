#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Libft function declarations
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);

// Function to test
char	*remove_quotes_beg_end(char *arg);

// Main test function
int	main(void)
{
	char *test1, *test2, *test3, *test4, *result;
	
	// Test case 1: Empty double quotes
	printf("Test 1: Empty double quotes (\"\")\n");
	test1 = ft_strdup("\"\"");
	printf("Input: %s\n", test1);
	result = remove_quotes_beg_end(test1);
	printf("Output: '%s'\n", result);
	printf("Length: %zu\n\n", ft_strlen(result));
	free(result);  // Free the result

	// Test case 2: Empty single quotes
	printf("Test 2: Empty single quotes ('')\n");
	test2 = ft_strdup("''");
	printf("Input: %s\n", test2);
	result = remove_quotes_beg_end(test2);
	printf("Output: '%s'\n", result);
	printf("Length: %zu\n\n", ft_strlen(result));
	free(result);  // Free the result
	
	// Test case 3: Normal double quotes
	printf("Test 3: Normal double quotes (\"hello\")\n");
	test3 = ft_strdup("\"hello\"");
	printf("Input: %s\n", test3);
	result = remove_quotes_beg_end(test3);
	printf("Output: '%s'\n", result);
	printf("Length: %zu\n\n", ft_strlen(result));
	free(result);  // Free the result
	
	// Test case 4: Normal single quotes
	printf("Test 4: Normal single quotes ('hello')\n");
	test4 = ft_strdup("'hello'");
	printf("Input: %s\n", test4);
	result = remove_quotes_beg_end(test4);
	printf("Output: '%s'\n", result);
	printf("Length: %zu\n\n", ft_strlen(result));
	free(result);  // Free the result
	
	printf("All tests completed successfully!\n");
	return (0);
}

// Implementation of remove_quotes_beg_end
char	*remove_quotes_beg_end(char *arg)
{
	char	*new_str;

	if (!arg)
		return (NULL);
	// Check for empty quoted strings
	if ((ft_strlen(arg) == 2 && arg[0] == '\"' && arg[1] == '\"') ||
		(ft_strlen(arg) == 2 && arg[0] == '\'' && arg[1] == '\''))
	{
		new_str = ft_strdup("");
		free(arg);
		return (new_str);
	}
	else if (arg[0] == '\"')
	{
		new_str = ft_strtrim(arg, "\"");
		free(arg);
		return (new_str);
	}
	else if (arg[0] == '\'')
	{
		new_str = ft_strtrim(arg, "\'");
		free(arg);
		return (new_str);
	}
	return (arg);
}

// Libft function implementations
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = NULL;
	while (*s)
	{
		if (*s == (char)c)
			last = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (last);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen((char *)s1);
	while (ft_strchr(set, s1[i]))
		i++;
	while (len > i && ft_strrchr(set, s1[len - 1]))
		len--;
	new_str = (char *)malloc(sizeof(char) * (len - i + 1));
	if (!new_str)
		return (NULL);
	while (i < len)
	{
		new_str[j] = s1[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

