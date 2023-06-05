/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-yaag <del-yaag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:55:38 by markik            #+#    #+#             */
/*   Updated: 2023/06/05 13:55:50 by del-yaag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_split(char **split)
{
    int i;

    i = 0;
    while(split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

char	*if_path(char *command, char **path_splied)
{
	char	*path;
    char    *str;
	int		i;

	i = 0;
	if (!ft_strncmp(command, "./", ft_strlen("./")))
	{
		path = ft_strdup(command);
		return (path);
	}
	else if (!ft_strncmp(command, "/", ft_strlen("/")))
	{
		path = ft_strdup(command);
		return (path);
	}
	if (!path_splied)
		return (NULL);
	while (path_splied[i])
	{
        str = ft_strjoiness(path_splied[i], "/");
		path = ft_strjoin(str, command);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		i++;
	}
	if (access(path, F_OK) == -1)
		return (NULL);
	return (path);
}

size_t  if_builting(char *head)
{

	if ((head && ft_strlen(head) == ft_strlen("env")
	&& !ft_strncmp(head, "env", ft_strlen("env")))
	|| (head && ft_strlen(head) == ft_strlen("export")
	&& !ft_strncmp(head, "export", ft_strlen("export")))
	|| (head && ft_strlen(head) == ft_strlen("unset")
	&& !ft_strncmp(head, "unset", ft_strlen("unset")))
	|| ((head && ft_strlen(head) == ft_strlen("echo")
	&& !ft_strncmp(head, "echo", ft_strlen("echo"))))
	|| ((head && ft_strlen(head) == ft_strlen("cd")
	&& !ft_strncmp(head, "cd", ft_strlen("cd"))))
	|| ((head && ft_strlen(head) == ft_strlen("pwd")
	&& !ft_strncmp(head, "pwd", ft_strlen("pwd"))))
	|| ((head && ft_strlen(head) == ft_strlen("exit")
	&& !ft_strncmp(head, "exit", ft_strlen("exit")))))
		return (1);
    return (0);
}

pid_t    exec_command(t_token **token, t_envs **envs, char **command, char **path_splied, char **env, int infile_fd, int outfile_fd, int **pipe_fd)
{
    char    *path;
    pid_t   pid;
    
    path = if_path(command[0], path_splied);
	signal(SIGINT, SIG_IGN);
    pid = fork();
    if (pid == -1)
    {
		perror("fork");
        return -1;
    }
    else if(pid == 0)
    {
		signal(SIGINT, SIG_DFL);
        if (infile_fd != STDIN_FILENO)
        {
            dup2(infile_fd, 0);
            close(infile_fd);
        }
        if (outfile_fd != STDOUT_FILENO)
        {
            dup2(outfile_fd, 1); 
            close(outfile_fd);
        }
        if (pipe_fd != NULL)
        {
            int i = 0;
            while(pipe_fd[i])
            {
                close(pipe_fd[i][0]);
                close(pipe_fd[i][1]);
                i++;
            }
        }
		if (if_builting(command[0]) == 1)
		{
			builtin_func(token, envs, outfile_fd, 1);
			exit(0);
		}
        else if (execve(path, command, env) == -1)
        {
            ft_putstr_fd("Minishell: ", 2);
            ft_putstr_fd(command[0], 2);
            ft_putstr_fd(" command not found\n", 2);
            exit(1);
        }
    }
    free(path);
    return (pid);
}

int redirection_in(char *file)
{
    int fd;

    fd = open(file, O_RDONLY, 0777);
    if (fd == -1)
    {
        perror(file);
        return (fd);
    }
    return (fd);
}

int redirection_out(char *file)
{
    int fd;

    fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (fd == -1)
    {
        perror(file);
        return (fd);
    }
    return (fd);
}

int redirection_append(char *file)
{
    int fd;

    fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
    if (fd == -1)
    {
        perror(file);
        return (fd);
    }
    return (fd);
}

size_t    pipe_exist(t_token **token)
{
    t_token *head;
    size_t  counter;

    head = *token;
    counter = 0;
    while (head)
    {
        if (head->type == 7)
            counter++;
        head = head->next;
    }
    return (counter);
}

t_token    *head_next_pipe(t_token **token, size_t i)
{
    t_token *head = *token;
    size_t  count = 0;
    while(head)
    {
        if (head->type == 7)
            count++;
        if (i == count)
            return (head->next);
        head = head->next;
    }
    return (0);
}

void    pipe_executing(t_token **token, t_envs **envs, char **env, char **path)
{
    t_token	*head;
    size_t	pipe_count;
    pid_t	pid_child1;
    pid_t	pid_child2;
    pid_t	pid_child3;
    size_t	i;
    int		**pipe_fd;
    int		infile_fd;
    int		outfile_fd;
    
	i = 0;
	pipe_count = pipe_exist(token);
	infile_fd = STDIN_FILENO;
	outfile_fd = STDOUT_FILENO;
    if (!pipe_count)
        return ;
    pipe_fd = malloc(sizeof(int *) * (pipe_count + 1));
    while(i < pipe_count)
    {
        pipe_fd[i] = malloc(sizeof(int) * 2);
        pipe(pipe_fd[i]);
        i++;
    }
    pipe_fd[i] = NULL;
    pid_child1 = execute_cmd_tools(token, envs, env, path, infile_fd, pipe_fd[0][1], pipe_fd);
    i = 1;
    while(i < pipe_count)
    {
        head = head_next_pipe(token, i);
        pid_child3 = execute_cmd_tools(&head, envs, env, path, pipe_fd[(i) - 1][0], pipe_fd[i][1], pipe_fd);
        i++;
    }
    head = head_next_pipe(token, i);
    if (head == NULL)
        head = *token;
    pid_child2 = execute_cmd_tools(&head, envs, env, path, pipe_fd[(i) - 1][0], outfile_fd, pipe_fd);
    i = 0;
    while(pipe_fd[i])
    {
        close(pipe_fd[i][0]);
        close(pipe_fd[i][1]);
        i++;
    }
    waitpid(pid_child1, &status, 0);
    waitpid(pid_child2, &status, 0);
    waitpid(pid_child3, &status, 0);
	signal(SIGINT, signal_handler);
}

int    _here_doc(char *argv, t_token **token, t_envs *envs)
{
    pid_t	pid;
	char	*buffer;
	char	*stop_sign;
    int		fake_status;
    int		fd[2];

    pipe(fd);
    signal(SIGINT, SIG_IGN);
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 0;
    }
    else if (pid == 0)
    {
		stop_sign = ft_strdup(argv);
        signal(SIGINT, SIG_DFL);
        while (1)
        {
            buffer = readline("heredoc> ");
            if (buffer == NULL || (ft_strlen(buffer) == ft_strlen(stop_sign)
                && (!ft_strncmp(buffer, stop_sign, ft_strlen(stop_sign)))))
            {
                free(stop_sign);
                free(buffer);
                break ;
            }
			if ((*token) && (*token)->type == 8 && (*token)->here_exp == 0)
			{
				buffer = expand_input(envs, buffer);
				buffer = remove_character(buffer, 31);
			}
            write(fd[1], buffer, ft_strlen(buffer));
            write(fd[1], "\n", 1);
            free(buffer);
        }
        close(fd[0]);
        close(fd[1]);
        exit(0);
    }
    close(fd[1]);
    waitpid(pid, &fake_status, 0);
    signal(SIGINT, signal_handler);
    if (fake_status == 2)
        return (-1);
    return (fd[0]);
}

pid_t    execute_cmd_tools(t_token **token, t_envs **envs, char **env, char **path, int infile_fd, int outfile_fd, int **pipe_fd)
{
    t_token	*head;
	t_token	*tmp;
    pid_t	pid;
	char	*semi_command;
    char	**command;
	int		here_fd;

	command = NULL;
	semi_command = NULL;
    head = *token;
    while(head)
    {
        if (head->type == 3)
        {
            head = head->next;
            here_fd = _here_doc(head->string, &head, *envs);
            if (here_fd == -1)
                return -1;
            if (head->next || tmp->type < 2)
				infile_fd = here_fd;
        }
        else if (head->type == 5)
        {
            head = head->next;
            infile_fd = redirection_in(head->string);
            if (infile_fd == -1)
                return -1;
			if (!head->next)
				if (!tmp || tmp->type >= 2)
					return -1;
        }
        else if (head->type == 6)
        {
            head = head->next;
            outfile_fd = redirection_out(head->string);
            if(outfile_fd == -1)
                return -1;
        }
        else if (head->type == 4)
        {
            head = head->next;
            outfile_fd = redirection_append(head->string);
            if (outfile_fd == -1)
                return -1;
        }
        else if (head->type == 7)
            break ;
        else
        {
            if (!semi_command)
                semi_command = ft_strdup(head->string);
            else
            {
                char *str = ft_strjoin(semi_command, " ");
                semi_command = ft_strjoin(str, head->string);
            }
        }
		tmp = head;
        head = head->next;
    }
    if (!semi_command)
        return -1;
    command = ft_split(semi_command, ' ');
    free(semi_command);
    if (if_builting(command[0]) == 1 && pipe_fd == NULL)
    {
		builtin_func(token, envs, outfile_fd, 0);
		free_split(command);
		return -1;	
    }
    pid = exec_command(token, envs, command, path, env, infile_fd, outfile_fd, pipe_fd);
    free_split(command);
    return (pid);
}

void    execute_cmd(t_token **token, t_envs **envs, char **env)
{
    char    **path;
    pid_t   pid;

    path = ft_split(ft_getenv(*envs, "PATH"), ':');
    if (pipe_exist(token))
        pipe_executing(token, envs, env, path);
    else
    {
        pid = execute_cmd_tools(token, envs, env, path, STDIN_FILENO, STDOUT_FILENO, NULL);
        waitpid(pid, &status, 0);
		signal(SIGINT, signal_handler);
    }
	if (path)
    	free_split(path);
}
