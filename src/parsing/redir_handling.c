#include "ft_parsing.h"


// functions to parse the redirs and args
// and then handle the arg array to remove the redirs
// so that the execution function can use the args array

// function to handle the args and redirs
void handle_args_n_redirs(char **args, char **redirs)
{}

// function to open all the redirs in a cmd
void open_redirs(t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd->redirs[i])
    {
        if (cmd->fd_struct[i].type == INFILE_)
            cmd->fd[0] = open(cmd->redirs[i], O_RDONLY);
        else if (cmd->fd_struct[i].type == OUTFILE_)
            cmd->fd[1] = open(cmd->redirs[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (cmd->fd_struct[i].type == APPEND_)
            cmd->fd[1] = open(cmd->redirs[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
        else if (cmd->fd_struct[i].type == HERE_DOC_)
            cmd->fd[0] = open(cmd->redirs[i], O_RDONLY);
        i++;
    }
}

// function to close all the redirs in a cmd
void close_redirs(t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd->redirs[i])
    {
        if (cmd->fd_struct[i].type == INFILE_)
            close(cmd->fd[0]);
        else if (cmd->fd_struct[i].type == OUTFILE_)
            close(cmd->fd[1]);
        else if (cmd->fd_struct[i].type == APPEND_)
            close(cmd->fd[1]);
        else if (cmd->fd_struct[i].type == HERE_DOC_)
            close(cmd->fd[0]);
        i++;
    }
}

// function that handles all the redirs in the same command
//ex : cmd > file1 < file2 > file3 >> file4 << file5 > file6 should
// open all the files and set the fd in the cmd struct
// and then close all the files
void handle_cmd_redirs(t_cmd *cmd)
{
    t_fd *tmp;
    
    tmp = cmd->fd_struct;
    while (tmp)
    {
        open_redirs(cmd);
        tmp = tmp->next;
    }    
    
}


// !!!!! NEED TO HANDLE shell_$   > outfile (COMMAND) !!!!!!
