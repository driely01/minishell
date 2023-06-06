/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:03:14 by del-yaag          #+#    #+#             */
/*   Updated: 2023/06/06 18:10:49 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_checklast(char const *s, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s) - 1;
	while (set[i])
	{
		if (j > 0 && s[j] == set[i])
		{
			j--;
			i = 0;
		}
		else
			i++;
	}
	if (j < 0)
		return (0);
	return (j);
}

static size_t	ft_checkbeg(char const *s, char const *set)
{
	size_t	i;
	size_t	z;

	i = 0;
	z = 0;
	while (set[i])
	{
		if (s[z] == set[i])
		{
			z++;
			i = 0;
		}
		else
			i++;
	}
	return (z);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	end;
	size_t	start;
	char	*p;

	if (s1 == 0 || set == 0)
		return (0);
	if (s1[0] == '\0')
		return (0);
	i = 0;
	start = ft_checkbeg(s1, set);
	end = ft_checklast(s1, set);
	if (start > end)
		return (0);
	if (start > end)
		return ((char *)ft_calloc(1, 1));
	p = malloc(sizeof(char) * ((end - start) + 2));
	if (!p)
		return (0);
	while (start <= end)
		p[i++] = s1[start++];
	p[i] = '\0';
	return (p);
}
