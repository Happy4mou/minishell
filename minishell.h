/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:40:41 by rchmouk           #+#    #+#             */
/*   Updated: 2023/05/16 09:07:15 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_list
{
	char			**infile;
	char			**outfile;
	char			**apend;
	char			**heredoc;
	char			**arg;
	struct s_list	*next;
}					t_parc;

typedef struct s_list2
{
	char			*var;
	char			*val;
	struct s_list2	*next;
}					t_env;

typedef struct node
{
	char			*data;
	struct node		*next;
}					t_node;

int					ft_count(char *str, char c);
char				*ft_put(char *str, int x, char c);
t_parc				*ft_lst_last(t_parc *lst);
void				ft_lst_add_back(t_parc *lst, t_parc *new);
t_parc				*ft_lst_new(char *arg, int index);
char				**split_pro_max(int *tab, char *str);
char				*ft_expand(char *str, t_env *env);
char				**split_pro_max(int *tab, char *str);
void				ft_lst_add_back2(t_env *lst, t_env *new);
void				ft_echo(t_parc *head);
void				ft_checkcmd(t_parc *head, t_node **env);
void				ft_write_in_fd(char **str, int fd);
void				cdfunction(t_node **head, char *ptr);
void				pwdfunction(t_node **head);
char				*gethompath(t_node **head);
char				**ft_stockenvinptr(t_node *head);
int					sizell(t_node *lls);
t_node				*ft_stockenvinlist(char **env);
void				addback(t_node **head, char *ptr);
char				*ft_get_bufcmd(char **spltcmd, char *av);
int					ft_getpath(char **env);
void				ft_export(t_node **env, t_parc *head);
t_node				*ft_stockenvinexport(t_node **env);
void				ft_printexport(t_node **env);
void				print_line_exp(char *s);
int					ft_check_cmd_exp(t_node **env, char *ptr);
int					ft_check_value_in_exp(t_node **env, char *ptr);
void				ft_change_value_in_exp(t_node **env, char *ptr);
void				ft_remove_node(t_node **env, char *ptr);
void				cdfunction(t_node **head, char *ptr);
void				pwdfunction(t_node **head);
char				*gethompath(t_node **head);
int					ft_getpath(char **env);
char				*ft_get_bufcmd(char **spltcmd, char *av);
t_node				*ft_stockenvinlist(char **env);
int					sizell(t_node *lls);
char				**ft_stockenvinptr(t_node *head);
int	ft_strcmp1(t_node **env, const char *d);

#endif
