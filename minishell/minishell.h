/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:16:38 by victor            #+#    #+#             */
/*   Updated: 2024/07/07 14:36:06 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT_COMMAND_STACK_SIZE 6
# define PROMPT_INPUT_BUFFER_SIZE 1024
# define SCREEN_CLEAR "\033[2J"
# define CURSOR_MOVE_HOME "\033[H"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define RED "\033[0;31m"
# define CURSOR_MOVE_UP "\033[A"
# define CURSOR_MOVE_DOWN "\033[B"
# define CURSOR_MOVE_RIGHT "\033[C"
# define CURSOR_MOVE_LEFT "\033[D"
# define CURSOR_POSITION_GET "\033[6n"
# define CURSOR_POSITION_SET "\033[%d;%dH"
# define CURSOR_POSITION_SAVE "\033[s"
# define CURSOR_POSITION_RESTORE "\033[u"
# define SCREEN_CLEAR_TO_EOL "\033[K"

typedef struct s_prompt
{
	char	*command;
	/*char	**commands;*/
	/*char	***command_argv;*/
	/*uint32_t	number_of_commands;*/
	/*uint32_t	total_prompt_lenght;*/
}				t_prompt;

enum e_alloc
{
	ADD,
	CLEAN,
	END,
	FREE,
};

typedef struct s_clean
{
	void			*content;
	void			(*clean)(void *del);
	struct s_clean	*next;
}					t_clean;

/* Memory Management */
void	lst_memory(void *mem, void (*del)(void *c), int mode);
t_clean	*lst_node_new(void *content, void (*del)(void *));
void	lst_node_del(t_clean **lst);
void	lst_node_del_clean(t_clean **lst, void *mem);
int		lst_add_back(t_clean **node, t_clean *node_new);
void	lst_list_clean(t_clean **head);

/* This function stores a pointer to the return value on the memory management linked list */
char	*find_absolute_path(const char **env, char *input);

void terminal_raw_mode_disable();
void terminal_raw_mode_enable();

int		p_stderr(int stderr_fd, const char *error, char const *specifier);

/* Ft Wrapper */
void	ft_pipe(int pipefd[2], char const *specifier);
void	ft_fork(pid_t *pid, char const *specifier);
int		ft_close(int fd, char const *specifier);
void	ft_dup2(int fd_old, int fd_new, const char *specifier);
void	ft_open(int *fd, const char *path, int flag, int mode);

void	*m_tokenizer(const char *input, char const **env);
void command_execute(char const *command_path, char const **argv, char const **env);
bool	buildin_execute(char const *command, char const **argv);
void	ft_chdir(const char *path);
void	ft_exit();

void	free_split(void *back);

#endif
