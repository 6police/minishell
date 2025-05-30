/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:32:08 by nneves-a          #+#    #+#             */
/*   Updated: 2025/05/30 17:32:09 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H

# include "../minishell.h"

// function to assign the key and value to the environment variable
void	assign_env_var(t_env_var *env_var, char *env);

// function to add an env variable to the list
void	add_env_var(t_env **env);

// Function to create a copy of the environment
t_env	*copy_env(char **env);

// function to copy the environment list
t_env	*copy_env_list(t_env *env);

// fucntions to sort the environment variables

// function to swap the position of two environment variables
void	swap_env_var(t_env_var *a, t_env_var *b, t_env *env);

// function to sort the environment variables alphabetically
void	sort_env_list(t_env *env);

t_env	*new_env(void);

#endif
