#include "ft_cmd_as_regular_user.h"

char	*handle_dollar(char *arg, t_shell *shell);
static int	check_quotes_type(char *str);

void	dollar_sign(t_shell *shell)
{
	int	i;
	int		quote_type;
	bool	has_dollar;
	char *s;

	i = 0;
	quote_type = 0;
	has_dollar = false;
	s = NULL;
	while (shell->tokens[i])
	{
		if (ft_strstr(shell->tokens[i], "$") != NULL)
		{
			quote_type = check_quotes_type(shell->tokens[i]);
			has_dollar = true;
		}
		if ((quote_type != 2) && has_dollar == true)
			shell->tokens[i] = handle_dollar(shell->tokens[i], shell);
		i++;
	}
}
char	*handle_dollar(char *arg, t_shell *shell)
{
	int			i;
	int			delete;
	int			start;
	int			env_key_len;
	char		*tmp;
	char	*aux;
	t_env_var	*env_var;

	i = 0;
	start = 0;
	env_key_len = 0;
	tmp = NULL;
	aux = NULL;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1])
		{
			if (ft_isalpha(arg[i + 1]) == 1 || (arg[i + 1] == '_'))
			{
				if ((env_var = find_env_var(shell->env, (arg + (i + 1)))) != NULL)
				{
					start = i;
					env_key_len = ft_strlen(env_var->key) + 1; // +1 to catch the $
					aux = ft_strdup(arg);
					tmp = str_replace_segment(aux, env_var->value, i, env_key_len);
					if (tmp[i + ft_strlen(env_var->value)] != '\0' && (ft_isalnum(tmp[i + ft_strlen(env_var->value)]) == 1 || tmp[i + ft_strlen(env_var->value)] == '_')) // we want to check 
					{
						i += ft_strlen(env_var->value);
						delete = 0;
						while ((ft_isalnum(tmp[i]) == 1 || tmp[i] == '_'))
						{	
							i++;
							delete++;
						}
						arg = str_replace_segment(arg, "", start, env_key_len + delete);
						i = start - 1;
					}
					else
					{	
						arg = str_replace_segment(arg, env_var->value, start, env_key_len);
						i += ft_strlen(env_var->value) - 1;
					}
					free(tmp);
				}
				else // env not found, env == NULL
				{
					start = i;
					i += 1; // we want to skip the $
					while (arg[i])
					{
						if (ft_isalnum(arg[i]) == 1 || arg[i] == '_')
							i++;
						else
							break ;
					}
					arg = str_replace_segment(arg, "", start, i - start);
					i = start - 1;
				}
			}
			else if (arg[i + 1] == '?')
			{
				aux = ft_itoa(shell->exit_value);
				arg = str_replace_segment(arg, aux, i, 2);
				i = i + ft_strlen(aux) - 2;
				free(aux);
			}
			else if (arg[i + 1] == '$')
			{
				aux = ft_itoa(shell->main_pid);
				arg = str_replace_segment(arg, aux, i, 2);
				i = i + ft_strlen(aux) - 2;
				free(aux);
			}
		}
		i++;
	}
	return (arg);
}

