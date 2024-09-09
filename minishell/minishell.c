/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:22:34 by victor            #+#    #+#             */
/*   Updated: 2024/07/07 12:35:37 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>

typedef int t_history;

void ft_chdir(const char *path)
{
	if (path == NULL)
	{
		path = getenv("HOME");
	}
	if (chdir(path) == -1)
	{
		perror("cd");
	}
}

void	signal_handle(int signal)
{
	(void)signal;
}

void	cursor_position_get(uint32_t cursor_position[2])
{
	char	*cursor_position_str;
	char	*cursor_position_str_ptr;
	char	*cursor_position_str_ptr2;
	char	cursor_position_str_buffer[32];
	int		bytes_read;

	write(1, CURSOR_POSITION_GET, 4);
	bytes_read = read(0, cursor_position_str_buffer, 32);
	if (bytes_read == -1)
	{
		perror("read");
		return ;
	}
	cursor_position_str = ft_strdup(cursor_position_str_buffer);
	if (!cursor_position_str)
	{
		perror("ft_strndup");
		return ;
	}
	cursor_position_str_ptr = cursor_position_str;
	cursor_position_str_ptr2 = ft_strchr(cursor_position_str, ';');
	if (!cursor_position_str_ptr2)
	{
		ft_free((void **)&cursor_position_str);
		return ;
	}
	*cursor_position_str_ptr2 = 0;
	cursor_position[0] = ft_atoi(cursor_position_str_ptr);
	cursor_position_str_ptr = cursor_position_str_ptr2 + 1;
	cursor_position_str_ptr2 = ft_strchr(cursor_position_str_ptr, 'R');
	if (!cursor_position_str_ptr2)
	{
		ft_free((void **)&cursor_position_str);
		return ;
	}
	*cursor_position_str_ptr2 = 0;
	cursor_position[1] = ft_atoi(cursor_position_str_ptr);
	ft_free((void **)&cursor_position_str);
}

uint8_t	prompt_escape_sequence_arrowkeys(uint32_t *cursor_position_current)
{
	char		escape_sequence[2];

	if (read(0, escape_sequence, 2) == -1)
	{
		perror("read");
		return (0);
	}
	if (escape_sequence[0] == 91 && escape_sequence[1] == 65)
		;
	else if (escape_sequence[0] == 91 && escape_sequence[1] == 66)
		;
	else if (escape_sequence[0] == 91 && escape_sequence[1] == 67)
	{
		(*cursor_position_current)++;
		ft_printf(CURSOR_MOVE_RIGHT);
	}
	else if (escape_sequence[0] == 91 && escape_sequence[1] == 68)
	{
		(*cursor_position_current)--;
		ft_printf(CURSOR_MOVE_LEFT);
	}
	return (1);
}

char	*prompt_get_input(t_prompt *prompt)
{
	char		*input;
	char		*input_free_ptr;
	char		character;
	uint32_t	cursor_position_original[2];
	uint32_t	cursor_position_new[2];
	uint32_t	cursor_position_current;
	int32_t		bytes_read;
	uint32_t	total_bytes_read;

	(void)prompt;
	input = ft_calloc(1, PROMPT_INPUT_BUFFER_SIZE + 1);
	if (!input)
	{
		perror("ft_calloc");
		return (NULL);
	}
	total_bytes_read = 0;
	character = 0;
	cursor_position_current = 0;
	while (1)
	{
		cursor_position_get(cursor_position_original);
		bytes_read = read(0, &character, 1);
		total_bytes_read += bytes_read;
		if (bytes_read == -1)
		{
			ft_free((void **)&input);
			perror("read");
			return (NULL);
		}
		else if (character == 27)
		{
			if (!prompt_escape_sequence_arrowkeys(&cursor_position_current))
				return (ft_free((void **)&input), NULL);
		}
		/*TODO Implement Backspace Delete Behavior*/
		else if (character == 127 && cursor_position_current > 0)
		{
			cursor_position_current--;
			input[cursor_position_current] = ' ';
			ft_printf(CURSOR_MOVE_LEFT);
			write(1, " ", 1);
		}
		else if (character == '\n')
			break ;
		else if (bytes_read == 0 && total_bytes_read == 0 && character == 0)
		{
			ft_free((void **)&input);
			return (NULL);
		}
		else if (total_bytes_read == PROMPT_INPUT_BUFFER_SIZE)
		{
			input_free_ptr = input;
			input = ft_calloc(1, PROMPT_INPUT_BUFFER_SIZE + total_bytes_read + 1);
			if (!input)
			{
				perror("ft_calloc");
				return (NULL);
			}
			ft_memcpy(input, input_free_ptr, total_bytes_read);
			ft_free((void **)&input_free_ptr);
		}
		else if (total_bytes_read > 0)
			input[cursor_position_current] = character;
		ft_printf(CURSOR_POSITION_SAVE);
		cursor_position_get(cursor_position_new);
		ft_printf(CURSOR_POSITION_RESTORE);
		ft_printf("%s", input);
		/*ft_printf(CURSOR_POSITION_SET, cursor_position_new[0], cursor_position_new[1]);*/
		cursor_position_current++;
	}
	if (total_bytes_read == 0)
	{
		ft_free((void **)&input);
		return (NULL);
	}
	if (character == '\n')
		write(1, &character, 1);
	return (input);
}

void	prompt_destroy(void *prompt)
{
	t_prompt	*prompt_ptr;

	prompt_ptr = (t_prompt *)prompt;
	ft_free((void **)&prompt_ptr->command);
	ft_free((void **)&prompt_ptr);
}

void	prompt_display(char *pwd)
{
	ft_printf(GREEN);
	ft_printf("%s$ ", pwd);
	ft_printf(RESET);
}

t_prompt	*prompt_get(t_prompt *prompt)
{
	char		*pwd;

	pwd = getcwd(NULL, 0);
	prompt_display(pwd);
	ft_free((void **)&pwd);
	prompt_get_input(prompt);
	return (prompt);
}

int main(int argc, char **argv, char **env)
{
	t_prompt	*prompt;
	t_history	history;
	char		*input;

	/*terminal_raw_mode_enable();*/
	(void)argc;
	(void)argv;
	(void)env;
	ft_open(&history, ".minishell_history", O_RDWR | O_CREAT, 0644);
	ft_printf(SCREEN_CLEAR);
	ft_printf(CURSOR_MOVE_HOME);
	prompt = ft_calloc(1, sizeof(t_prompt));
	lst_memory(prompt, prompt_destroy, ADD);
	while (1)
	{
		input = readline("minishell$ ");
		add_history(input);
		/*prompt_get(prompt);*/
		/*if (!prompt->command)*/
		/*	break ;*/
		/*m_tokenizer(prompt->command, (char const **)env);*/
		ft_free((void **)&prompt->command);
	}
	ft_close(history, "history");
	unlink(".minishell_history");
	terminal_raw_mode_disable();
	lst_memory(NULL, NULL, CLEAN);
}
