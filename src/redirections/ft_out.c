#include "redirections.h"

/**
 * Função para lidar com redirecionamento de output (>)
 * 
 * Substitui o conteúdo do ficheiro com a saída do comando
 * Diferente do >> que adiciona ao final
 */

void	ft_redir_out(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	fd;
	int	saved_stdout;
	t_redir *redir;

	i = -1;
	saved_stdout = dup(STDOUT_FILENO);
	// mm coisa que os outros... vamos percorrer todos os redirs a procura do redir_out
	while (cmd->redirs[++i])
	{
		redir = cmd->redirs[i];
		if (redir->redir_out)
		{
			 // Abre o ficheiro, substituindo conteúdo existente:
			// - O_WRONLY: escrita
			// - O_CREAT: cria se não existir
			// - O_TRUNC: limpa conteúdo existente
			// 0777 ver hcmod (permissoes para nos e para os outros).
			fd = open(redir->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->redir_out, STDERR_FILENO);
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
				shell->exit_value = EXIT_FAILURE;
				break ;
			}
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdout);
		}
	}
}