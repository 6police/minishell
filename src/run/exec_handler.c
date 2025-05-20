#include "ft_run.h"

void eggxecutor (t_cmd *cmd, t_shell *shell, int flag)
{
    shell->is_child = true;
    if (flag == 1)
    {
		printf("entered\n");
    }
    if (setup_redirections(cmd, shell) == 1)
        clean_exit(&shell);
}

void run_pipe(t_cmd *cmd, t_shell *shell)
{
    if (!cmd || !shell || !shell->is_pipe)
        return ;
    
    shell->wait = true;
	signal(SIGQUIT, SIG_IGN); // Ignore Ctrl+\ in parent
	signal(SIGINT, SIG_IGN); // Ignore Ctrl+C in parent
    cmd->pid = fork();
	if (cmd->pid == -1)
    {
        ft_putstr_fd("minishell: fork failed\n", STDERR_FILENO);
        shell->exit_value = 1;
        return ;
    }
    if (cmd->pid == 0)
    {
		signal(SIGQUIT, SIG_DFL);
        signal(SIGINT, SIG_DFL);
        eggxecutor(cmd, shell, 1);
        manage_pipes(cmd, shell);
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
	
	printf("running no pipe\n");
    if (!cmd->is_builtin)
    {
        shell->wait = true;
		signal(SIGQUIT, SIG_IGN); // Ignore Ctrl+\ in parent
		signal(SIGINT, SIG_IGN); // Ignore Ctrl+C in parent
        cmd->pid = fork();
		printf("pid: %d\n", cmd->pid);
        if (cmd->pid == -1)
        {
            ft_putstr_fd("minishell: fork failed\n", STDERR_FILENO);
            shell->exit_value = 1;
            return ;
        }
        if (cmd->pid == 0)
        {
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
            eggxecutor(cmd, shell, 1);
            cmd->builtin_func(cmd, shell);
            clean_exit(&shell);
        }
    }
    else
    {
		printf("aqui\n");
		shell->is_child = true;
		shell->wait = false;
        eggxecutor(cmd, shell, 0);
        shell->is_child = false;
        cmd->builtin_func(cmd, shell);
    }
}

void processor(t_cmd *cmd, t_shell *shell)
{
    if (!cmd || !shell)
        return ;

    if (shell->is_pipe)
        run_pipe(cmd, shell);
    else
        run_no_pipe(cmd, shell);
}
