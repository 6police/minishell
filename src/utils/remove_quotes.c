#include "ft_utils.h"

char	*remove_quotes(char *arg)
{
	char	*new_str;

	if (!arg)
		return (NULL);
	if (arg[0] == '\"')
	{
		new_str = ft_strtrim(arg, "\"");
		free(arg); // Free the old arg
		return (new_str);
	}
	else if (arg[0] == '\'')
	{
		new_str = ft_strtrim(arg, "\'");
		free(arg); // Free the old arg
		return (new_str);
	} // Duplicate the string if no quotes
	 // Return the new string
	return (arg);
}

// // remove all occurences of quotes from a string
// char *remove_all_quotes(char *arg)
// {
// 	char	*new_str;
// 	char	*temp;

// 	if (!arg)
// 		return (NULL);
// 	new_str = ft_strdup(arg);
// 	temp = new_str;
	
// 	while (*temp)
// 	{
// 		if (*temp == '\"' || *temp == '\'')
// 		{
// 			ft_memmove(temp, temp + 1, ft_strlen(temp));
// 			temp--;
// 		}
// 		temp++;
// 	}
// 	free(arg); // Free the old arg
// 	return (new_str);
// }

char *remove_all_quotes(char *arg)
{
	char *new_str;
	char *temp;

	if (!arg)
		return (NULL);
	new_str = ft_strdup(arg);
	if (!new_str)
		return (NULL);

	temp = new_str;
	while (*temp)
	{
		if (*temp == '\'' || *temp == '\"')
		{
			ft_memmove(temp, temp + 1, ft_strlen(temp)); // includes null byte
			continue; // don't decrement, just recheck current temp
		}
		temp++;
	}
	free(arg);
	return (new_str);
}

char	**ft_removequotes(char **args)
{
	char	**newargs;
	int		len;

	int i, j, k;
	for (i = 0; args[i]; i++)
		;
	newargs = ft_calloc(i + 1, sizeof(char *));
	if (!newargs)
		return (NULL);
	for (i = 0; args[i]; i++)
	{
		len = 0;
		for (j = 0; args[i][j]; j++)
		{
			if (args[i][j] != '\'' && args[i][j] != '"')
				len++;
		}
		newargs[i] = ft_calloc(len + 1, sizeof(char));
		if (!newargs[i])
			return (NULL); 
		for (j = 0, k = 0; args[i][j]; j++)
		{
			if (args[i][j] != '\'' && args[i][j] != '"')
				newargs[i][k++] = args[i][j];
		}
		newargs[i][k] = '\0';
	}
	newargs[i] = NULL;
	free_split(args);
	return (newargs);
}
