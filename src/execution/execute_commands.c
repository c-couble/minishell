/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 05:20:04 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/15 03:01:29 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "expander.h"
#include "minishell.h"
#include "lexer.h"
#include "signals.h"
#include "vector.h"
#include "execution.h"
#include "util.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

static int		end_shell(t_ms *ms, t_lexer *lexer, size_t i);
static int		write_signal(t_ms *ms);
static int		run_get_result(t_ms *ms, t_lexer *lexer, size_t i);
static size_t	next_command(t_lexer *lexer, size_t i);

int	execute_commands(t_ms *ms, t_lexer *lexer)
{
	size_t		i;
	t_lexer_tok	*token;

	i = 0;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == COMMAND || token->type == SUBSHELL)
		{
			ms->lastexit = run_get_result(ms, lexer, i);
			if (ms->lastexit == -1)
				return (-1);
			if (g_sig == SIGINT)
			{
				ms->signaled = 1;
				ms->lastexit = 128 + SIGINT;
			}
			if (set_exitcode_str(ms, ms->lastexit) == -1)
				return (-1);
		}
		i = next_command(lexer, i);
		if (write_signal(ms) == -1)
			return (-1);
		if (end_shell(ms, lexer, i))
			break ;
		++i;
	}
	return (ms->lastexit);
}

static int	end_shell(t_ms *ms, t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;

	if (ms->lastexit == -1)
		return (1);
	if (ms->signaled && ms->lastexit == 128 + SIGINT)
		return (1);
	if (i >= lexer->size)
		return (0);
	token = at_vector(lexer, i);
	return ((token->type == LOGICAL_AND && ms->lastexit != 0)
		|| (token->type == LOGICAL_OR && ms->lastexit == 0));
}

static int	write_signal(t_ms *ms)
{
	int	ret;

	if (ms->signaled && ms->lastexit == 128 + SIGINT)
		ret = write(STDERR_FILENO, "\n", 1);
	else if (ms->signaled && ms->lastexit == 128 + SIGQUIT)
		ret = write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	else
		return (0);
	if (ret == -1)
		return (-1);
	return (0);
}

static int	run_get_result(t_ms *ms, t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;
	pid_t		pid;
	char		**s;

	token = at_vector(lexer, i);
	pid = -1;
	if (next_token(lexer, i) == PIPE)
		pid = execute_pipeline(ms, lexer, i);
	else if (token->type == COMMAND)
	{
		if (perform_expansions(ms, token) == -1)
			return (-1);
		if (g_sig == SIGINT)
			return (130);
		if (token->args.size != 0)
		{
			s = at_vector(&token->args, 0);
			if (s != NULL && is_builtin(*s))
				return (run_builtin(ms, token));
		}
		pid = execute_simple_command(ms, lexer, i);
	}
	else if (token->type == SUBSHELL)
		pid = execute_subshell(ms, lexer, i);
	if (pid == -1)
		return (-1);
	return (wait_children(ms, pid));
}

static size_t	next_command(t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;

	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == LOGICAL_AND || token->type == LOGICAL_OR)
			return (i);
		++i;
	}
	return (i);
}
