/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:15:00 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/05/17 08:29:53 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getpath(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (i);
		i++;
	}
	return (0);
}

// int	ft_strcmp1(t_node **env, const char *d)
// {
// 	size_t	i;
// 	t_node	*tmp;

// 	tmp = *env;
// 	while (tmp)
// 	{
// 		i = 0;
// 		while (tmp->data[i] && d[i])
// 		{
// 			while  (tmp->data[i] != '+' && d[i] != '+' && tmp->data[i + 1] == '='
// 				&& d[i + 1] == '=')
// 			{
// 				//printf("data[%zu] = %c \t ptr[%zu] = %c\n", i, tmp->data[i], i,d[i]);
                
// 				return (1);
// 			}
// 			else
// 				// printf(">>>env : %c\t>>>>ptr : %c\n", s[i], d[i]);
// 				i++;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

char	*ft_get_bufcmd(char **spltcmd, char *av)
{
	int		i;
	char	*buff;

	i = 0;
	while (spltcmd[i])
	{
		buff = ft_strjoin(spltcmd[i], "/");
		buff = ft_strjoin(buff, av);
		if (access(buff, F_OK) == 0)
			return (buff);
		free(buff);
		i++;
	}
	return (NULL);
}

void	addback(t_node **head, char *ptr)
{
	t_node	*new;
	t_node	*last;

	new = malloc(sizeof(t_node));
	new->data = ptr;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

t_node	*ft_stockenvinlist(char **env)
{
	t_node	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (env[i])
	{
		addback(&tmp, env[i]);
		i++;
	}
	return (tmp);
}

int	sizell(t_node *lls)
{
	t_node	*tmp;
	int		i;

	tmp = NULL;
	tmp = lls;
	i = 0;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**ft_stockenvinptr(t_node *head)
{
	int		i;
	char	**ptr;

	i = 0;
	ptr = (char **)malloc(sizeof(char *) * sizell(head) + 1);
	while (head)
	{
		ptr[i] = head->data;
		head = head->next;
		i++;
	}
	return (ptr);
}

char	*gethompath(t_node **head)
{
	t_node	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (ft_strnstr(tmp->data, "HOME=", 5))
			return (tmp->data);
		tmp = tmp->next;
	}
	return (0);
}

void	pwdfunction(t_node **head)
{
	t_node	*tmp;
	char	*ptr;

	tmp = *head;
	while (tmp)
	{
		if (ft_strnstr(tmp->data, "PWD=", 4))
		{
			ptr = tmp->data;
			ft_putstr(ptr + 4);
		}
		tmp = tmp->next;
	}
}

// int pwdendoldpwd(t_node **head)
// {
//     char *pwd;
//     char *oldpwd;
//     t_node *tmp;
//     tmp = *head;
//     while(tmp)
//     {
//         if (ft_strnstr(tmp->data, "PWD=",4))
//         {
//             ptr = tmp->data;
//             ft_putstr_fd(ptr + 4);
//         }
//         tmp = tmp->next;
//     }
// }

void	cdfunction(t_node **head, char *ptr)
{
	char	*svptr;

	//t_node *tmp;
	if (ptr == NULL || ft_strcmp(ptr, "~", '\0') == 0)
	{
		svptr = gethompath(head);
		if (chdir(svptr + 5) == -1)
			(write(2, "chdihomererror\n", 16), exit(0));
	}
	else
	{
		if (chdir(ptr) == -1)
			(write(2, "chdirerror\n", 12), exit(0));
	}
	//pwdendoldpwd(head);
}

// int main(int ac, char **av , char **env)
// {
//     int i;
//     char **spltcmd;
//     char *bufcmd;
//     int id ;
//     int fd[2];
//     int fd1;
//     t_node *tmp;
//     char **ptr;
//     int j = 0;
//     tmp = ft_stockenvinlist(env);
//     // ptr = ft_stockenvinptr(tmp);
//     // while(ptr[j])
//     // {
//     //     printf("%s\n", ptr[j]);
//     //     j++;
//     // }
//     //  fd1 = open(av[1], O_RDONLY);
//     //  if(fd1 < 0)
//     //      (write(2, "trtrt\n", 7), exit(0));
//      i = ft_getpath(env);
//      while(*env[i] != '/')
//          *env[i]++;
//      spltcmd = ft_split(env[i], ':');
//     // if (ft_strncmp(av[1], "pwd") == 0)
//     //     pwdfunction(&tmp);
//     cdfunction(&tmp , "libft");
//     ft_echo(av);
//     //  pipe(fd);

//     //  //printf("$$$$$%s\n", bufcmd);
//     //  id = fork();
//     //  if (id == 0)
//     //  {
//     //      dup2(fd1, 0);
//     //      close(fd[0]);
//     //      dup2(fd[1], 1);
//     //      char **s =ft_split(av[2], ' ');
//     //      bufcmd = ft_get_bufcmd(spltcmd, s[0]);
//     //      int sc = execve(bufcmd, s, env);
//     //  }
//     //  if(fork() == 0)
//     //  {
//     //      //printf("#######%s\n", bufcmd);
//     //      close(fd[1]);
//     //      dup2(fd[0], 0);
//     //      char **s =ft_split(av[3], ' ');
//     //      bufcmd = ft_get_bufcmd(spltcmd, s[0]);
//     //     int sc = execve(bufcmd, s, env);
//     //     printf("------%d\n", sc);
//     //  }
//     //     close(fd[1]);
//     //     close(fd[0]);
//     //  while(wait(NULL) != -1);
// }