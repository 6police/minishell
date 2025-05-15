
// wildcard.c
#include "ft_wildcard.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//-----------------------------------------------------------------------------
// Helpers
//----------------------------------------------------------------------------- 

static bool has_wildcard(char *arg)
{
	int i = 0;
	while (arg[i])
	{
		if (arg[i] == '*')
			return true;
		i++;
	}
	return false;
}

static bool is_there_quotes(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return true;
		i++;
	}
	return false;
}

// Case-sensitive strstr offset; returns -1 if not found
static int ft_strstr_off(const char *hay, const char *ndl)
{
	const char *p = strstr(hay, ndl);
	if (!p)
		return -1;
	return (int)(p - hay);
}

// Free a NULL-terminated split array
static void ft_free_split(char **spl)
{
	int i = 0;
	while (spl[i])
	{
		free(spl[i]);
		i++;
	}
	free(spl);
}

// Remove empty tokens from split in-place
static void filter_chunks(char **chunks)
{
	int ri = 0, wi = 0;
	while (chunks[ri])
	{
		if (chunks[ri][0] != '\0')
		{
			chunks[wi++] = chunks[ri];
		}
		else
		{
			free(chunks[ri]);
		}
		ri++;
	}
	chunks[wi] = NULL;
}

// Case-insensitive char-to-lower for sort compare
static int ft_tolower_ci(int c)
{
	if (c >= 'A' && c <= 'Z')
		return c + 32;
	return c;
}

// Case-insensitive strcmp with '.' sorted after letters
static int ft_strcasecmp_dot(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		int c1 = ft_tolower_ci((unsigned char)*s1);
		int c2 = ft_tolower_ci((unsigned char)*s2);
		if (c1 != c2)
		{
			if (c1 == '.') return 1;
			if (c2 == '.') return -1;
			return c1 - c2;
		}
		s1++; s2++;
	}
	return ft_tolower_ci((unsigned char)*s1)
			- ft_tolower_ci((unsigned char)*s2);
}

// Sort wildcard matches in-place
static void organize_wildcard(t_wildcard *wc)
{
	int i = 0;
	while (i + 1 < wc->nbr_of_files)
	{
		int k = i + 1;
		while (k < wc->nbr_of_files)
		{
			if (ft_strcasecmp_dot(wc->wildcard[i], wc->wildcard[k]) > 0)
			{
				char *tmp = wc->wildcard[i];
				wc->wildcard[i] = wc->wildcard[k];
				wc->wildcard[k] = tmp;
			}
			k++;
		}
		i++;
	}
}

//-----------------------------------------------------------------------------
// “Expand all” helper (for "*" or "**", etc.)
//----------------------------------------------------------------------------- 

static void expand_all(char **argp)
{
	t_wildcard wc = {0};
	DIR *dir = opendir(".");
	struct dirent *entry;

	if (!dir) return;

	// 1) Count non-hidden files
	while ((entry = readdir(dir)))
		if (entry->d_name[0] != '.')
			wc.nbr_of_files++;
	closedir(dir);

	if (wc.nbr_of_files == 0) return;

	// 2) Collect
	wc.wildcard = malloc(sizeof(char*) * wc.nbr_of_files);
	if (!wc.wildcard) return;

	dir = opendir(".");
	if (!dir) { free(wc.wildcard); return; }

	int idx = 0;
	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] != '.')
			wc.wildcard[idx++] = strdup(entry->d_name);
	}
	closedir(dir);

	// 3) Sort
	organize_wildcard(&wc);

	// 4) Rebuild into single string
	free(*argp);
	char *out = strdup(wc.wildcard[0]);
	if (!out)
	{
		for (int i = 0; i < wc.nbr_of_files; i++) free(wc.wildcard[i]);
		free(wc.wildcard);
		return;
	}

	for (int i = 1; i < wc.nbr_of_files; i++)
	{
		char *tmp = ft_strjoin(out, " ");
		free(out);
		out = tmp;

		tmp = ft_strjoin(out, wc.wildcard[i]);
		free(out);
		out = tmp;

		free(wc.wildcard[i]);
	}
	// free index 0
	free(wc.wildcard[0]);
	free(wc.wildcard);

	*argp = out;
}

//-----------------------------------------------------------------------------
// Core wildcard expander: case-sensitive match, case-insensitive sort
//----------------------------------------------------------------------------- 

