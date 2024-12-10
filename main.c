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

static void	execute_command(char *argv, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = ft_split(argv, ' ');
	if (!cmd)
		display_err_and_exit(strerror(ENOSPC));
	path = get_path(cmd[0], envp);
	if (!path)
	{
		ft_free_tab(cmd);
		if (errno == 0)
			display_err_and_exit("Error.\n");
		display_err_and_exit(strerror(errno));
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_free_tab(cmd);
		free(path);
		display_err_and_exit(strerror(errno));
	}
}

static void	create_pipe_process(char *arg, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		display_err_and_exit(strerror(errno));
	pid = fork();
	if (pid == -1)
		display_err_and_exit(strerror(errno));
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			display_err_and_exit(strerror(errno));
		close(fd[1]);
		execute_command(arg, envp);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			display_err_and_exit(strerror(errno));
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

static void	process_pipes(int ac, char **av, char **envp)
{
	int	i;
	int	in;
	int	out;

	i = 2;
	in = open_file(av[1], O_RDONLY);
	out = open_file(av[ac - 1], O_TRUNC);
	if (dup2(in, STDIN_FILENO) == -1)
		display_err_and_exit(strerror(errno));
	close(in);
	while (i < ac - 2)
		create_pipe_process(av[i++], envp);
	if (dup2(out, STDOUT_FILENO) == -1)
		display_err_and_exit(strerror(errno));
	close(out);
	execute_command(av[ac - 2], envp);
}

int	main(int ac, char **av, char **envp)
{
	int	i;

	i = 2;
	if (ac > 4)
		process_pipes(ac, av, envp);
	usage();
	return (0);
}

