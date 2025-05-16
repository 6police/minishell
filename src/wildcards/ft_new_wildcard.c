/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:04:22 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/16 19:54:25 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wildcard.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Helpers
static bool has_wildcard(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '*')
            return (true);
        i++;
    }
    return (false);
}

static bool is_there_quotes(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
            return (true);
        i++;
    }
    return (false);
}

// Split argument into directory and pattern
static void split_dir_pattern(const char *arg, char **dirp, char **patp)
{
    int i;

    i = (int)strlen(arg) - 1;
    while (i >= 0 && arg[i] != '/')
        i--;
    if (i < 0)
    {
        *dirp = strdup(".");
        *patp = strdup(arg);
    }
    else
    {
        *dirp = strndup(arg, i);
        *patp = strdup(arg + i + 1);
    }
}

// Case-sensitive substring offset
static int strstr_off(const char *hay, const char *ndl)
{
    const char *p;

    p = strstr(hay, ndl);
    if (!p)
        return (-1);
    return ((int)(p - hay));
}

// Free split array
static void split_free(char **spl)
{
    int i;

    i = 0;
    while (spl[i])
    {
        free(spl[i]);
        i++;
    }
    free(spl);
}

// Remove empty tokens
static void filter_chunks(char **chunks)
{
    int ri;
    int wi;

    ri = 0;
    wi = 0;
    while (chunks[ri])
    {
        if (chunks[ri][0])
            chunks[wi++] = chunks[ri];
        else
            free(chunks[ri]);
        ri++;
    }
    chunks[wi] = NULL;
}

// Case-insensitive compare helper for sort
static int tolower_ci(int c)
{
    if (c >= 'A' && c <= 'Z')
        return (c + 32);
    return (c);
}

static int strcmp_dot(const char *s1, const char *s2)
{
    int c1;
    int c2;

    while (*s1 && *s2)
    {
        c1 = tolower_ci((unsigned char)*s1);
        c2 = tolower_ci((unsigned char)*s2);
        if (c1 != c2)
        {
            if (c1 == '.')
                return (1);
            if (c2 == '.')
                return (-1);
            return (c1 - c2);
        }
        s1++;
        s2++;
    }
    return (tolower_ci((unsigned char)*s1) 
          - tolower_ci((unsigned char)*s2));
}

