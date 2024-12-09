/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:16:03 by llebugle          #+#    #+#             */
/*   Updated: 2024/12/09 17:16:11 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	usage(void)
{
	ft_printf_fd(1, "Usage : ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n");
	ft_printf_fd(1,
		"    ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n");
	exit(0);
}

void	display_err_and_exit(char *msg)
{
	if (msg)
		perror(msg);
	exit(EXIT_FAILURE);
}