static int	check_quotes_type(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
 		if (str[i] == '\"')
			return (1);
		else if (str[i] == '\'')
			return (2);
	}
	return (0);
}
/*
==452139== 
==452139== FILE DESCRIPTORS: 3 open (3 std) at exit.
==452139== 
==452139== HEAP SUMMARY:
==452139==     in use at exit: 220,106 bytes in 511 blocks
==452139==   total heap usage: 804 allocs, 293 frees, 246,229 bytes allocated
==452139== 
==452139== 2 bytes in 1 blocks are still reachable in loss record 1 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40C20C: ft_itoa (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x402B83: handle_shell_value (copy_env.c:12)
==452139==    by 0x402B2A: copy_env (copy_env.c:44)
==452139==    by 0x408C00: init_shell (init_shell.c:34)
==452139==    by 0x40A8BA: main (main.c:32)
==452139== 
==452139== 16 bytes in 1 blocks are still reachable in loss record 11 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40BCFE: ft_calloc (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x402AB3: copy_env (copy_env.c:32)
==452139==    by 0x408C00: init_shell (init_shell.c:34)
==452139==    by 0x40A8BA: main (main.c:32)
==452139== 
==452139== 16 bytes in 1 blocks are still reachable in loss record 13 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40BCFE: ft_calloc (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x40B687: ft_split (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x404E0B: ft_parse_split (parse_split.c:71)
==452139==    by 0x4064D8: parse_line (parsing_1.c:11)
==452139==    by 0x404F02: parse (parsing_2.c:55)
==452139==    by 0x406FE6: minishellers (run_shell.c:38)
==452139==    by 0x406F93: run_shell (run_shell.c:81)
==452139==    by 0x407079: shelling (run_shell.c:93)
==452139==    by 0x40A8EC: main (main.c:37)
==452139== 
==452139== 16 bytes in 1 blocks are still reachable in loss record 14 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40BCFE: ft_calloc (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x407186: copy_array (copy_array.c:12)
==452139==    by 0x40453E: process_cmd_args (constructor_6.c:69)
==452139==    by 0x403D14: parse_cmd (constructor_2.c:79)
==452139==    by 0x403AF9: build_cmds (constructor_2.c:109)
==452139==    by 0x404F7F: parse (parsing_2.c:66)
==452139==    by 0x406FE6: minishellers (run_shell.c:38)
==452139==    by 0x406F93: run_shell (run_shell.c:81)
==452139==    by 0x407079: shelling (run_shell.c:93)
==452139==    by 0x40A8EC: main (main.c:37)
==452139== 
==452139== 24 bytes in 1 blocks are still reachable in loss record 17 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40BCFE: ft_calloc (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x408B26: init_separator (init_shell.c:8)
==452139==    by 0x408C10: init_shell (init_shell.c:35)
==452139==    by 0x40A8BA: main (main.c:32)
==452139== 
==452139== 52 bytes in 1 blocks are still reachable in loss record 24 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40ADA4: ft_strdup (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x408DDE: dollar_sign (dollar_sign_command.c:27)
==452139==    by 0x404F76: parse (parsing_2.c:65)
==452139==    by 0x406FE6: minishellers (run_shell.c:38)
==452139==    by 0x406F93: run_shell (run_shell.c:81)
==452139==    by 0x407079: shelling (run_shell.c:93)
==452139==    by 0x40A8EC: main (main.c:37)
==452139== 
==452139== 52 bytes in 1 blocks are still reachable in loss record 25 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40ADA4: ft_strdup (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x4039A6: init_cmd (constructor_2.c:10)
==452139==    by 0x403C7B: parse_cmd (constructor_2.c:71)
==452139==    by 0x403AF9: build_cmds (constructor_2.c:109)
==452139==    by 0x404F7F: parse (parsing_2.c:66)
==452139==    by 0x406FE6: minishellers (run_shell.c:38)
==452139==    by 0x406F93: run_shell (run_shell.c:81)
==452139==    by 0x407079: shelling (run_shell.c:93)
==452139==    by 0x40A8EC: main (main.c:37)
==452139== 
==452139== 52 bytes in 1 blocks are still reachable in loss record 26 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40ADA4: ft_strdup (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x40429C: assemble_cmd_path (constructor_4.c:6)
==452139==    by 0x4040BA: build_cmd (constructor_3.c:46)
==452139==    by 0x40395D: built_in_handle (constructor_1.c:63)
==452139==    by 0x403C99: parse_cmd (constructor_2.c:73)
==452139==    by 0x403AF9: build_cmds (constructor_2.c:109)
==452139==    by 0x404F7F: parse (parsing_2.c:66)
==452139==    by 0x406FE6: minishellers (run_shell.c:38)
==452139==    by 0x406F93: run_shell (run_shell.c:81)
==452139==    by 0x407079: shelling (run_shell.c:93)
==452139==    by 0x40A8EC: main (main.c:37)
==452139== 
==452139== 52 bytes in 1 blocks are still reachable in loss record 27 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40ADA4: ft_strdup (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x403DEE: cmd_processor_a (constructor_2.c:38)
==452139==    by 0x403CBD: parse_cmd (constructor_2.c:75)
==452139==    by 0x403AF9: build_cmds (constructor_2.c:109)
==452139==    by 0x404F7F: parse (parsing_2.c:66)
==452139==    by 0x406FE6: minishellers (run_shell.c:38)
==452139==    by 0x406F93: run_shell (run_shell.c:81)
==452139==    by 0x407079: shelling (run_shell.c:93)
==452139==    by 0x40A8EC: main (main.c:37)
==452139== 
==452139== 52 bytes in 1 blocks are still reachable in loss record 28 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40ADA4: ft_strdup (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x4071B5: copy_array (copy_array.c:16)
==452139==    by 0x40453E: process_cmd_args (constructor_6.c:69)
==452139==    by 0x403D14: parse_cmd (constructor_2.c:79)
==452139==    by 0x403AF9: build_cmds (constructor_2.c:109)
==452139==    by 0x404F7F: parse (parsing_2.c:66)
==452139==    by 0x406FE6: minishellers (run_shell.c:38)
==452139==    by 0x406F93: run_shell (run_shell.c:81)
==452139==    by 0x407079: shelling (run_shell.c:93)
==452139==    by 0x40A8EC: main (main.c:37)
==452139== 
==452139== 112 bytes in 1 blocks are still reachable in loss record 35 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40BCFE: ft_calloc (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x40398E: init_cmd (constructor_2.c:8)
==452139==    by 0x403C7B: parse_cmd (constructor_2.c:71)
==452139==    by 0x403AF9: build_cmds (constructor_2.c:109)
==452139==    by 0x404F7F: parse (parsing_2.c:66)
==452139==    by 0x406FE6: minishellers (run_shell.c:38)
==452139==    by 0x406F93: run_shell (run_shell.c:81)
==452139==    by 0x407079: shelling (run_shell.c:93)
==452139==    by 0x40A8EC: main (main.c:37)
==452139== 
==452139== 168 bytes in 1 blocks are still reachable in loss record 37 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40BCFE: ft_calloc (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x408BCA: init_shell (init_shell.c:28)
==452139==    by 0x40A8BA: main (main.c:32)
==452139== 
==452139== 552 bytes in 1 blocks are still reachable in loss record 40 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40180C: convert_env_to_array (external_cmd.c:61)
==452139==    by 0x40172C: execute_external (external_cmd.c:12)
==452139==    by 0x4069AE: run_no_pipe (exec_handler.c:93)
==452139==    by 0x406A5F: processor (exec_handler.c:117)
==452139==    by 0x406C66: run_commands (run_cmds.c:62)
==452139==    by 0x406FEF: minishellers (run_shell.c:39)
==452139==    by 0x406F93: run_shell (run_shell.c:81)
==452139==    by 0x407079: shelling (run_shell.c:93)
==452139==    by 0x40A8EC: main (main.c:37)
==452139== 
==452139== 856 bytes in 68 blocks are still reachable in loss record 44 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40B159: ft_substr (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x4028CA: chng_env_var (add_env_vars.c:11)
==452139==    by 0x40284D: assign_env_var (add_env_vars.c:38)
==452139==    by 0x402B10: copy_env (copy_env.c:41)
==452139==    by 0x408C00: init_shell (init_shell.c:34)
==452139==    by 0x40A8BA: main (main.c:32)
==452139== 
==452139== 2,720 bytes in 68 blocks are still reachable in loss record 58 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40BCFE: ft_calloc (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x4029E1: add_env_var (add_env_vars.c:51)
==452139==    by 0x402AFC: copy_env (copy_env.c:40)
==452139==    by 0x408C00: init_shell (init_shell.c:34)
==452139==    by 0x40A8BA: main (main.c:32)
==452139== 
==452139== 3,062 bytes in 67 blocks are still reachable in loss record 59 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40ADA4: ft_strdup (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x4028E1: chng_env_var (add_env_vars.c:12)
==452139==    by 0x40284D: assign_env_var (add_env_vars.c:38)
==452139==    by 0x402B10: copy_env (copy_env.c:41)
==452139==    by 0x408C00: init_shell (init_shell.c:34)
==452139==    by 0x40A8BA: main (main.c:32)
==452139== 
==452139== 3,920 bytes in 68 blocks are still reachable in loss record 62 of 85
==452139==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==452139==    by 0x40BA81: ft_strjoin (in /home/nneves-a/42/42_common_core/minishell_this_one/minishell)
==452139==    by 0x4018BB: convert_env_to_array (external_cmd.c:75)
==452139==    by 0x40172C: execute_external (external_cmd.c:12)
==452139==    by 0x4069AE: run_no_pipe (exec_handler.c:93)
==452139==    by 0x406A5F: processor (exec_handler.c:117)
==452139==    by 0x406C66: run_commands (run_cmds.c:62)
==452139==    by 0x406FEF: minishellers (run_shell.c:39)
==452139==    by 0x406F93: run_shell (run_shell.c:81)
==452139==    by 0x407079: shelling (run_shell.c:93)
==452139==    by 0x40A8EC: main (main.c:37)
==452139== 
==452139== LEAK SUMMARY:
==452139==    definitely lost: 0 bytes in 0 blocks
==452139==    indirectly lost: 0 bytes in 0 blocks
==452139==      possibly lost: 0 bytes in 0 blocks
==452139==    still reachable: 11,724 bytes in 284 blocks
==452139==         suppressed: 208,382 bytes in 227 blocks
==452139== 
==452139== For lists of detected and suppressed errors, rerun with: -s
==452139== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


*/