// Sort wildcard matches
static void sort_wildcard(t_wildcard *wc)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    while (i + 1 < wc->nbr_of_files)
    {
        j = i + 1;
        while (j < wc->nbr_of_files)
        {
            if (strcmp_dot(wc->wildcard[i], wc->wildcard[j]) > 0)
            {
                tmp = wc->wildcard[i];
                wc->wildcard[i] = wc->wildcard[j];
                wc->wildcard[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

// Check if a filename matches chunks with anchors
static bool match_chunks(const char *name,
    char **chunks, bool must_start, bool must_end)
{
    int pos;
    int off;
    int nch;
    int i;
    size_t len_name;
    size_t len_chunk;

    pos = 0;
    nch = 0;
    while (chunks[nch])
        nch++;
    i = 0;
    if (must_start)
    {
        len_chunk = strlen(chunks[0]);
        if (strncmp(name, chunks[0], len_chunk) != 0)
            return (false);
        pos = (int)len_chunk;
        i = 1;
    }
    while (i < nch)
    {
        if (must_end && i == nch - 1)
            break;
        off = strstr_off(name + pos, chunks[i]);
        if (off < 0)
            return (false);
        pos += off + (int)strlen(chunks[i]);
        i++;
    }
    if (must_end)
    {
        len_chunk = strlen(chunks[nch - 1]);
        len_name = strlen(name);
        if (len_name < len_chunk)
            return (false);
        if (strncmp(name + len_name - len_chunk,
            chunks[nch - 1], len_chunk) != 0)
            return (false);
    }
    return (true);
}

// Expand '*' or '**' in directory
static void expand_all(char **argp, const char *dirpath)
{
    t_wildcard wc;
    DIR *dir;
    struct dirent *entry;
    char *out;
    char *sep;
    int idx;

    wc.nbr_of_files = 0;
    dir = opendir(dirpath);
    if (!dir)
        return;
    while ((entry = readdir(dir)))
        if (entry->d_name[0] != '.')
            wc.nbr_of_files++;
    closedir(dir);
    if (wc.nbr_of_files == 0)
        return;

    wc.wildcard = malloc(sizeof(char *) * wc.nbr_of_files);
    if (!wc.wildcard)
        return;
    dir = opendir(dirpath);
    if (!dir)
    {
        free(wc.wildcard);
        return;
    }
    idx = 0;
    while ((entry = readdir(dir)))
    {
        if (entry->d_name[0] != '.')
            wc.wildcard[idx++] = strdup(entry->d_name);
    }
    closedir(dir);

    sort_wildcard(&wc);

    free(*argp);
    out = NULL;
    idx = 0;
    while (idx < wc.nbr_of_files)
    {
        char *name = wc.wildcard[idx];
        char *full;
        if (strcmp(dirpath, ".") == 0)
            full = strdup(name);
        else
        {
            sep = ft_strjoin(dirpath, "/");
            full = ft_strjoin(sep, name);
            free(sep);
        }
        if (!out)
            out = strdup(full);
        else
        {
            char *tmp = ft_strjoin(out, " ");
            free(out);
            out = ft_strjoin(tmp, full);
            free(tmp);
        }
        free(full);
        free(name);
        idx++;
    }
    free(wc.wildcard);
    *argp = out;
}

// Main wildcard expander
static void wilding(char **argp)
{
    char            *dirpath;
    char            *pat;
    bool            must_start;
    bool            must_end;
    char            **chunks;
    DIR             *dir;
    struct dirent   *entry;
    t_wildcard      wc;
    int             count;
    char            *out;
    char            *sep;
    char            *full;

    split_dir_pattern(*argp, &dirpath, &pat);
    must_start = (pat[0] != '*');
    must_end = (pat[strlen(pat) - 1] != '*');
    if (strspn(pat, "*") == strlen(pat))
    {
        expand_all(argp, dirpath);
        free(pat);
        free(dirpath);
        return;
    }
    chunks = ft_split(pat, '*');
    free(pat);
    if (!chunks)
    {
        free(dirpath);
        return;
    }
    filter_chunks(chunks);

    wc.nbr_of_files = 0;
    dir = opendir(dirpath);
    if (!dir)
    {
        split_free(chunks);
        free(dirpath);
        return;
    }
    while ((entry = readdir(dir)))
    {
        if (entry->d_name[0] == '.')
            continue;
        if (match_chunks(entry->d_name,
            chunks, must_start, must_end))
            wc.nbr_of_files++;
    }
    closedir(dir);
    if (wc.nbr_of_files == 0)
    {
        split_free(chunks);
        free(dirpath);
        return;
    }
    wc.wildcard = malloc(sizeof(char *) * wc.nbr_of_files);
    if (!wc.wildcard)
    {
        split_free(chunks);
        free(dirpath);
        return;
    }
    count = 0;
    dir = opendir(dirpath);
    while ((entry = readdir(dir)))
    {
        if (entry->d_name[0] == '.')
            continue;
        if (match_chunks(entry->d_name,
            chunks, must_start, must_end))
            wc.wildcard[count++] = strdup(entry->d_name);
    }
    closedir(dir);

    sort_wildcard(&wc);

    free(*argp);
    out = NULL;
    count = 0;
    while (count < wc.nbr_of_files)
    {
        char *name = wc.wildcard[count];
        if (strcmp(dirpath, ".") == 0)
            full = strdup(name);
        else
        {
            sep = ft_strjoin(dirpath, "/");
            full = ft_strjoin(sep, name);
            free(sep);
        }
        if (!out)
            out = strdup(full);
        else
        {
            char *tmp = ft_strjoin(out, " ");
            free(out);
            out = ft_strjoin(tmp, full);
            free(tmp);
        }
        free(full);
        free(name);
        count++;
    }
    free(wc.wildcard);
    *argp = out;
    split_free(chunks);
    free(dirpath);
}

void ft_new_wildcard(t_cmd *cmd, t_shell *shell)
{
    int i;

    (void)shell;
    i = 0;
    while (cmd->args[i])
    {
        if (has_wildcard(cmd->args[i]) && !is_there_quotes(cmd->args[i]))
            wilding(&cmd->args[i]);
        i++;
    }
}
