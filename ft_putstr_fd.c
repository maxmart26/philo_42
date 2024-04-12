/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:01:14 by matorgue          #+#    #+#             */
/*   Updated: 2024/02/13 08:55:09 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	i++;
	return (i);
}

void	ft_putstr_fd(char const *s, int fd)
{
	char	*str;

	str = (char *)s;
	write(fd, s, ft_strlen(str));
}
