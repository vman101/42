/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:48:39 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/24 10:53:22 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_file
{
	char	*path;
	int		mode;
	int		fd;
	bool	tmp;
}			t_file;

typedef struct s_cmd
{
	char	*path_absolute;
	char	**argv;
	char	**env;
	pid_t	cpid;
}			t_cmd;

typedef struct s_clean
{
	void			*content;
	void			(*clean)(void *del);
	struct s_clean	*next;
}					t_clean;

enum e_alloc
{
	ADD,
	CLEAN,
	END,
	FREE,
};

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

t_clean	*lst_node_new(void *content, void (*del)(void *));
void	lst_node_del(t_clean **lst);
void	lst_node_del_clean(t_clean **lst, void *mem);
int		lst_add_back(t_clean **node, t_clean *node_new);
void	lst_list_clean(t_clean **head);
char	*find_absolute_path(char **env, char *input);
void	free_split(void *back);

void	lst_memory(void *mem, void (*del)(void *c), int mode);
int		p_stderr(int stderr_fd, const char *error, char const *specifier);
int		ft_close(int fd);
int		ft_closeall(int pipe[2][2]);

bool	pipe_in(t_cmd *cmd_in, int pipefd[2], int fd);
bool	pipe_out(t_cmd *cmd_out, int fd);
int		wait_pids(pid_t *pids, int pid_count);
bool	pipe_in2(t_cmd *cmd_in, int pipefd[2]);
bool	pipe_out2(t_cmd *cmd_out, int pipefd[2]);

t_cmd	*command_create(char **input, char **env);
t_file	*file_create(char const *path, int flag, int mode);
void	command_destroy(void *cmd_del);
void	file_destroy(void *file_del);

#endif
