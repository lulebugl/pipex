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

void	redirect_to_stdout(char **av, t_data *data)
{
	char	*line;

	close(data->pipe_fd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
			clean_exit(data);
		write(data->pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
}

int	open_file(char *path, int flag)
{
	int	ret;

	ret = 0;
	if (flag == O_APPEND)
		ret = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (flag == O_TRUNC)
		ret = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (flag == O_RDONLY)
		ret = open(path, O_RDONLY);
	return (ret);
}

void	usage(void)
{
	ft_printf_fd(1, "Usage : ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n");
	ft_printf_fd(1,
		"        ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n");
	exit(0);
}

void	clean_exit(t_data *data)
{
	if (data)
	{
		if (data->in_fd > 2)
			close(data->in_fd);
		if (data->out_fd > 2)
			close(data->out_fd);
		if (data->pipe_fd[0] > 2)
			close(data->pipe_fd[0]);
		if (data->pipe_fd[1] > 2)
			close(data->pipe_fd[1]);
	}
	exit(EXIT_SUCCESS);
}

void	display_err_and_exit(char *msg, t_data *data)
{
	if (msg)
	{
		if (errno == 0)
			ft_printf_fd(2, "%s", msg);
		else
			perror(msg);
	}
	if (data)
	{
		if (data->in_fd > 2)
			close(data->in_fd);
		if (data->out_fd > 2)
			close(data->out_fd);
		if (data->pipe_fd[0] > 2)
			close(data->pipe_fd[0]);
		if (data->pipe_fd[1] > 2)
			close(data->pipe_fd[1]);
	}
	exit(EXIT_FAILURE);
}
