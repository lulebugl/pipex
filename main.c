/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 16:19:40 by llebugle          #+#    #+#             */
/*   Updated: 2024/12/08 16:19:43 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <fcntl.h>

static void	execute_command(char *argv, char **envp, t_data *data)
{
	char	**cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = ft_split(argv, ' ');
	if (!cmd)
		display_err_and_exit(strerror(ENOSPC), data);
	path = get_path(cmd[0], envp);
	if (!path)
	{
		ft_free_tab(cmd);
		if (errno == 0)
			display_err_and_exit("Command not found.\n", data);
		display_err_and_exit(strerror(errno), data);
		exit(1);
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_free_tab(cmd);
		free(path);
		display_err_and_exit(strerror(errno), data);
	}
}

static void	create_pipe_process(char *arg, char **envp, t_data *data)
{
	pid_t	pid;

	if (pipe(data->pipe_fd) == -1)
		display_err_and_exit(strerror(errno), data);
	pid = fork();
	if (pid == -1)
		display_err_and_exit(strerror(errno), data);
	if (pid == 0)
	{
		close(data->pipe_fd[0]);
		if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
			display_err_and_exit(strerror(errno), data);
		close(data->pipe_fd[1]);
		execute_command(arg, envp, data);
	}
	else
	{
		close(data->pipe_fd[1]);
		if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1)
			display_err_and_exit(strerror(errno), data);
		close(data->pipe_fd[0]);
		waitpid(pid, NULL, 0);
	}
}

static void	process_pipes(int ac, char **av, char **envp)
{
	int		i;
	t_data	data;

	i = 2;
	ft_memset(&data, -1, sizeof(t_data));
	data.in_fd = open_file(av[1], O_RDONLY);
	data.out_fd = open_file(av[ac - 1], O_TRUNC);
	if (data.in_fd == -1 || data.out_fd == -1)
		display_err_and_exit(strerror(errno), &data);
	if (dup2(data.in_fd, STDIN_FILENO) == -1)
		display_err_and_exit(strerror(errno), &data);
	close(data.in_fd);
	while (i < ac - 2)
		create_pipe_process(av[i++], envp, &data);
	if (dup2(data.out_fd, STDOUT_FILENO) == -1)
		display_err_and_exit(strerror(errno), &data);
	close(data.out_fd);
	execute_command(av[ac - 2], envp, &data);
}

static void	process_here_doc(int ac, char **av, char **envp)
{
	int		i;
	pid_t	reader;
	t_data	data;
	char    *line;
	
	i = 3;
	data.out_fd = open_file(av[ac - 1], O_APPEND);
	if (pipe(data.pipe_fd) == -1)
		display_err_and_exit(strerror(errno), &data);
	reader = fork();
	if (reader == 0)
	{
		close(data.pipe_fd[0]);
		while (1)
		{
			line = get_next_line(0);
			if (!line)
				break ;
			if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
				clean_exit(&data);
			write(data.pipe_fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	else
	{
		close(data.pipe_fd[1]);
		dup2(data.pipe_fd[0], STDIN_FILENO);
		wait(NULL);
	}
	while (i < ac - 2)
		create_pipe_process(av[i++], envp, &data);
	if (dup2(data.out_fd, STDOUT_FILENO) == -1)
		display_err_and_exit(strerror(errno), &data);
	close(data.out_fd);
	execute_command(av[ac - 2], envp, &data);
}

int	main(int ac, char **av, char **envp)
{
	int	i;

	i = 2;
	if (ac > 4)
	{
		if (ac > 5 && ft_strncmp(av[1], "here_doc", 8) == 0)
			process_here_doc(ac, av, envp);
		else
			process_pipes(ac, av, envp);
	}
	usage();
	return (0);
}

