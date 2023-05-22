#include "minishell.h"

char	*ft_strcpy(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	char		*dest;
	size_t		src_size;

	src_size = ft_strlen(src);
	dest = malloc(sizeof (char) * (src_size + 1));
	if (dest == NULL)
		return (NULL);
	dest = ft_strcpy(dest, src);
	return (dest);
}

int    single_qoutes(t_token **token, char *input, size_t *i)
{
    t_token *head;
    char    *str;
    static  int flag;
    int start;
    int end;


    (*i)++;
    start = *i;
    while (input[*i] && input[*i] != 39)
        (*i)++;
    if (input[*i] != 39)
    {
        printf("Syntax erorr\n");
        return (-1);
    }
    end = *i - 1;
    (*i)++;
    if(flag == 1)
    {
        head = *token;
        while(head && head->next && head->next->next)
            head = head->next;
        str = ft_strndup(input, start, end);
        head->string = ft_strjoin(head->string, str);
        free(str);
    }
    else{
        add_node(token);
        head = *token;
        while(head && head->next)
            head = head->next;
        head->string = ft_strndup(input, start, end);
        head->next = NULL;
    }
    if (input[*i] == 39)
        flag = 1;
    else
        flag = 0;
    if (ft_isalnum(input[*i]))
    {
        if (handle_char(token, input, i) == -1)
            return (-1);
        str = ft_strdup(head->next->string);
        head->string = ft_strjoin(head->string, str);
        head->next = NULL;
        free(head->next);
        free(str);
    }
    else if(input[*i] == 34)
    {
        if (double_qoutes(token, input, i) == -1)
            return (-1);
        str = ft_strdup(head->next->string);
        head->string = ft_strjoin(head->string, str);
        head->next = NULL;
        free(head->next);
        free(str);
    }
    return (0);
}

int    double_qoutes(t_token **token, char *input, size_t *i)
{
    t_token *head;
    char    *str;
    static  int flag;
    int start;
    int end;


    (*i)++;
    start = *i;
    while (input[*i] && input[*i] != 34)
        (*i)++;
    if (input[*i] != 34)
    {
        printf("Syntax erorr\n");
        return (-1);
    }
    end = *i - 1;
    (*i)++;
    if(flag == 1)
    {
        head = *token;
        while(head && head->next && head->next->next)
            head = head->next;
        str = ft_strndup(input, start, end);
        head->string = ft_strjoin(head->string, str);
        free(str);
    }
    else{
        add_node(token);
        head = *token;
        while(head && head->next)
            head = head->next;
        head->string = ft_strndup(input, start, end);
        head->next = NULL;
    }
    if (input[*i] == 34)
        flag = 1;
    else
        flag = 0;
    if (ft_isalnum(input[*i]))
    {
        if (handle_char(token, input, i) == -1)
            return (-1);
        str = ft_strdup(head->next->string);
        head->string = ft_strjoin(head->string, str);
        head->next = NULL;
        free(head->next);
        free(str);
    }
    else if(input[*i] == 39)
    {
        if (single_qoutes(token, input, i) == -1)
            return (-1);
        str = ft_strdup(head->next->string);
        head->string = ft_strjoin(head->string, str);
        head->next = NULL;
        free(head->next);
        free(str);
    }
    return (0);
}