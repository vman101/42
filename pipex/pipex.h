/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:15:17 by vvobis            #+#    #+#             */
/*   Updated: 2024/05/10 17:45:21 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "gnl2/get_next_line.h"

enum e_file
{
	LAUNCH = 0,
	IN = 0,
	CMD1 = 2,
	CMD2 = 3,
	OUT = 1,
	FILE_IN = 1,
	FILE_OUT = 4,
	PIPE_IN = 1,
	PIPE_OUT = 0,
};

#endif
