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
#include <cstdlib>
#include <cstring>
#include <string.h>
#include <unistd.h>

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
	if (ret == -1)
	{
		ft_printf_fd(2, "Can't open %d\n", path);
		exit(EXIT_FAILURE);
	}
	return (ret);
}

char	*get_path(char *str, char **envp)
{
	char	*cmd;
	char	**path;
	int		i;
	int		err;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
		{
			i = 0;
			err = 0;
			path = ft_split(envp[i], ':');
			while (path[i])
			{
				err = access(path[i], F_OK);
				if (err == 0)
					return (path[i]);
			}
			if (err == -1)
				display_err_and_exit(strerror(errno));
		}
		i++;
	}
	return (NULL);
	// return (cmd);
}

static void	exec_cmd(char *argv, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = ft_split(argv, ' ');
	if (!cmd)
		display_err_and_exit(MALLOC_ERR);
	path = get_path(cmd[0], envp);
	if (execve(path, cmd, envp) == -1)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	ft_free_tab(cmd);
}

static void	create_pipe_and_redirect(char *arg, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		display_err_and_exit("An error occured while opening the pipe.\n");
	pid = fork();
	if (pid == -1)
		display_err_and_exit("An error occured while forking processes.\n");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		exec_cmd(arg, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

static void	execute_command(int ac, char **av, char **envp)
{
	int	i;
	int	in;
	int	out;

	i = 2;
	in = open_file(av[1], O_RDONLY);
	out = open_file(av[ac - 1], O_TRUNC);
	dup2(in, STDIN_FILENO);
	while (i < ac - 2)
	{
		// exec_cmd(av[i++], envp);
		create_pipe_and_redirect(av[i++], envp);
	}
	dup2(out, STDOUT_FILENO);
	exec_cmd(av[ac - 2], envp);
}

int	main(int ac, char **av, char **envp)
{
	int	i;

	i = 2;
	if (ac > 4)
		execute_command(ac, av, envp);
	usage();
	return (0);
}

