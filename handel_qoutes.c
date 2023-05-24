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

    if (!src)
        return (0);
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
    int count = 0;

    (*i)++;
    start = *i;
    while (input[*i] && input[*i] != 39)
    {
        if (ft_isseparators(input[*i]))
        {
            perror(input);
            return (-1);
        }
        (*i)++;
    }
    if (input[*i] != 39)
    {
        printf("Syntax erorr\n");
        flag = 0;
        return (-1);
    }
    end = *i - 1;
    (*i)++;
    if(flag == 1)
    {
        head = *token;
        while(head && head->next)
            head = head->next;
        str = ft_strndup(input, start, end);
        head->string = ft_strjoin(head->string, str);
        free(str);
    }
    else if (flag == 2)
    {
        while(input[*i] && input[*i] == 39)
        {
            count++;
            (*i)++;
        }
        if (count % 2 == 0)
        {
            head = *token;
            while(head && head->next)
                head = head->next;
        }
        else
        {
            (*i)--;
            flag = 3;
            if (single_qoutes(token, input, i) == -1)
                return (-1);
        }
    }
    else if (flag == 3)
    {
        head = *token;
        while(head && head->next)
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
    if (input[*i] == 39 && input[*i + 1] != 39)
        flag = 1;
    else if (input[*i] == 39 && input[*i + 1] == 39)
        flag = 2;
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
        head = *token;
        while(head && head->next && head->next->next)
            head = head->next;
        if(!head || !head->next)
            return 0;
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
    int count = 0;

    (*i)++;
    start = *i;
    while (input[*i] && input[*i] != 34)
    {
        if (ft_isseparators(input[*i]))
        {
            perror(input);
            return (-1);
        }
        (*i)++;
    }
    if (input[*i] != 34)
    {
        printf("Syntax erorr\n");
        flag = 0;
        return (-1);
    }
    end = *i - 1;
    (*i)++;
    if(flag == 1)
    {
        head = *token;
        while(head && head->next)
            head = head->next;
        str = ft_strndup(input, start, end);
        head->string = ft_strjoin(head->string, str);
        free(str);
    }
    else if (flag == 2)
    {
        while(input[*i] && input[*i] == 34)
        {
            count++;
            (*i)++;
        }
        if (count % 2 == 0)
        {
            head = *token;
            while(head && head->next)
                head = head->next;
        }
        else
        {
            (*i)--;
            flag = 3;
            if (double_qoutes(token, input, i) == -1)
                return (-1);
        }
    }
    else if (flag == 3)
    {
        head = *token;
        while(head && head->next)
            head = head->next;
        str = ft_strndup(input, start, end);
        head->string = ft_strjoin(head->string, str);
        free(str);
    }
    else
    {
        add_node(token);
        head = *token;
        while(head && head->next)
            head = head->next;
        head->string = ft_strndup(input, start, end);
        head->next = NULL;
    }
    if (input[*i] == 34 && input[*i + 1] != 34)
        flag = 1;
    else if (input[*i] == 34 && input[*i + 1] == 34)
        flag = 2;
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
        if(single_qoutes(token, input, i) == -1)
            return (-1);
        head = *token;
        while(head && head->next && head->next->next)
            head = head->next;
        if(!head || !head->next)
            return 0;
        str = ft_strdup(head->next->string);
        head->string = ft_strjoin(head->string, str);
        head->next = NULL;
        free(head->next);
        free(str);
    }
    return (0);
}