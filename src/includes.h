/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:24:01 by nneves-a          #+#    #+#             */
/*   Updated: 2025/06/01 17:24:59 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

// headers from system libraries
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

// headers from lib_ft directory
# include "../inc/lib_ft/ft_printf.h"
# include "../inc/lib_ft/get_next_line.h"
# include "../inc/lib_ft/libft.h"

// headers from inc directorys
# include "ft_typedefs.h"
# include "unicodes.h"

// headers from src directory
# include "builtins/ft_builtins.h"
# include "cmd_as_regular_user/ft_cmd_as_regular_user.h"
# include "debugging/ft_debug.h"
# include "env/ft_env.h"
# include "frees/ft_free.h"
# include "history/ft_history.h"
# include "inits/ft_inits.h"
# include "parsing/ft_parsing.h"
# include "redirections/redirections.h"
# include "run/ft_run.h"
# include "signals/ft_signal.h"
# include "utils/ft_utils.h"
# include "validations/ft_validations.h"
# include "wildcards/ft_wildcard.h"

// headers from src/pipes directory
# include "pipes/ft_pipes.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
// Maximum number of bytes in a pathname
// Typical maximum path length in many systems
// getconf PATH_MAX / to determine the actual limit for your system.
# endif

#endif
