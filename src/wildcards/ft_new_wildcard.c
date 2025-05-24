// src/wildcards/ft_new_wildcard.c
#include "ft_wildcard.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//--- Helpers ----------------------------------------------------------------
static bool has_wildcard(const char *s)
{
    int i = 0;
    while (s[i])
        if (s[i++] == '*')
            return true;
    return false;
}

static bool is_quoted(const char *s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == '"' || s[i] == '\'')
            return true;
        i++;
    }
    return false;
}

static char **split_path(const char *path)
{
    return ft_split(path, '/');
}

static void free_strarr(char **a)
{
    int i = 0;
    while (a[i])
        free(a[i++]);
    free(a);
}

static int tolower_ci(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 32 : c;
}

static int strcmp_ci(const char *a, const char *b)
{
    while (*a && *b)
    {
        int ca = tolower_ci((unsigned char)*a);
        int cb = tolower_ci((unsigned char)*b);
        if (ca != cb)
            return ca - cb;
        a++; b++;
    }
    return tolower_ci((unsigned char)*a) - tolower_ci((unsigned char)*b);
}

static void sort_strs(char **arr, int n)
{
    int i = 0;
    while (i + 1 < n)
    {
        int j = i + 1;
        while (j < n)
        {
            if (strcmp_ci(arr[i], arr[j]) > 0)
            {
                char *t = arr[i]; arr[i] = arr[j]; arr[j] = t;
            }
            j++;
        }
        i++;
    }
}

static bool match_pat(const char *name, const char *pat)
{
    bool must_start = pat[0] != '*';
    bool must_end   = pat[strlen(pat)-1] != '*';
    char **chunks   = ft_split(pat, '*');
    int    nch = 0;
    while (chunks[nch]) nch++;
    int pos = 0, idx = 0;
    if (must_start && nch > 0)
    {
        int len = strlen(chunks[0]);
        if (strncmp(name, chunks[0], len))
        {
            free_strarr(chunks);
            return false;
        }
        pos = len;
        idx = 1;
    }
    while (idx < nch - (must_end ? 1 : 0))
    {
        char *p = strstr(name + pos, chunks[idx]);
        if (!p)
        {
            free_strarr(chunks);
            return false;
        }
        pos = (int)(p - name) + strlen(chunks[idx]);
        idx++;
    }
    if (must_end && nch > 0)
    {
        int len = strlen(chunks[nch-1]);
        int nl  = strlen(name);
        if (nl < len || strncmp(name + nl - len, chunks[nch-1], len))
        {
            free_strarr(chunks);
            return false;
        }
    }
    free_strarr(chunks);
    return true;
}

static char *join_path(const char *a, const char *b)
{
    if (!a[0])
        return strdup(b);
    int la = strlen(a), lb = strlen(b);
    char *r = malloc(la + 1 + lb + 1);
    memcpy(r, a, la);
    r[la] = '/';
    memcpy(r+la+1, b, lb);
    r[la+1+lb] = '\0';
    return r;
}

//— Collector struct —--------------------------------------------------------
typedef struct {
    char **arr;
    int    len;
    int    cap;
} t_collect;

static void collect_init(t_collect *c)
{
    c->cap = 16;
    c->len = 0;
    c->arr = malloc(sizeof(char*) * c->cap);
}

static void collect_add(t_collect *c, char *s)
{
    if (c->len + 1 >= c->cap)
    {
        c->cap *= 2;
        c->arr = realloc(c->arr, sizeof(char*) * c->cap);
    }
    c->arr[c->len++] = s;
}

//— Recursive traversal —------------------------------------------------------
static void expand_recursive(char **comps, int lvl,
    const char *base, t_collect *out)
{
    char *next;
    if (comps[lvl] && !has_wildcard(comps[lvl]))
    {
        next = join_path(base, comps[lvl]);
        expand_recursive(comps, lvl + 1, next, out);
        free(next);
        return;
    }
    if (!comps[lvl])
    {
        collect_add(out, strdup(base));
        return;
    }
    DIR *d = opendir(*base ? base : ".");
    if (!d)
        return;
    struct dirent *e;
    bool last = comps[lvl + 1] == NULL;
    while ((e = readdir(d)))
    {
        if (e->d_name[0] == '.')
            continue;
        if (!match_pat(e->d_name, comps[lvl]))
            continue;
        next = join_path(base, e->d_name);
        if (last)
            collect_add(out, next);
        else
        {
            expand_recursive(comps, lvl + 1, next, out);
            free(next);
        }
    }
    closedir(d);
}

//— Public entry point —-------------------------------------------------------
void ft_new_wildcard(t_cmd *cmd, t_shell *shell)
{
    (void)shell;
    int i = 0;
    while (cmd->args[i])
    {
        char *arg = cmd->args[i];
        if (!has_wildcard(arg) || is_quoted(arg))
        {
            i++;
            continue;
        }
        char **comps;
        t_collect coll;
        collect_init(&coll);
        comps = split_path(arg);
        expand_recursive(comps, 0, "", &coll);
        free_strarr(comps);

        if (coll.len > 1)
            sort_strs(coll.arr, coll.len);

        int total = 1;
        int j = 0;
        while (j < coll.len)
        {
            total += strlen(coll.arr[j]) + 1;
            j++;
        }
        char *out = malloc(total);
        out[0] = '\0';
        j = 0;
        while (j < coll.len)
        {
            strcat(out, coll.arr[j]);
            if (j + 1 < coll.len)
                strcat(out, " ");
            free(coll.arr[j]);
            j++;
        }
        free(coll.arr);
        free(cmd->args[i]);
        cmd->args[i] = out;
        i++;
    }
}
