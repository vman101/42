/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:15:17 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/11 20:25:43 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <stdbool.h>
# include "list_debug/lst_debug.h"
# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef	struct	s_file
{
	char	*path;
	int		mode;
	int		fd;
}			t_file;

typedef struct	s_cmd
{
	t_file	*file;
	char	*path_absolute;
	char	**argv;
	char	**env;
	int		pipefd;
	pid_t	cpid;
}			t_cmd;

typedef struct s_clean
{
	void	*content;
	void	(*clean)(void *del);
	struct	s_clean *next;
}			t_clean;

enum e_file
{
	LAUNCH = 0,
	IN = 0,
	CMD0 = 2,
	CMD1 = 3,
	OUT = 1,
	FILE_IN = 1,
	FILE_OUT = 4,
	PIPE_IN = 1,
	PIPE_OUT = 0,
};

void	lst_list_clean(t_clean **head);
char	*find_absolute_path(char **env, char *input);
void	free_split(char **back);

#endif
