#include "redirections.h"

///**
// *  serve para gerar um nome único para ficheiros temporários do heredoc
// *
// *  Usamos um contador estático para garantir nomes únicos!!
// *  mesmo quando há múltiplos heredocs na mesma sessão!
// */

// static char	*generate_heredoc_filename(void)
//{
//	static int	counter;
//	char		*num_str;
//	char		*filename;

//	num_str = ft_itoa(counter++);
// static int nao preciso de inicializar counter?? confirmar mais tarde
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

// static int	create_heredoc(t_redir *redir)
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

// void	ft_redir_heredoc(t_cmd *cmd, t_shell *shell)
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

static bool	has_expansion(char *line)
{
	int		i;
	int		count_quotes;
	bool	expansion;

	i = 0;
	count_quotes = 0;
	expansion = false;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && !count_quotes)
			count_quotes = line[i];
		else if (count_quotes && line[i] == count_quotes)
			count_quotes = 0;
		else if (line[i] == '$' && !count_quotes)
		{
			expansion = true;
			break ;
		}
		i++;
	}
	return (expansion);
}

// static char	*ft_str_find_and_replace(char *str, char *old, char *new)
// {
// 	char	*result;
// 	char	*insert;
// 	char	*tmp;
// 	int		i;
// 	int		count;

// 	if (!str || !old || !new)
// 		return (NULL);
// 	count = 0;
// 	insert = new;
// 	tmp = str;
// 	while ((tmp = ft_strstr(tmp, old)))
// 	{
// 		count++;
// 		tmp += ft_strlen(old);
// 	}
// 	result = malloc(ft_strlen(str) + (ft_strlen(new) - ft_strlen(old)) * count
// 			+ 1);
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	while (*str)
// 	{
// 		if (ft_strstr(str, old) == str)
// 		{
// 			strcpy(&result[i], insert);
// 			i += ft_strlen(insert);
// 			str += ft_strlen(old);
// 		}
// 		else
// 			result[i++] = *str++;
// 	}
// 	result[i] = '\0';
// 	return (result);
// }

// static char	*ft_expand(char *line, t_shell *shell)
// {
// 	char		*expansion;
// 	char		*newline;
// 	char		*oldline;
// 	t_env_var	*tmp;
// 	int			i;
// 	int			j;
// 	int			quotes;

// 	if (!line)
// 		return (NULL);
// 	expansion = NULL;
// 	newline = ft_strdup(line);
// 	oldline = NULL;
// 	if (!newline)
// 		return (NULL);
// 	i = 0;
// 	quotes = 0;
// 	tmp = NULL;
// 	while (line[i])
// 	{
// 		if ((line[i] == '\'' || line[i] == '"') && !quotes)
// 			quotes = line[i];
// 		else if (quotes && line[i] == quotes)
// 			quotes = 0;
// 		else if (line[i] == '$' && !quotes)
// 		{
// 			i++;
// 			j = i;
// 			while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
// 				j++;
// 			if (j > i)
// 			{
// 				expansion = ft_substr(line, i, j - i);
// 				if (!expansion)
// 					return (NULL);
// 				tmp = find_env_var(shell->env, expansion);
// 				if (tmp)
// 				{
// 					free(expansion);
// 					expansion = NULL;
// 					expansion = ft_strdup(tmp->value);
// 					if (!expansion)
// 						return (NULL);
// 				}
// 				oldline = newline;
// 				newline = ft_str_find_and_replace(newline, line + i - 1,
// 						expansion);
// 				if (!newline)
// 					return (NULL);
// 				free(oldline);
// 				free(expansion);
// 				expansion = NULL;
// 				i = j;
// 			}
// 			else
// 			{
// 				oldline = newline;
// 				newline = ft_str_find_and_replace(oldline, "$", "$");
// 				free(oldline);
// 				if (!newline)
// 					return (NULL);
// 				i++;
// 			}
// 		}
// 		else
// 			i++;
// 	}
// 	free(line);
// 	return (newline);
// }

char	*str_replace_segment(const char *src, const char *replace, int start, int len_to_delete)
{
	int		new_len;
	char	*new_str;
	int		i;
	int		j;

	if (!src || !replace || start < 0 || len_to_delete < 0)
		return (NULL);
	new_len = strlen(src) - len_to_delete + strlen(replace);
	new_str = malloc(sizeof(char) * (new_len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < start)
	{
		new_str[i] = src[i];
		i++;
	}
	j = 0;
	while (replace[j])
		new_str[i++] = replace[j++];
	j = start + len_to_delete;
	while (src[j])
		new_str[i++] = src[j++];
	new_str[i] = '\0';
	return (new_str);
}

char *ft_expand(char *line, t_shell *shell)
{
    int		i;
    int		j;
    char	*expansion;
    char	*new_line;
    t_env_var	*tmp;

    i = 0;
    tmp = NULL;
    while (line[i])
    {
        if (line[i] == '$')
        {
            j = i + 1;
            while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
                j++;
            expansion = ft_substr(line, i + 1, j - i - 1);
            if (!expansion)
                return (NULL);
            tmp = find_env_var(shell->env, expansion);
            if (tmp)
            {
                free(expansion);
                expansion = ft_strdup(tmp->value);
                if (!expansion)
                    return (NULL);
            }
            new_line = str_replace_segment(line, expansion, i, j - i);
            free(line);
            line = new_line;
            i += ft_strlen(expansion) - 1;
            free(expansion);
        }
        i++;
    }
    return (line);
}

void	handle_heredoc(t_fd *fd_struct, t_shell *shell)
{
	int		fd;
	char	*line;
	char	*limiter;

	limiter = fd_struct->file;
	fd = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
				&& line[ft_strlen(limiter)] == '\n'))
		{
			free(line);
			break ;
		}
		if (has_expansion(line))
			line = ft_expand(line, shell);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}
