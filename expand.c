#include "minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

char    *replaceWord(char *line, char *word, char *change_word, int start, int end)
{
    int len = (ft_strlen(line) - (ft_strlen(word) + 1) + ft_strlen(change_word) + 1);
    char *str = malloc(sizeof(char) * len);
    int    i;
    int     j;
    int     a;

    i = 0;
    a = 0;
    j = 0;
    while(i <= ft_strlen(line))
    {
        if (i == start)
        {
            a = i - 1;
            while(change_word[j])
            {
                str[a] = change_word[j];
                a++;
                j++;
            }
            i = end + 1;
        }
        else
        {
            if (a > 0)
            {
                str[a] = line[i];
                a++;
                i++;
            }
            else
            {
                str[i] = line[i];
                i++;
            }
        }
    }
    free(line);
    return (str);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (str1[i] != str2[i] || str1[i] == 0 || str2[i] == 0)
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

char *ft_strchr(char **env, char *search)
{
    size_t i;

    i = 0;
    if (!search)
        return 0;
    while(env[i])
    {
        if (!strncmp(env[i], search, ft_strlen(search)))
            return(env[i]);
        i++;
    }
    return 0;
}

int is_alpha(char c)
{
    if ((c >= 'a' && c <= 'z')
	|| (c >= 'A' && c <= 'Z'))
		return (1);
    return (0);
}

int	ft_isalnum_expand(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int valid_expand(char c)
{
    if (c == '_' || is_alpha(c))
        return (1);
    return (0);
}

char *change_line_input(char **env, char *input, size_t *i ,size_t *count)
{
    char *str;
    char *tab;
    size_t start;
    size_t  end;

    (*count)++;
    while(input[*i] && input[*i] == '$')
    {
        (*count)++;
        (*i)++;
    }
    //$$ ZAWJI:
    if ((*count) % 2 ==  1)
        return (input);
    start = *i;
    while(input[*i] && valid_expand(input[*i]))
    {
        //treating conditions
        if (input[*i] == '_' && !ft_isalnum_expand(input[*i + 1]))
        {
            return input;
        }
        (*i)++;
    }
    if (start == *i)
        return input;
    end = *i - 1;
    tab = ft_strndup(input, start, end);
    str = getenv(ft_strchr(env, tab));
    if (!str)
        return NULL;
    input = replaceWord(input, tab ,str, start, end);
    free(tab);
    return input;
}

char *expand_start_end(char **env, char *input)
{
    char *tab;
    size_t i;
    size_t count;

    i = 0;
    while (i < ft_strlen(input))
    {
        count = 0;
        if (input[i] == '$')
        {
            tab = change_line_input(env, input, &i , &count);
            if (!tab)
                return NULL;
            input = ft_strdup(tab);
            free(tab);
        }
        i++;
    }
    return (input);
}

char    *expand_input(char **env, char *input)
{
    char *tab;

    tab = expand_start_end(env, input);
    if (!tab)
        return NULL;
    return (tab);
}