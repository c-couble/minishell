/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:42:43 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/25 23:11:27 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "wildcard.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

DIR	*get_file_path(t_wildcard *wild, char *path);

int	is_file(char *s)
{
	if (ft_strcmp(s, ".") == 0)
		return (0);
	if (ft_strcmp(s, "..") == 0)
		return (0);
	return (1);
}

int	add_file_tok(t_lexer *filenames, char *s)
{
	t_lexer_tok	token;

	if (ft_strcmp(s, ".") == 0 || ft_strcmp(s, "..") == 0)
		return (0);
	token.content = ft_strdup(s);
	if (token.content == NULL)
		return (-1);
	token.type = WORD;
	if (add_vector(filenames, &token, 1) == -1)
		return (-1);
	return (0);
}

int	get_files_ls(t_wildcard *w, t_lexer *pattern, t_lexer *fname, char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*tmp;

	dir = get_file_path(w, path);
	if (dir == NULL)
		return (0);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (is_file(entry->d_name) && is_wildcard_match(w, pattern, entry->d_name))
		{
			tmp = entry->d_name;
			if (path)
			{
				tmp = ft_strjoin(path, entry->d_name);
				if (path == NULL)
					return (-1);
			}
			if (add_file_tok(fname, tmp) == -1)
			{
				closedir(dir);
				return (-1);
			}
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}

DIR	*get_file_path(t_wildcard *wild, char *path)
{
	char 			*wd;
	DIR				*dir;

	(void)wild;
	wd = ft_strdup(wild->wd);
	if (wd == NULL)
		return (NULL);
	if (path)
	{
		if (wild->wd[ft_strlen(wild->wd) -1] == '/')
		{
			wd = ft_strjoin(wd, path);
		}
		else
		{
			wd = ft_strjoin_three(wd, "/", path);
			if (wd == NULL)
				return (NULL);
		}
	}
	printf("wd = %s\n", wd);
	dir = opendir(wd);
	return (dir);
}
