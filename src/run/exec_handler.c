#include "ft_run.h"

void eggxecutor (t_cmd *cmd, t_shell *shell, int flag)
{
    if (flag == 1)
    {
        shell->is_child = true;
        signal(SIGQUIT, SIG_DFL);
        signal(SIGINT, SIG_DFL);
        if (cmd->fd[0] != -1)
            dup2(cmd->fd[0], STDIN_FILENO);
        if (cmd->fd[1] != -1)
            dup2(cmd->fd[1], STDOUT_FILENO);
    }
    (void)cmd;
    // if (setup_redirections(cmd, shell) == 1)
    //     clean_exit(&shell);
}

void run_pipe(t_cmd *cmd, t_shell *shell)
{
    if (!cmd || !shell || !shell->is_pipe)
        return ;
    if (setup_redirections(cmd, shell) == 1)
        clean_exit(&shell);
    shell->wait = true;
    cmd->pid = fork();
    if (cmd->pid == -1)
    {
        ft_putstr_fd("minishell: fork failed\n", STDERR_FILENO);
        shell->exit_value = 1;
        return ;
    }
    if (cmd->pid == 0)
    {
        manage_pipes(cmd, shell);
        eggxecutor(cmd, shell, 1);
        close_pipes(shell->cmds);
        cmd->builtin_func(cmd, shell);
        clean_exit(&shell);
    }
    else
        close_pipes_after_fork(cmd);
}

void run_no_pipe(t_cmd *cmd, t_shell *shell)
{
    if (!cmd || !shell || shell->is_pipe)
        return ;
    if (setup_redirections(cmd, shell) == 1)
        clean_exit(&shell);
    if (!cmd->is_builtin)
    {
        shell->wait = true;
        cmd->pid = fork();
        if (cmd->pid == -1)
        {
            ft_putstr_fd("minishell: fork failed\n", STDERR_FILENO);
            shell->exit_value = 1;
            return ;
        }
        if (cmd->pid == 0)
        {
            eggxecutor(cmd, shell, 1);
            cmd->builtin_func(cmd, shell);
            clean_exit(&shell);
        }
    }
    else
    {
        shell->wait = false;
        eggxecutor(cmd, shell, 0);
        shell->is_child = false;
        cmd->builtin_func(cmd, shell);
        
    }
}


void processor(t_cmd *cmd, t_shell *shell)
{
    t_fd *tmp;

    tmp = NULL;
    if (!cmd || !shell)
        return ;

    if (shell->is_pipe)
        run_pipe(cmd, shell);
    else
        run_no_pipe(cmd, shell);//look after

    if (cmd->fd_struct)
	{
        // Finally, close everything (but NOT STDIN/OUT) (this was in handle_redirections)
	    tmp = cmd->fd_struct;
	    while (tmp)
	    {
	    	if (tmp->fd != -1)
	    	{
            
	    		close(tmp->fd);
	    		tmp->fd = -1;
	    		if (tmp->type == HERE_DOC_)
	    		{
	    			unlink(HERE_DOC);
	    			free(tmp->file);
	    			tmp->file = NULL;
	    		}
	    	}
	    	tmp = tmp->next;
	    }
    }
}



