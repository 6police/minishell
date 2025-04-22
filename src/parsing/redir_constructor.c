#include "ft_parsing.h"

void	add_last_redir(t_fd **head, t_fd *new_redir)
{
    t_fd	*tmp;

    tmp = *head;
    if (!tmp)
        *head = new_redir;
    else
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_redir;
    }
}

/* void assign_redir_type(t_fd *redir, char *str)
{
    if (!str)
        redir->type = NONE;
    else if (str[0] == '>')
    {
        if ((str[1] == '>') && str[2] == '\0')
            redir->type = REDIR_APPEND;
        else if (str[1] != '\0')
            redir->type = REDIR_OUT;
    }
    else if (str[0] == '<')
    {
        if ((str[1] == '<') && str[2] == '\0')
            redir->type = HERE_DOC_;
        else if (str[1] != '\0')
            redir->type = REDIR_IN;
    }
    else
        redir->type = NONE;
} */

int assign_redir_type(char *str)
{
    if (!str)
        return (0);
    if (str[0] == '>' && str[1] != '\0')
    {
        if (str[3] == '>' && str[3] == '<')
            return (0);
        else if ((str[1] == '>') && str[2] != '\0')
            return (REDIR_APPEND);
        else if (str[1] != '\0')
            return (REDIR_OUT);
        else 
            return (0);
    }
    else if (str[0] == '<' && str[1] != '\0')
    {
        if ((str[1] == '<') && str[2] != '\0')
            return (HERE_DOC_);
        else if (str[1] != '\0')
            return (REDIR_IN);
        else
            return (0);
    }
    else
        return (0);
}

void assign_redir_file(t_fd *redir, char *str)
{
    int		i;

    i = 0;
    if (!str || !str[0])
        redir->file = NULL;
    else
    {
        while (str[i] && (str[i] == '>' || str[i] == '<'))
            i++;
        while (str[i] && str[i] == ' ')
            i++;
        redir->file = ft_strdup(str + i);
        if (!redir->file)
        {
            ft_printf_fd(STDIN_FILENO, "Error: malloc failed\n");
            return;
        }
    }
    if (redir->file && redir->file[0] == '\0')
    {
        free(redir->file);
        redir->file = NULL;
    }
}

// function that creates a redirection structure
t_fd *create_redir(char *str)
{
    t_fd	*redir;

    if (!str)
        return (NULL);

    redir = malloc(sizeof(t_fd));
    if (redir == NULL)
    {
        ft_printf_fd(STDIN_FILENO, "Error: malloc failed\n");
        return (NULL);
    }
    redir->type = 0;
    redir->fd = 0;
    redir->file = NULL;
    redir->next = NULL;
    return (redir);
}

t_fd *assemble_redirs(char **redirs)
{
    t_fd	*redir;
    t_fd	*head;
    int		i;

    head = NULL;
    i = 0;
    while (redirs[i])
    {
        redir = create_redir(redirs[i]);
        if (redir == NULL)
            return (NULL);
        redir->type = assign_redir_type(redirs[i]);
        if (redir->type == 0)
        {
            add_last_redir(&head, redir);
            break ;
        }
        assign_redir_file(redir, redirs[i]);
        add_last_redir(&head, redir);
        i++;
    }
    return (head);
}

