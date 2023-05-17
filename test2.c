
#include "libft/libft.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	int			data;
	struct node	*next;
}				t_node;

void	addback(t_node **head, int ptr)
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

void	ft_remove_node(t_node **env, int ptr)
{
	t_node	*tmp;
	t_node	*prv;

	tmp = NULL;
	prv = *env;
	if ((*env)->data == ptr)
	{
		tmp = *env;
		*env = (*env)->next;
		//free(tmp);
		return ;
	}
	while (prv->next != NULL)
	{ //printf(">> : %d\n",ft_strcmp1(prv->data , ptr,'=') );
		if (prv->data == ptr)
		{
			
			tmp->next = prv->next;
            //free(prv->data);
			free(prv);
			break ;
		}
        tmp = prv;
		prv = prv->next;
	}
    		if (prv->data == ptr)
		{
			
			tmp->next = NULL;
            //free(prv->data);
			free(prv);
			return;
		}
	if (tmp == NULL)
		return ;
}

int	main(void)
{
	t_node *tmp = NULL;
	addback(&tmp, 2);
	addback(&tmp, 3);
	addback(&tmp, 4);
	addback(&tmp, 5);
	ft_remove_node(&tmp, 5);

	t_node *ptr = tmp;
	while (ptr)
	{
		printf(">>>> tmp : %d\n", ptr->data);
		ptr = ptr->next;
	}
}