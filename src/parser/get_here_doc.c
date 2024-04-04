/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:51:48 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/28 11:57:51 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "parser.h"
#include "vector.h"
#include <stdlib.h>

static int	handle_here_doc(t_lexer_tok *t1, t_lexer_tok *t2);

int	get_here_doc(t_lexer *lexer)
{
	t_lexer_tok	*tok;
	size_t		i;

	i = 0;
	while (i < lexer->size)
	{
		tok = at_vector(lexer, i);
		if (tok->type == HERE_DOC)
		{
			if (handle_here_doc(tok, at_vector(lexer, i + 1)) == -1)
				return (-1);
			remove_vector(lexer, i + 1);
		}
		++i;
	}
	return (0);
}

static int	handle_here_doc(t_lexer_tok *t1, t_lexer_tok *t2)
{
	char		path[25];
	t_vector	vector;

	init_vector(&vector, sizeof(char));
	if (fill_here_doc(&vector, path, t2->content) == -1)
	{
		clear_vector(&vector);
		return (-1);
	}
	clear_vector(&vector);
	t1->content = ft_strdup(path);
	if (t1->content == NULL)
		return (-1);
	free(t2->content);
	return (0);
}
