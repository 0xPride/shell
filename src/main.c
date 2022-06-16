/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumouss <aoumouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:51:26 by habouiba          #+#    #+#             */
/*   Updated: 2022/06/16 08:50:46 by habouiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"

// const char *__asan_default_options() { return "detect_leaks=0"; }

void print_cmds(t_list *cmds);
void printc(t_list *cmds);

// int main(int ac, char **av, char **env) {

//   ac = (int)ac;
//   av = (char **)av;
//   env = (char **)env;
//   t_env_list lst;

//   t_list *commands = generator();
//   print_cmds(commands);
//   executer(commands, env);
//   return (g_exit_code);
// }

int main(int ac, char **av, char **env) {

  ac = (int)ac;
  av = (char **)av;
  env = (char **)env;
  t_env_list lst;

  // t_list *commands = generator();
  // print_cmds(commands);
  // executer(commands, env);
  t_list *cmds = parser("<tmp cat -n hello ; ls . > out", NULL);
  printc(cmds);
  return (g_exit_code);
}

void print_cmds(t_list *cmds) {
  while (cmds) {
    t_cmd *cmd = (t_cmd *)cmds->content;
    printf("%s ", (char *)cmd->cmd_name);
    t_list *args = cmd->args;
    while (args->next) {
      printf("%s ", (char *)args->next->content);
      args = args->next;
    }
    if (cmds->next)
      printf(" | ");
    cmds = cmds->next;
  }
  printf("\n");
}

void printc(t_list *cmds) {
  char *a[] = {"NONE", "AND", "OR", "SEMICOLON", "PIPE"};
  char *b[] = {"NIL", "SINGLE", "DOUBLE", "HEREDOC"};
  for (t_list *node = cmds; node; node = node->next) {
    t_cmd *cmd = node->content;
    printf("cmd_name: %s\n", cmd->cmd_name);
    printf("args: ");
    for (t_list *arg = cmd->args; arg; arg = arg->next) {
      printf("%s ", (char *)arg->content);
    }
    printf("\n");
    printf("in: %s type: %s\n", cmd->in, b[cmd->in_redir]);
    printf("out: %s type: %s\n", cmd->out, b[cmd->out_redir]);
    printf("left: %s\n", a[cmd->left_delimiter]);
    printf("right: %s\n", a[cmd->right_delimiter]);
    printf("heredoc %s\n", cmd->heredoc_del);
  }
}
