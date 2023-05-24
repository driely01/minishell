#include "minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

char *replaceWord(char *line, char *word, char *new_word)
{
    char *line_part;
    char *line_part_1;

    size_t i = ft_strlen(line) - 1;
    line_part = ft_strdup(strstr(line, word));
    if(!line_part)
        return 0;
    size_t j = ft_strlen(line_part);
    printf("line %s\n", line);
    printf("world: %s\n", line_part);
        printf("world: %s\n", new_word);
        printf("i is %ld\n", i);
                printf("j is %ld\n", j);
    if (i == j)
    {
        free(line);
        line = ft_strdup(new_word);
        return(line);
    }
    else
        exit(0);
    //line_part_1 = ft_strndup(line, 0, i - j);
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
        return (NULL);
    start = *i;
    while(input[*i] && valid_expand(input[*i]))
    {
        //treating conditions
        if (input[*i] == '_' && !ft_isalnum_expand(input[*i + 1]))
        {
            return NULL;
        }
        (*i)++;
    }
    if (start == *i)
        return NULL;
    end = *i - 1;
    tab = ft_strndup(input, start, end);
    str = getenv(ft_strchr(env, tab));
    if (!str)
        return NULL;
    replaceWord(input, tab, str);
    free(tab);
    return input;
}

char *expand_start_end(char **env, char *input)
{
    char *tab;
    size_t i;
    size_t count;

    i = 0;
    int j = ft_strlen(input);
    while (i < j)
    {
        count = 0;
        if (input[i] == '$')
        {
            tab = change_line_input(env, input, &i , &count);
            if (!tab)
                return 0;
        }
        i++;
    }
    return (0);
}

void    expand_input(char **env, char *input)
{
    char *tab;

    tab = expand_start_end(env, input);
    if (!tab)
        return ;
    // printf("string %s\n", tab);
    free(tab);
}