/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:15:17 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/15 13:39:43 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <stdbool.h>
# include "libft/libft.h"
# include "printf/ft_printf.h"
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
}			t_file;

typedef struct s_cmd
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
	void			*content;
	void			(*clean)(void *del);
	struct s_clean	*next;
}					t_clean;

enum e_alloc
{
	ADD,
	CLEAN,
	END,
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
int		lst_add_back(t_clean **node, t_clean *node_new);
void	lst_list_clean(t_clean **head);
char	*find_absolute_path(char **env, char *input);
void	free_split(void *back);
void	lst_memory(void *mem, void (*del)(void *c), int mode);

int		p_stderr(int stderr_fd, const char *error, char const *specifier);

bool	pipe_in(t_cmd *cmd_in, int pipefd[2]);
bool	pipe_out(t_cmd *cmd_out, int pipefd[2]);

t_cmd	*command_create(char **input, char **env, t_file *files);
t_file	*file_create(char const *path, int flag, int mode);
void	command_destroy(void *cmd_del);
void	file_destroy(void *file_del);

#endif
