/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:52:26 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/04 13:30:38 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	const char	*prompt = "minishell $> ";
	char		*str;

	(void)argc;
	(void)argv;
	(void)envp;
	str = readline(prompt);
	if (str == NULL)
		return (1);
	while (str)
	{
		free(str);
		str = readline(prompt);
		if (str == NULL)
			break ;
	}
	rl_clear_history();
	return (0);
}
