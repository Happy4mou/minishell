/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 08:38:44 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/05/16 09:06:17 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2, char c)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	i = 0;
	s = (unsigned char *)s1;
	d = (unsigned char *)s2;
	while (s[i] != c && d[i] != c)
	{
		if (s[i] != d[i])
			return (s[i] - d[i]);
		i++;
	}
	return (0);
}

