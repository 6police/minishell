//#include "redirections.h"

///**
// *  serve para gerar um nome único para ficheiros temporários do heredoc
// * 
// *  Usamos um contador estático para garantir nomes únicos!!
// *  mesmo quando há múltiplos heredocs na mesma sessão!
// */

//static char	*generate_heredoc_filename(void)
//{
//	static int	counter;
//	char		*num_str;
//	char		*filename;

//	num_str = ft_itoa(counter++); // static int nao preciso de inicializar counter?? confirmar mais tarde
//	filename = ft_strjoin("/tmp/minishell_heredoc_", num_str);
//	free(num_str);
//	return (filename);
//}

///**
// * Criamos e preenchemos um ficheiro temporário par o heredoc
// * 
// * 1. Geramos um nome único (recorremos a funcao generate_heredoc_filename();)
// * 2. Lê input do utilizador até encontrar o delimitador
// * 3. Armazena tudo no ficheiro temporário
// */

//static int	create_heredoc(t_redir *redir)
//{
//	char	*line;
//	char	*filename;
//	int		fd;

//	filename = generate_heredoc_filename();
//	// - 0600: permissões (nos/donos lê+escreve, resto nada) ver chmod 777
//	fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0600);
//	if (fd == -1)
//	{
//		free(filename);
//		return (-1);
//	}
//	// Loop para ler input até encontrar delimitador
//	while (1)
//	{
//		line = readline("> "); // para mostra prompt especial para o heredoc
//		if (!line || ft_strcmp(line, redir->heredoc->delim) == 0)
//		{
//			free(line);
//			break ;
//		}
//		// Escreve a linha no ficheiro temporário
//		ft_putstr_fd(line, fd); // escreve o conteudo
//		ft_putchar_fd('\n', fd); //adicona a linha
//		free(line);
//	}
//	close(fd);
//	redir->heredoc->file = filename;
//	return (open(filename, O_RDONLY));
//}

///**
// * Função principal para lidar com os heredocs (<<)
// * 
// * Para cada redirecionamento do tipo heredoc no comando:
// * 1. Cria ficheiro temporário
// * 2. Redireciona STDIN para ler desse ficheiro
// */

//void	ft_redir_heredoc(t_cmd *cmd, t_shell *shell)
//{
//	int i;
//	int fd;
//	t_redir *redir;

//	i = -1;
//	while (cmd->redirs[++i])
//	{
//		redir = cmd->redirs[i];
//		// Verificamos se é um heredoc com o delimitador definido
//		if (redir->heredoc && redir->heredoc->delim)
//		{
//			fd = create_heredoc(redir);
//			if (fd == -1)
//			{
//				ft_putstr_fd("minishell: heredoc failed\n", STDERR_FILENO);
//				shell->exit_value = EXIT_FAILURE;
//				break ;
//			}
//			// Redirecionar o STDIN para ler do ficheiro
//			dup2(fd, STDIN_FILENO);
//			close(fd);
//		}
//	}
//}


// void	handle_hd(char *limiter, int fd)
// {
// 	char	*line;

// 	if (fd < 0)
// 		exit_error(NULL, "Error: cannot create temporary file");
// 	while (1)
// 	{
// 		ft_printf("theredoc> ");
// 		line = get_next_line(0);
// 		if (!line)
// 			exit(1);
// 		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
// 			&& line[ft_strlen(limiter)] == '\n')
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(fd, line, ft_strlen(line));
// 		free(line);
// 	}
// 	close(fd);
// }

// int	setup_heredoc(char *limiter)
// {
// 	int	fd;

// 	fd = open(TEMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd == -1)
// 		exit_error(NULL, "Error: cannot create temporary file");
// 	handle_hd(limiter, fd);
// 	fd = open(TEMP_FILE, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		unlink(TEMP_FILE);
// 		exit_error(NULL, "Error: cannot open temporary file");
// 	}
// 	return (fd);
// }




void handle_heredoc(t_fd *fd_struct, t_shell *shell)
{
// GOTTA HANDLE HEREDOC 
///
}

