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
#include <fcntl.h>
#include <unistd.h>

void	usage(void)
{
	ft_printf_fd(2, "Error: Wrong number of argument\n");
	ft_printf_fd(1, "Usage : ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n");
	ft_printf_fd(1,
		"    ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n");
	exit(0);
}

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

static void	create_pipe_and_redirect(void)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		ft_printf_fd(2, "An error occured while opening the pipe.\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_printf_fd(2, "An error occured while forking processes.\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	in;
	int	out;

	i = 2;
	if (ac < 5)
		usage();
	in = open_file(av[1], O_RDONLY);
	out = open_file(av[ac - 1], O_TRUNC);
	dup2(in, STDIN_FILENO);
	while (i < ac - 2)
	{
		create_pipe_and_redirect()
	}
	return (0);
}

