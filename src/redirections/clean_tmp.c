#include "redirections.h"
/**
 * Função que limpa os ficheiros temporários criados pelo heredoc
 * 
 * O heredoc (<<) serve para:
 * 1. Armzenar o input temporário ate que se ecreva o delimitador
 * 2. Servir como input redirecionado para comandos
 * 
 * Recebe um array de comandos (t_cmd **cmds) porque:
 * - Se houver um pipe (cmd1 | cmd2) tem múltiplos comandos (por isso e que e necessario percorrer)
 * - Cada comando pode ter múltiplos redirecionamentos
 * - Cada heredoc cria seu próprio ficheiro temporário
 */

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
			redir = cmd->redirs[j]; //pegamos o redirecionamento atual
			// verifica se tem um heredoc como ficheiro associado
			// importante porque nem todos os redirect. sao heredocs
			if (redir->heredoc && redir->heredoc->file)
			{
				// Remove o ficheiro do sistema (unlink)
				// Isto evita acumular lixo em /tmp quando o programa termina
				unlink(redir->heredoc->file); // man unlink == unlink - call the unlink function to remove the specified file
				free(redir->heredoc->file);
				redir->heredoc->file = NULL;
			}
		}
	}
}