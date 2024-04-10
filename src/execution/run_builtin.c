/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:54:45 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/10 04:39:54 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"
#include "expander.h"
#include "lexer.h"
#include "execution.h"
#include "ft_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	run_builtin(t_ms *ms, t_lexer_tok *token)
{
	int	ret;
	int	stds[2];

	if (perform_expansions(ms, token) == -1)
		return (-1);
	if (save_stds(stds) == -1)
		return (-1);
	ret = perform_redirections(token);
	if (ret == -1)
		return (-1);
	if (ret == 1)
		return (1);
	ret = exec_builtins(ms, token);
	if (restore_stds(stds) == -1)
		return (-1);
	return (ret);
}
