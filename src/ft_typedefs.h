#ifndef FT_TYPEDEFS_H
# define FT_TYPEDEFS_H


# define PROMPT monke " minishell _$ "
# define PROMPT_SIZE 11

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

# define HERE_DOC "here_doc"
# define HD_TEMP_FILE ".hd_temp"
# define HISTORY ".minishell_history"

typedef enum e_exit_status
{
	EXITSUCCESS = 0, // Successful execution
	EXITFAILURE = 1,
		// General failure (often used by programs to indicate an error)

	// Shell-specific exit codes (for shell-like environments)
	EXIT_COMMAND_NOT_FOUND = 127, // Command not found (shell scripts)

	SIG = 128 //+ SIGSEGV,			// + signal - For all the other SIG's
}				t_exit_status;

// struct to store the here document information
typedef struct here_doc
{
	char *delim;   // delimiter of the here document
	char *content; // content of the here document
	char *file;    // file to store the here document

	int fd; // file descriptor
}				t_here_doc;

// struct to store the redirection information
typedef struct redir
{
	char *input;    // input redirection
	char *output;   // output redirection
	char *error;    // error redirection
	char *here_doc; // here document
}				t_redir;

// struct to store the command information
typedef struct cmd
{
	char *name;  // command name
	char **args; // arguments
	char *path;  // path to the command,

    bool    is_builtin; // if the command is a built-in command


	struct cmd *next; // next command
	struct cmd *prev; // previous command

	t_redir **redirs; // redirections
	int		last_fd;
	int		last_read;
}				t_cmd;

// struct to store the file descriptors
typedef struct fds
{
	int fd_in;       // file descriptor for the input
	int fd_out;      // file descriptor for the output
	int fd_err;      // file descriptor for the error
	int fd_here_doc; // file descriptor for the here document
}				t_fds;

// struct to store the environment variable and its value
typedef struct env_var
{
	char *key;     // environment variable
	char *value;   // value of the environment variable
	bool exported; // if only 'a' goes to export only, if a= goes to env aswell

	struct env_var *next; // next environment variable
	struct env_var *prev; // previous environment variable
}				t_env_var;

// struct to store the environment variables
typedef struct env
{
	t_env_var *head; // head of the environment variables
	t_env_var *last; // last of the environment variables
}				t_env;

// struct to store the shell information
typedef struct shell
{
	t_here_doc	*hd;

	t_env *env;         // environment variables
	char *line;         // line read from the input
	char *history_file; // file to store the history

	char **tokens; // tokens from the line

	int ret;    // return value
	int status; // status of the shell
	int			exit_value;

    int         *separators; // separators for the parsing

	t_fds *fds;   // file descriptors
	t_cmd **cmds; // commands
}				t_shell;

#endif
