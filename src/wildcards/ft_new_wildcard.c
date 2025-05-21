// ft_wildcard.c
#include "ft_wildcard.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// --- Helpers from your original code ----------------------------------------

static bool has_wildcard(const char *arg) {
    for (int i = 0; arg[i]; i++)
        if (arg[i] == '*')
            return true;
    return false;
}

static bool is_there_quotes(const char *str) {
    for (int i = 0; str[i]; i++)
        if (str[i] == '"' || str[i] == '\'')
            return true;
    return false;
}

static int tolower_ci(int c) {
    if (c >= 'A' && c <= 'Z') return c + 32;
    return c;
}

static int strcmp_dot(const char *s1, const char *s2) {
    int c1, c2;
    while (*s1 && *s2) {
        c1 = tolower_ci((unsigned char)*s1);
        c2 = tolower_ci((unsigned char)*s2);
        if (c1 != c2) {
            if (c1 == '.') return  1;
            if (c2 == '.') return -1;
            return (c1 - c2);
        }
        s1++; s2++;
    }
    return (tolower_ci((unsigned char)*s1) 
          - tolower_ci((unsigned char)*s2));
}

static void sort_strs(char **arr, int n) {
    for (int i = 0; i + 1 < n; i++)
        for (int j = i + 1; j < n; j++)
            if (strcmp_dot(arr[i], arr[j]) > 0) {
                char *t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
}

// split path by '/', returns NULL-terminated array
static char **split_path(const char *path) {
    return ft_split(path, '/');
}

static void free_strarr(char **a) {
    for (int i = 0; a[i]; i++)
        free(a[i]);
    free(a);
}

// test if `name` matches wildcard chunk `pat`
static bool match_pat(const char *name, const char *pat) {
    bool must_start = pat[0] != '*';
    bool must_end   = pat[strlen(pat) - 1] != '*';
    char **chunks   = ft_split(pat, '*');
    if (!chunks) return false;
    int wi = 0;
    for (int ri = 0; chunks[ri]; ri++) {
        if (chunks[ri][0])
            chunks[wi++] = chunks[ri];
        else
            free(chunks[ri]);
    }
    chunks[wi] = NULL;
    int nch = wi;
    int pos = 0;
    if (must_start && nch > 0) {
        int len = strlen(chunks[0]);
        if (strncmp(name, chunks[0], len) != 0) {
            free_strarr(chunks);
            return false;
        }
        pos = len;
    }
    for (int i = must_start ? 1 : 0; i < nch - (must_end ? 1 : 0); i++) {
        char *p = strstr(name + pos, chunks[i]);
        if (!p) {
            free_strarr(chunks);
            return false;
        }
        pos = (int)(p - name) + strlen(chunks[i]);
    }
    if (must_end && nch > 0) {
        int len = strlen(chunks[nch - 1]);
        int namelen = strlen(name);
        if (namelen < len ||
            strncmp(name + namelen - len, chunks[nch - 1], len) != 0) {
            free_strarr(chunks);
            return false;
        }
    }
    free_strarr(chunks);
    return true;
}

// join two path segments with '/'
static char *join_path(const char *a, const char *b) {
    if (!a || a[0] == '\0')
        return strdup(b);
    char *tmp = ft_strjoin(a, "/");
    char *res = ft_strjoin(tmp, b);
    free(tmp);
    return res;
}

// --- Recursive expansion -----------------------------------------------------

typedef struct {
    char **arr;
    int    cap;
    int    len;
} t_collect;

static void collect_init(t_collect *c) {
    c->cap = 16;
    c->len = 0;
    c->arr = malloc(sizeof(char*) * c->cap);
}

static void collect_add(t_collect *c, char *s) {
    if (c->len + 1 >= c->cap) {
        c->cap *= 2;
        c->arr = realloc(c->arr, sizeof(char*) * c->cap);
    }
    c->arr[c->len++] = s;
}

static void expand_recursive(char **components, int level,
                             const char *base, t_collect *out)
{
    if (!components[level]) {
        collect_add(out, strdup(base));
        return;
    }

    DIR *d = opendir(base[0] ? base : ".");
    if (!d) return;

    struct dirent *e;
    bool is_last = components[level + 1] == NULL;
    while ((e = readdir(d))) {
        if (e->d_name[0] == '.') continue;
        if (!match_pat(e->d_name, components[level])) continue;
        char *next = join_path(base, e->d_name);
        if (is_last) {
            collect_add(out, next);
        } else {
            expand_recursive(components, level + 1, next, out);
            free(next);
        }
    }
    closedir(d);
}

// --- Public interface -------------------------------------------------------

void ft_new_wildcard(t_cmd *cmd, t_shell *shell) {
    (void)shell;
    for (int i = 0; cmd->args[i]; i++) {
        char *arg = cmd->args[i];
        if (!has_wildcard(arg) || is_there_quotes(arg))
            continue;

        char **comps = split_path(arg);
        if (!comps) continue;

        t_collect coll;
        collect_init(&coll);
        expand_recursive(comps, 0, "", &coll);

        free_strarr(comps);
        if (coll.len > 0) {
            sort_strs(coll.arr, coll.len);

            size_t total = 1;
            for (int j = 0; j < coll.len; j++)
                total += strlen(coll.arr[j]) + 1;
            char *out = malloc(total);
            out[0] = '\0';
            for (int j = 0; j < coll.len; j++) {
                strcat(out, coll.arr[j]);
                if (j + 1 < coll.len) strcat(out, " ");
                free(coll.arr[j]);
            }
            free(cmd->args[i]);
            cmd->args[i] = out;
        }
        free(coll.arr);
    }
}
