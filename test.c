/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:00:26 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/05/17 20:59:10 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write_in_fd(char **str, int fd)
{
	int	i;

	i = 1;
	if (str == NULL)
		return ;
	while (str[i])
	{
		ft_putstr_fd(str[i], fd);
		i++;
	}
}

t_node	*ft_stockenvinexport(t_node **env)
{
	t_node	*tmp;
	t_node	*exp;

	tmp = *env;
	exp = NULL;
	while (tmp)
	{
		addback(&exp, tmp->data);
		tmp = tmp->next;
	}
	return (exp);
}

void	print_line_exp(char *s)
{
	int	i;

	i = 0;
	write(1, "declare -x ", 11);
	while (s[i] != '=')
	{
		if (s[i] == '\0')
			return ;
		write(1, &s[i], 1);
		i++;
	}
	write(1, "=", 1);
	write(1, "\"", 1);
	i++;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\"", 1);
}

void	ft_printexport(t_node **env)
{
	t_node	*tmp;

	tmp = *env;
	while (tmp)
	{
		print_line_exp(tmp->data);
		printf("\n");
		tmp = tmp->next;
	}
}

int	ft_check_cmd_exp(t_node **env, char *ptr)
{
	t_node	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->data, ptr, '=') != 0  && ft_strcmp(tmp->data, ptr, '+') != 0)
			tmp = tmp->next;
		else
			return (1);
	}
	return (0);
}

void	ft_change_value_in_exp(t_node **env, char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != '=')
	{
		if (ptr[i] == '\0')
			break ;
		i++;
	}
	i++;
	while (ptr[i])
	{
		(*env)->data[i] = ptr[i];
		i++;
	}
}

void	ft_remove_node(t_node **env, char *ptr)
{
	t_node	*tmp;
	t_node	*prv;

	tmp = *env;
	prv = *env;
	if (ft_strcmp((*env)->data, ptr, '=') == 0)
	{
		tmp = *env;
		*env = (*env)->next;
		//free(tmp);
		return ;
	}
	while (prv->next != NULL)
	{
		if (ft_strcmp(prv->data, ptr, '=') == 0)
		{
			tmp->next = prv->next;
			break ;
		}
		tmp = prv;
		prv = prv->next;
	}
	if (ft_strcmp(prv->data, ptr, '=') == 0)
	{
		tmp->next = NULL;
		//free(prv->data);
		free(prv);
		return ;
	}
	if (tmp == NULL)
		return ;
}

// int	ft_check_value_in_exp(t_node **env, char *ptr)
// {
// 	int		i;
// 	t_node	*tmp;

// 	tmp = *env;
// 	while (tmp)
// 	{
// 		i = 0;
// 		while (ptr[i] != '=')
// 		{

// 			if (ptr[i] == '\0')
// 				break ;
// 			i++;
// 		}
//         i++;
// 		while (tmp->data[i] && ptr[i])
// 		{
// 			if (ft_strcmp(&tmp->data[i], &ptr[i], '\0') == 0)
// 				i++;
// 			else
// 				return (1);make re
// 		}
// 	}
// 	return (0);
// }

int	ft_check_plus(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '+' && ptr[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_add_in_exp(t_node **env, char *ptr)
{
	int	i;

	i = 0;
    t_node *tmp = *env;
	while (ptr[i])
	{
		if (ptr[i] == '+' && ptr[i + 1] == '=')
			break ;
		i++;
	}
    i  += 2;
	//printf("--->%d\n", i);
		if (ft_strcmp(tmp->data, ptr, '+') == 0)
		{
            tmp->data = ft_strjoin(tmp->data,"=");
            tmp->data = ft_strjoin(tmp->data,&ptr[i]);
			return ;
		}
	while (tmp)
	{
		if (ft_strcmp(tmp->data, ptr, '+') == 0)
		{
			tmp->data = ft_strjoin(tmp->data,"=");
			tmp->data = ft_strjoin(tmp->data,&ptr[i]);
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_export(t_node **env, t_parc *head)
{
	t_node	*exp;
	int		i;

	exp = (*env);
	i = 1;
	// exp = ft_stockenvinexport(env);
	// if (head->arg[1] == NULL)
	// {
	// 	ft_printexport(env);
	// 	return ;
	// }
	// else
	// {
	while (head->arg[i])
	{
		//printf("---> : %d\n", ft_check_plus(head->arg[i]));
		//printf("---> : %d\n", ft_strcmp1(env, head->arg[i]));
		//printf("---> arg[%d] : %s\t", i, head->arg[i]);
		//printf(">>>>> : %s\n",head->arg[i]);
	
		if (ft_check_cmd_exp(env, head->arg[i]) == 0)
            addback(env, head->arg[i]);
			
    	else if (ft_check_plus(head->arg[i]) == 1)
			ft_add_in_exp(env, head->arg[i]);
		else
		{
				ft_remove_node(env, head->arg[i]);
				addback(env, head->arg[i]);
		}
		//ft_change_value_in_exp(env, head->arg[i]);
		i++;
	}
	//ft_printexport(env);
	//}
	while (exp)
	{
		printf("%s\n", exp->data);
		exp = exp->next;
	}
}

void	ft_checkcmd(t_parc *head, t_node **env)
{
	t_node	*tmp;

	tmp = *env;
	if (ft_strncmp(head->arg[0], "echo", 5) == 0)
		ft_echo(head);
	else if (ft_strncmp(head->arg[0], "export", 7) == 0)
		ft_export(env, head);
	else if (ft_strncmp(head->arg[0], "unset", 6) == 0)
		ft_remove_node(env, head->arg[1]);
	else if (ft_strncmp(head->arg[0], "cd", 3) == 0)
		cdfunction(env, head->arg[1]);
	else if (ft_strncmp(head->arg[0], "pwd", 4) == 0)
		pwdfunction(env);
    //else if  (ft_strncmp(head->arg[0], "env", 4) == 0)
    
	// while (tmp)
	// {
	// 	printf("%s\n", tmp->data);
	// 	tmp = tmp->next;
	// }
}
void	ft_echo(t_parc *head)
{
	int	i;
	int	fd;

	i = 0;
	if (head->outfile[i] == NULL)
	{
		ft_write_in_fd(head->arg, 1);
		printf("\n");
	}
	else
	{
		while (head->outfile[i] != NULL)
		{
			fd = open(head->outfile[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			i++;
		}
		ft_write_in_fd(head->arg, fd);
	}
}
