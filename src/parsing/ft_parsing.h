/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:20:13 by joao              #+#    #+#             */
/*   Updated: 2025/06/02 18:06:34 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSING_H
# define FT_PARSING_H

# include "../minishell.h"
// parsing

// parsing the line into tokens
char	**parse_line(char *line, int letter, int sub);

// parsing to make tokens so we can later parse the tokens into commands
void	parse_tokens(t_shell *shell);

// parse the line and tokens
void	parse(t_shell *shell);

// count the number of quotes
int		count_quotes(char *line);

// mark a character in the line and switch for another
void	mark_and_replace(char *line, int letter, int sub);

// mark the pipes
int		mark_pipes(char *line);

// number of pipes in the line
int		count_pipers(char *line);

// split the line into tokens
char	**ft_parse_split(char *line, int letter, int sub);

// function to check if the token is not empty
bool	token_not_empty(const char *token);

// function to initialize tokens
t_token	*init_token(char **tokens);

// function to add a token to the list
t_cmd	*build_cmds(t_shell *shell);

// funciton to count the number of > redirects in the token
int		forward_redir_count(char *token);

// function to count the number of >> redirects in the token
int		dbl_forward_redir_count(char *token);

// function to count the number of < redirects in the token
int		back_redir_count(char *token);

// function that counts the number of here_docs in the token
int		here_doc_count(char *token);

// function to check for redirections
int		check_for_redirs(char *token);

// function to treat tokens and corresponding redirections
char	**split_into_redirs(char *token);

// function to add a redirection to the list
void	add_last_redir(t_fd **head, t_fd *new_redir);

// function to check and assign the redirection type
int		assign_redir_type(char *str);

// function to assign the redirection file
void	assign_redir_file(t_fd *redir);

// function to create a new redirection
t_fd	*create_redir(char *str);

// function to assemble all the redirections
t_fd	*assemble_redirs(char **redirs);

// function to create a new command
t_cmd	*init_cmd(char *name, char **args);

// function to handle built-in commands
void	built_in_handle(t_cmd *cmd, t_shell *shell, char **args);

// function to set the name of the command
char	*set_name(char **args);

// function to process the command arguments, normalizing the cmd->args
void	process_cmd_args(t_cmd *cmd);

// function to add a command to the linked list
void	add_last_cmd(t_cmd **head, t_cmd *new_cmd);

// function to check if the command is a built-in command
void	check_builtin(t_cmd *cmd);

// function to build a built-in command
void	build_builtin(t_cmd *cmd, char **args);

// function to build the command
void	build_cmd(t_cmd *cmd, char **args, t_shell *shell);

// function to assemble the command if the line is a path
void	assemble_cmd_path(t_cmd *cmd, char **args);

// function to check for the command path and assemble the command
void	assemble_cmd(t_cmd *cmd, char **args, t_shell *shell);

// check if the command is a redirection with no arguments
bool	is_redir_noarg(char *str);

// check if the command is a redirection
bool	is_redir(char *str);

// function to check if the string is all whitespace
bool	is_all_whitespace(const char *s);

// function to parse the line according to priority
char	**parse_line(char *line, int letter, int sub);

// function to print the tokens
void	print_tokens(t_shell *shell);

// function to check if the redirection is valid
bool	check_redir_validity(t_shell *shell);

// function to invalidate commands
void	invalidate_cmds(t_shell *shell);

// function to free the tokens
bool	check_syntax(char **tokens);

// function to check token validity
bool	invalidate_tokens(char **tokens);

// function to check if the token is a redirection
void	check_redir(char *token, int *j);

// check file
bool	check_file(char *cmd);

// function to copy only valid arguments from the original args array
char	**copy_valid_args(char **args, int count);

// count the number of valid arguments in the args array
int		count_valid_args(char **args);

// function to process the command arguments
void	cmd_processor_a(t_cmd *cmd, t_shell *shell, int i);

// invalid exit function
t_cmd	*invalid_exit(t_cmd *cmd, t_shell *shell);

// parse the command
t_cmd	*parse_cmd(t_shell *shell, int i);

// check if the command is a valid path
bool	ft_valid_pather(char *cmd);

#endif
