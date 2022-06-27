/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand-string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumouss <aoumouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:46:44 by habouiba          #+#    #+#             */
/*   Updated: 2022/06/26 06:46:22 by habouiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "types.h"
#include "utils.h"
#include <stdio.h>

// ""
// ''
// $

static char *ft_chardump(int c)
{
    char *str;

    str = malloc(sizeof(char) * 2);
    if (!str)
        return (NULL);
    str[0] = c;
    str[1] = '\0';
    return (str);
}

void expand(char **str, t_env_list *env)
{
    int   i;
    char *tmp;

    i = 0;
    if (!str || !*str)
        return;
    if (**str == '"')
        remove_double_quotes(str, env);
    else if (**str == '\'')
        remove_single_quotes(str);
    else
    {
        tmp = _expand(*str, env);
        free(*str);
        *str = tmp;
    }
}

void remove_double_quotes(char **s, t_env_list *env)
{
    char *tmp;

    if (**s != '"')
        return;
    tmp = _expand(*s, env);
    free(*s);
    *s = remove_last_and_first(tmp);
    free(tmp);
}

char *join_3_strings(char *s1, char *s2, char *s3)
{
    size_t len;
    char  *str;

    len = ft_strlen(s1) + ft_strlen(s3);
    if (s2)
        len += ft_strlen(s2);
    str = ft_calloc(len + 1, sizeof(char));
    if (!str)
        return (NULL);
    ft_strlcat(str, s1, len + 1);
    if (s2)
        ft_strlcat(str, s2, len + 1);
    ft_strlcat(str, s3, len + 1);
    free(s1);
    free(s3);
    return (str);
}

char *_expand(const char *s, t_env_list *env)
{
    size_t i;
    size_t j;
    char  *key;
    char  *joined;
    char  *tmp;

    i = 0;
    joined = ft_strdup(s);
    while (joined[i])
    {
        if (joined[i] != '$')
        {
            i++;
            continue;
        }
        if (!ft_isalpha(joined[i + 1]))
        {
            i++;
            continue;
        }
        j = 0;
        i++;
        while (joined[i + j] && !ft_isspace(joined[i + j]) &&
               joined[i + j] != '$' && joined[i + j] != '"')
            j++;
        key = ft_substr(joined, i, j);
        tmp =
            join_3_strings(ft_substr(joined, 0, i - 1), env_list_get(env, key),
                           ft_substr(joined, i + j, -1));
        free(joined);
        free(key);
        joined = tmp;
        i = 0;
    }
    return (joined);
}

char *remove_last_and_first(char *s)
{
    return (ft_substr(s, 1, ft_strlen(s) - 2));
}

void remove_single_quotes(char **s)
{
    char *tmp;

    if (**s != '\'')
        return;
    tmp = *s;
    *s = ft_substr(*s, 1, ft_strlen(*s) - 2);
    free(tmp);
}

void evaluate_str_and_var(t_list *cmds, t_env_list *env)
{
    t_cmd  *cmd;
    t_list *var;

    while (cmds)
    {
        cmd = cmds->content;
        expand(&cmd->cmd_name, env);
        var = cmd->args;
        while (var)
        {
            expand((char **)&var->content, env);
            var = var->next;
        }
        expand(&cmd->in, env);
        expand(&cmd->out, env);
        var = cmd->heredoc_del;
        while (var)
        {
            expand((char **)&var->content, env);
            var = var->next;
        }
        cmds = cmds->next;
    }
}
