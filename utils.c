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

int	open_file(char *path, int flag)
{
	int	ret;

	ret = 0;
	if (flag == O_APPEND)
		ret = open(path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (flag == O_TRUNC)
		ret = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (flag == O_RDONLY)
		ret = open(path, O_RDONLY, 0777);
	return (ret);
}

void	usage(void)
{
	ft_printf_fd(1, "Usage : ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n");
	ft_printf_fd(1,
		"    ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n");
	exit(0);
}

void	display_err_and_exit(char *msg, t_data *data)
{
 	if (data->in_fd > 2)
        close(data->in_fd);
    if (data->out_fd > 2)
        close(data->out_fd);
    if (data->pipe_fd[0] > 2)
        close(data->pipe_fd[0]);
    if (data->pipe_fd[1] > 2)
        close(data->pipe_fd[1]);
	if (msg)
		perror(msg);
	exit(EXIT_FAILURE);
}
