#include "redirections.h"

void	cleanup_temp_files(t_cmd **cmds)
{
	int i;
	int j;
	t_cmd *cmd;
	t_redir *redir;

	i = -1;
	while (cmds[++i])
	{
		cmd = cmds[i];
		j = -1;
		while (cmd->redirs[++j])
		{
			redir = cmd->redirs[j];
			if (redir->heredoc && redir->heredoc->file)
			{
				unlink(redir->heredoc->file);
				free(redir->heredoc->file);
				redir->heredoc->file = NULL;
			}
		}
	}
}