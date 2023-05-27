/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: markik <markik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:43:13 by del-yaag          #+#    #+#             */
/*   Updated: 2023/05/24 14:55:23 by markik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	*ft_calloc(size_t number, size_t size)
{
	void	*p;
	size_t	i;
	size_t	j;

	j = 0;
	i = number * size;
	if ((number && (i / number) != size) || (size && (i / size) != number))
		return (NULL);
	p = malloc(i);
	if (!p)
		return (0);
	while (i < j)
	{
		((char *)p)[j] = '\0';
		j++;
	}
	return (p);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	*ft_cpy(char *p, char const *s2, unsigned int start, size_t l)
{
	size_t	i;

	i = 0;
	while (i < l)
	{
		p[i] = s2[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	x;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (start <= ft_strlen(s))
	{
		x = ft_strlen(s) - start;
		if (len > x)
			len = x;
		p = malloc(sizeof(char) * len + 1);
		if (!p)
			return (0);
		ft_cpy(p, s, start, len);
	}
	else
		p = (char *)ft_calloc(1, 1);
	return (p);
}
