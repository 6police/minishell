#include "redirections.h"

/**
 * Função para lidar com o redirecionamento do append (>>)
 * 
 * O operador '>>' adiciona output no final de um ficheiro existente (escreve a frnete do que ja esta presente/escrito)
 * Diferente do '>' que substi o conteúdo do ficheiro
 */

void	ft_redir_append(t_cmd *cmd, t_shell *shell)
{
	int i;
	int fd;
	t_redir *redir;

	i = -1;
	while (cmd->redirs[++i])
	{
		redir = cmd->redirs[i];
		// Verificamos se este redirecionamento é do tipo append (>>)
		if (redir->redir_append)
		{
			// Abrimos o ficheiro em modo append:
			// - O_WRONLY: abre só para escrita - O_CREAT: cria o ficheiro se não existir - O_APPEND: escreve sempre no final do ficheiro
			// 0644 são as permissões: dono lê+escreve, grupo e outros só leem
			fd = open(redir->redir_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
			// 0644 sao permissoees, ver chmod 777, falar com o jony
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->redir_append, STDERR_FILENO);
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
				shell->exit_value = EXIT_FAILURE;
				break ;
			}
			// Redirecionamos o STDOUT para o ficheiro aberto
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
}