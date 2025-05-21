#include "ft_run.h"

void eggxecutor (t_cmd *cmd, t_shell *shell, int flag)
{
    shell->is_child = true;
    if (flag == 1)
    {
        signal(SIGQUIT, SIG_DFL);
        signal(SIGINT, SIG_DFL);
    }
    if (setup_redirections(cmd, shell) == 1)
        clean_exit(&shell);
}

void run_pipe(t_cmd *cmd, t_shell *shell)
{
    if (!cmd || !shell || !shell->is_pipe)
        return ;
    
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
    
    int backup_stdin;
    int backup_stdout;

    backup_stdin = -1;
    backup_stdout = -1;
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
        if (cmd->fd_struct)
        {
            backup_stdin = dup(STDIN_FILENO);
			backup_stdout = dup(STDOUT_FILENO);

        }
		
        shell->wait = false;
        eggxecutor(cmd, shell, 0);
        shell->is_child = false;
        cmd->builtin_func(cmd, shell);
        if (backup_stdin != -1)
        {
            dup2(backup_stdin, STDIN_FILENO);
            close(backup_stdin);
        }
        if (backup_stdout != -1)
        {
            dup2(backup_stdout, STDOUT_FILENO);
            close(backup_stdout);
        }
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
        run_no_pipe(cmd, shell);

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






// void	run_shell_debug(t_shell *shell)
// {
// 	while (1)
// 	{	

// 		shell->line = readline(PROMPT RED "DEBUG" RESET EMOJI_HAMMER);
// 		if (!shell->line)
// 		{
// 			printf(EMOJI_BRAIN "exiting shell\n");
// 			exit_shell(&(t_cmd){0}, shell);
// 		}
// 		else
// 		{
// 			add_history(shell->line);
// 			parse(shell); // builds tokens and cmd structs

// 			// Optional: track if redirs were added during parsing or setup
// 			bool has_redirs = false;
// 			t_cmd *tmp = shell->cmds;
// 			while (tmp)
// 			{
// 				if (tmp->fd_struct)
// 					has_redirs = true;
// 				tmp = tmp->next;
// 			}

// 			int backup_stdin = -1;
// 			int backup_stdout = -1;

// 			if (has_redirs)
// 			{
// 				printf(RED"---/n---/n---/nHAS REDIRS/n---/n---/n"RESET);
// 				backup_stdin = dup(STDIN_FILENO);
// 				backup_stdout = dup(STDOUT_FILENO);
// 			}

// 			run_commands(shell);

// 			if (backup_stdin != -1)
// 			{
// 				dup2(backup_stdin, STDIN_FILENO);
// 				close(backup_stdin);
// 			}
// 			if (backup_stdout != -1)
// 			{
// 				dup2(backup_stdout, STDOUT_FILENO);
// 				close(backup_stdout);
// 			}

// 			if (shell->tokens)
// 			{
// 				free_tokens(shell->tokens);
// 				shell->tokens = NULL;
// 			}
// 			flush_commands(shell);
// 			free(shell->line);
// 			shell->is_pipe = false;
// 		}
// 	}
// }


