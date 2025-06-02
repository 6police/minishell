/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_typedefs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:19:14 by joao              #+#    #+#             */
/*   Updated: 2025/06/01 22:03:49 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPEDEFS_H
# define FT_TYPEDEFS_H

# define PROMPT "minishell _$ "
# define PROMPT_SIZE 11

# define GRAY "\033[0;37m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

# define HERE_DOC ".here_doc"
# define HD_TEMP_FILE ".hd_temp"
# define HISTORY ".minishell_history"

# define REDIR_FAILURE "minishell: syntax error near unexpected token"
# define NOFILE "No such file or directory"
# define TOO_LONG_LINE "minishell: Input too long: Maximum length is "

# define MAX_PIPES 100
# define MAX_HEREDOCS 100
# define MAX_LINE_LENGTH 4096

typedef struct s_env		t_env;
typedef struct s_shell		t_shell;
typedef struct s_cmd		t_cmd; // Define a type for the function pointer

typedef enum e_exit_code
{
	EXIT_CODE_SUCCESS = 0,
	// No error,command executed successfully
	EXIT_CODE_GENERAL_ERROR = 1,		// General error occurred
	EXIT_CODE_MALLOC_FAILURE = 2,		// Memory allocation failure
	EXIT_CODE_PERMISSION_DENIED = 126,
		// Permission denied (common for exec errors)
	EXIT_CODE_CMD_NOT_FOUND = 127,		// Command not found
	EXIT_CODE_INVALID_ARGUMENT = 128,	// Invalid argument passed to a command
	EXIT_CODE_SYNTAX_ERROR = 129,		// Syntax error in the command line
	EXIT_CODE_ENV_FAILURE = 130,
	// Error with environment variable manipulation
	EXIT_CODE_BUILTIN_FAILURE = 131,	// Builtin command failure
	EXIT_CODE_REDIRECTION_ERROR = 132,	// Error during redirection processing
	EXIT_CODE_PIPE_FAILURE = 133,		// Failure in creating or handling pipes
	EXIT_CODE_FORK_FAILURE = 134,		// Failure in forking a new process
	EXIT_CODE_SIGNAL_TERMINATION = 135,	// Process terminated due to a signal
	EXIT_CODE_NOT_A_DIRECTORY = 136,
	// Path provided is not a directory when expected
	EXIT_CODE_FILE_NOT_FOUND = 137,		// Specified file does not exist
}						t_exit_code;

// struct to store the here document information
typedef struct s_wildcard
{
	char				**wildcard;
	int					nbr_of_files;
}						t_wildcard;

// struct to store the redirections
typedef enum s_type
{
	NONE,
	REDIR_OUT,
	REDIR_IN,
	REDIR_APPEND,
	HERE_DOC_
}						t_type;

// struct to store the redirections
typedef struct s_fd
{
	t_type				type;			// type of the redirection
	int					fd;				// file descriptor for the redirection
	char				*file;			// file name for the redirection
	struct s_fd			*next;			// next redirection
}						t_fd;

// struct to store the command information
struct					s_cmd
{
	char			*line;				// line of the command
	char			**redirs;			// redirections
	char			*name;				// command name
	char			**args;				// arguments
	char			*path;				// path to the command,
	int				fd[3];				// file descriptors 1 2 3
	int				fd_pipe[2];			// file descriptor for the pipe
	bool			is_builtin;			// if the command is a built-in command
	bool			is_valid;			// if the command is valid
	pid_t			pid;				// process id of the command
	// pointer for the builtin functions
	void			(*builtin_func)(t_cmd *cmd, t_shell *shell);
	struct s_cmd	*next;				// next command
	struct s_cmd	*prev;				// previous command
	t_fd			*fd_struct;			// redirections file descriptors
	bool			has_heredoc;		// if the command has a heredoc
};

// struct to store the environment variable and its value
typedef struct s_env_var
{
	char				*key;			// environment variable
	char				*value;			// value of the environment variable
	bool				exported;		// if the env var is exported
	struct s_env_var	*next;			// next environment variable
	struct s_env_var	*prev;			// previous environment variable
}	t_env_var;

// struct to store the environment variables
struct	s_env
{
	t_env_var	*head;					// head of the environment variables
	t_env_var	*last;					// last of the environment variables
};

// struct to store the dollar sign information
typedef struct s_dollar
{
	int			i;						// index of the dollar sign in the line
	int			delete;					// if the dollar sign should be deleted
	int			start;					// start index of the env var
	int			env_key_len;			// length of the env var key
	char		*tmp;					// temp str to store the env var key
	char		*aux;					// aux str to store the env var value
	t_env_var	*env_var;				// env var struct
}	t_dollar;

// struct to store the tokens
typedef struct s_token
{
	char			**token;			// tokens from the line
	struct s_token	*next;				// next token
}	t_token;

// struct to store the shell information
struct s_shell
{
	bool	hd;							// if the shell is in heredoc mode
	t_env	*env;						// environment variables
	char	*line;						// line read from the input
	char	*history_file;				// file to store the history
	char	**tokens;					// tokens after pipe
	bool	is_pipe;					// if the command has a pipe
	bool	wait;						// waitpid flag
	pid_t	main_pid;					// process id of the command
	bool	is_child;					// if the command is a child process
	t_token	*token;						// tokens from the line after parsing
	int		super_heredoc_fd;			// file descriptor for the super heredoc
	int		debug;						// debug mode
	int		fd[2];						// file descriptor for the redirections
	int		ret;						// return value
	int		status;						// status of the shell
	int		exit_value;					// exit value of the shell
	int		*separators;				// separators for the parsing
	char	*current_heredoc_file;		// file for the current heredoc
	t_cmd	*cmds;						// commands
};

#endif
