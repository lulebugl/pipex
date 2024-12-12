/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:12:11 by llebugle          #+#    #+#             */
/*   Updated: 2024/12/08 14:56:43 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_data
{
	int	in_fd;
	int	out_fd;
	int	pipe_fd[2];
}		t_data;

int		open_file(char *path, int flag);
char	*get_path(char *str, char **envp);
void	display_err_and_exit(char *msg, t_data *data);
void	clean_exit(t_data *data);
void	usage(void);

#endif
