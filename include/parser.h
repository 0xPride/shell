/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumouss <aoumouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:14:08 by habouiba          #+#    #+#             */
/*   Updated: 2022/06/18 17:15:24 by habouiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "types.h"
#include <dirent.h>

// int prev_exit_code;

t_list *parser(char *line, t_env_list *lst);
size_t  get_cmd_name(t_cmd *cmd, char const *s, t_env_list *lst);
size_t  get_input_redir(t_cmd *cmd, const char *s);
size_t  get_output_redir(t_cmd *cmd, const char *s);
size_t  get_args(t_cmd *cmd, const char *s);
size_t  parse_pipe(t_list **cmds, t_cmd **cmd, const char *s);
void    init_cmd(t_cmd *cmd);
size_t  parse_semicolon(t_list **cmds, t_cmd **cmd, const char *s);
size_t  parse_and(t_list **cmds, t_cmd **cmd, const char *s);
size_t  parse_or(t_list **cmds, t_cmd **cmd, const char *s);
int     is_inside_single_quotes(char *s, size_t idx);
char   *expand(const char *str, t_env_list *env);
size_t  expand_asterisk(t_cmd *cmd, const char *s);
char   *remove_double_quotes(const char *s, t_env_list *env);
#endif
