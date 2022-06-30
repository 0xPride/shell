/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumouss <aoumouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:00:49 by habouiba          #+#    #+#             */
/*   Updated: 2022/06/30 13:33:25 by aoumouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>

# include "types.h"
# include "defs.h"

# include "libft.h"
# include "lexer.h"
# include "parser.h"
# include "executer.h"
# include "builtins.h"
# include "prompt.h"
# include "utils.h"
# include "readline/readline.h"
# include "readline/history.h"

extern int	g_exit_code;

#endif // MINISHELL_H
