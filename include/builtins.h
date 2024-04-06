/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:27:17 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/06 03:00:25 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env.h"
# include "minishell.h"
# include "lexer.h"

# define CMD_NOT_FOUND "minishell: %s: command not found\n"
# define DIR_NOT_EXIST "minishell: cd: The directory '%s' does not exist\n"
# define HOME_NOT_SET "minishell: cd: HOME not set\n"
# define TOO_MANY_ARGS "minishell: cd: too many arguments\n"
# define CD_MALLOC_ERR "minishell: cd: Memory alocation failure\n"

typedef enum e_builtins_type
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
}	t_builtins_type;

typedef int	(*t_builtin)(t_env *env, char **args);

typedef struct s_builtins_map
{
	char		*name;
	t_builtin	func;
}	t_buitlins_map;

void	clear_args(char **args);
int		get_argc(char **args);
char	**get_args(t_lexer *lexer, size_t index);
int		is_builtin(char *word);
int		exec_test(t_ms *minishell, t_lexer *lexer);
int		exec_builtins(t_ms *minishell, t_lexer *lexer, char **args);

int		ms_cd(t_env	*env, char **args);
int		get_canonical_path(char **curpath);
char	*get_dir_operand(t_env *env, char **args);
int		ms_echo(t_env *env, char **args);
int		ms_env(t_env *env, char **args);
int		ms_exit(t_ms *minishell, t_lexer *lexer, char **args);
int		ms_export(t_env *env, char **args);
int		ms_pwd(t_env *env, char **args);
int		ms_unset(t_env *env, char **args);

#endif