static void wilding(char **argp)
{
	char *pattern = *argp;
	size_t len = strlen(pattern);
	bool must_start;
	bool must_end;
	char **chunks;
	DIR *dir;
	struct dirent *entry;
	t_wildcard wc;
	int pos, off, nch, idx, i;
	bool ok;

	// 1) Handle “all-stars” patterns
	if (strspn(pattern, "*") == len)
	{
		expand_all(argp);
		return;
	}

	// 2) Determine prefix/suffix anchors
	must_start = (pattern[0] != '*');
	must_end   = (pattern[len - 1] != '*');

	// 3) Split pattern on '*' and remove empty tokens
	chunks = ft_split(pattern, '*');
	if (!chunks) return;
	filter_chunks(chunks);

	// 4) First pass: count matches
	wc.nbr_of_files = 0;
	dir = opendir(".");
	if (!dir)
	{
		ft_free_split(chunks);
		return;
	}

	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
			continue;

		pos = 0; nch = 0; ok = true; i = 0;
		while (chunks[nch]) nch++;

		// prefix
		if (must_start)
		{
			size_t m = strlen(chunks[0]);
			if (strncmp(entry->d_name, chunks[0], m) != 0)
				ok = false;
			pos = m; i = 1;
		}

		// middle
		while (ok && i < nch)
		{
			if (must_end && i == nch - 1) break;
			off = ft_strstr_off(entry->d_name + pos, chunks[i]);
			if (off < 0) ok = false;
			else pos += off + strlen(chunks[i]);
			i++;
		}

		// suffix
		if (ok && must_end)
		{
			size_t m = strlen(chunks[nch - 1]);
			size_t N = strlen(entry->d_name);
			if (N < m || strncmp(entry->d_name + N - m, chunks[nch - 1], m) != 0)
				ok = false;
		}

		if (ok)
			wc.nbr_of_files++;
	}
	closedir(dir);

	// 5) No matches: leave argument alone
	if (wc.nbr_of_files == 0)
	{
		ft_free_split(chunks);
		return;
	}

	// 6) Collect matches
	wc.wildcard = malloc(sizeof(char *) * wc.nbr_of_files);
	if (!wc.wildcard)
	{
		ft_free_split(chunks);
		return;
	}

	dir = opendir(".");
	if (!dir)
	{
		free(wc.wildcard);
		ft_free_split(chunks);
		return;
	}

	idx = 0;
	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
			continue;

		pos = 0; nch = 0; ok = true; i = 0;
		while (chunks[nch]) nch++;

		if (must_start)
		{
			size_t m = strlen(chunks[0]);
			if (strncmp(entry->d_name, chunks[0], m) != 0)
				ok = false;
			pos = m; i = 1;
		}

		while (ok && i < nch)
		{
			if (must_end && i == nch - 1) break;
			off = ft_strstr_off(entry->d_name + pos, chunks[i]);
			if (off < 0) ok = false;
			else pos += off + strlen(chunks[i]);
			i++;
		}

		if (ok && must_end)
		{
			size_t m = strlen(chunks[nch - 1]);
			size_t N = strlen(entry->d_name);
			if (N < m || strncmp(entry->d_name + N - m, chunks[nch - 1], m) != 0)
				ok = false;
		}

		if (ok)
			wc.wildcard[idx++] = strdup(entry->d_name);
	}
	closedir(dir);

	// 7) Sort
	organize_wildcard(&wc);

	// 8) Rebuild into single string
	free(*argp);
	char *out = strdup(wc.wildcard[0]);
	for (i = 1; i < wc.nbr_of_files; i++)
	{
		char *tmp = ft_strjoin(out, " ");
		free(out);
		out = tmp;
		tmp = ft_strjoin(out, wc.wildcard[i]);
		free(out);
		out = tmp;
		free(wc.wildcard[i]);
	}
	// free index 0
	free(wc.wildcard[0]);
	free(wc.wildcard);

	*argp = out;

	// 9) Cleanup
	ft_free_split(chunks);
}

void ft_new_wildcard(t_cmd *cmd, t_shell *shell)
{
	(void)shell;
	int i = 0;
	while (cmd->args[i])
	{
		if (has_wildcard(cmd->args[i]) && !is_there_quotes(cmd->args[i]))
			wilding(&cmd->args[i]);
		i++;
	}
}