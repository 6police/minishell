///*#include "redirections.h"

///**
// * Função para lidar com redirecionamento de input (<)
// * 
// * Faz com que o comando leia de um ficheiro em vez de STDIN
// */

//void	ft_redir_in(t_cmd *cmd, t_shell *shell)
//{
//	int i;
//	int fd;
//	t_redir *redir;

//	i = -1;
//	 // Percorremos todos os redirecionamentos do comando, para vermos (if) se algum deles e '<'
//	while (cmd->redirs[++i])
//	{
//		redir = cmd->redirs[i];
//		//se for:
//		if (redir->redir_in)
//		{
//			fd = open(redir->redir_in, O_RDONLY);
//			// Abrimos o ficheiro em modo só leitura!
//			if (fd == -1)
//			{
//				ft_putstr_fd("minishell: ", STDERR_FILENO);
//				ft_putstr_fd(redir->redir_in, STDERR_FILENO);
//				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
//				shell->exit_value = EXIT_FAILURE;
//				break ;
//			}
//			// Redireciona STDIN para ler do ficheiro
//			dup2(fd, STDIN_FILENO);
//			close(fd);
//		}
//	}
//}*/