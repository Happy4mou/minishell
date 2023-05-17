/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:16:55 by mmajdoub          #+#    #+#             */
/*   Updated: 2022/11/01 20:59:23 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long		rst;
	int					s;

	i = 0;
	s = 1;
	rst = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rst = rst * 10 + str[i] - 48;
		i++;
	}
	if (rst >= 9223372036854775807 && s == 1)
		return (-1);
	else if (rst > 9223372036854775807 && s == -1)
		return (0);
	return (rst * s);
}
