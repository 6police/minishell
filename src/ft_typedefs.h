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

typedef struct env		t_env;
typedef struct shell	t_shell;
typedef struct cmd t_cmd; // Define a type for the function pointer

typedef enum e_exit_status
{
	EXITSUCCESS = 0, // Successful execution
	EXITFAILURE = 1,
	// General failure (often used by programs to indicate an error)

	// Shell-specific exit codes (for shell-like environments)
	EXIT_COMMAND_NOT_FOUND = 127, // Command not found (shell scripts)

	SIG = 128 //+ SIGSEGV,			// + signal - For all the other SIG's
}						t_exit_status;

// struct to store the here document information
typedef struct here_doc
{
	char *delim;   // delimiter of the here document
	char *content; // content of the here document
	char *file;    // file to store the here document
	int fd; // file descriptor
}						t_here_doc;

typedef enum s_type
{
	HEREDOC,
	APPEND,
	CREATE,
	READ
}						t_type;

// struct to store the command information
// struct to store the redirection information
typedef struct redir
{
	char *redir_in;    // input redirection
	char *redir_out;   // output redirection
	char *redir_append; // for >>
	char *error;    // error redirection
	t_here_doc *heredoc; // here document @@ jony antes tinhas aqui um char *here_doc, mudei para termos acesso a estrutura
}				t_redir;


// struct to store the command information
struct					cmd
{
	char *name;  // command name
	char **args; // arguments
	char *path;  // path to the command,

	bool is_builtin; // if the command is a built-in command
	bool is_valid;   // if the command is valid

	// pointer for the builtin functions
	void (*builtin_func)(t_cmd *cmd, t_shell *shell);
		// Function pointer to the built-in function

	struct cmd *next; // next command
	struct cmd *prev; // previous command

	t_redir **redirs; // redirections
	int					last_fd;
	int					last_read;
	bool				has_heredoc;
};

// struct to store the file descriptors
typedef struct fds
{
	int fd_in;       // file descriptor for the input
	int fd_out;      // file descriptor for the output
	int fd_err;      // file descriptor for the error
	int fd_here_doc; // file descriptor for the here document
}						t_fds;

// struct to store the environment variable and its value
typedef struct env_var
{
	char *key;     // environment variable
	char *value;   // value of the environment variable
	bool exported; // if only 'a' goes to export only, if a= goes to env aswell

	struct env_var *next; // next environment variable
	struct env_var *prev; // previous environment variable
}						t_env_var;

// struct to store the environment variables
struct					env
{
	t_env_var *head; // head of the environment variables
	t_env_var *last; // last of the environment variables
};

typedef struct token
{
	char				**token;
	struct token		*next;
}						t_token;

// struct to store the shell information
struct					shell
{
	t_here_doc			*hd;

	t_env *env;         // environment variables
	char *line;         // line read from the input
	char *history_file; // file to store the history

	char **tokens; // tokens from the line after pipe separation
	bool	is_pipe; // if the command has a pipe
	pid_t main_pid; // process id of the command
	bool is_child; // if the command is a child process

	t_token *token; // tokens from the line after parsing

	int debug; // debug mode
	int	last_exit_code; // last exit code, so we can print it with 'echo $?', isto e o exit_value lol, ja tava feito
	// adicionar isatty??
	// temos que fazer fork sempre que corremos um built_in, com pipeline!!
	// exemplo: ls | exit
	// adicionar exit code_status 'alguns' enum
	// ver ctrl \ em sleep 100;
	// so faco fork, em comandos com pipeline e comandos que leem do terminal para dar handle nos signals.

	int ret;    // return value
	int status; // status of the shell
	int	exit_value;

	int *separators; // separators for the parsing

	t_fds *fds;  // file descriptors
	t_cmd *cmds; // commands
};

#endif
