# minishell
<img width="541" alt="Screen Shot 2023-08-06 at 4 17 59 PM" src="https://github.com/driely01/minishell/assets/41493879/a001c046-9345-49a8-a683-f72a1b8f77d7">

> The project subject:

```
https://cdn.intra.42.fr/pdf/pdf/93145/en.subject.pdf
```

### about the project
First you need to study the behavior of the actual `bash` and see how it work under the hood, then you need to learn about the following system calls `access` `open` `read` `close` `fork` `wait & waitpid` `kill` `exit` `getcwd` `chdir` `execve` `dup & dup2` `pipe` `perror`, and now the main idea of this project is to execute the cmds with pipes or without and execute the builtin commands like `cd` `pwd` `echo` `export` `unset` `exit` `env` and execute the heredoc the same like in bash. But before to execute all this you should first parce the line who enter as a input to see if it doesn't contain any syntax errors or invalid input.

**Resources**
1. Bash: [Check it](https://www.gnu.org/software/bash/manual/bash.html)
2. open and other system calls: [Check it](https://man.freebsd.org/cgi/man.cgi?query=open&apropos=0&sektion=2&manpath=FreeBSD+13.2-RELEASE+and+Ports&arch=default&format=html)

## Parsing Part
<img width="1400" alt="Screen Shot 2023-06-14 at 10 54 08 AM" src="https://github.com/driely01/minishell/assets/41493879/f0df2261-a30b-4a02-bce9-c001dc569e3b">

## how tokenizer work
<img width="2512" alt="Screen Shot 2023-08-06 at 12 02 21 PM" src="https://github.com/driely01/minishell/assets/41493879/8871ac57-8ceb-4f38-a306-23896f621e7c">

## Execution Part
```
https://www.figma.com/community/file/1269608787526815167/minishell-execution-part
```
<img width="1169" alt="Screen Shot 2023-08-05 at 11 45 37 AM" src="https://github.com/driely01/minishell/assets/41493879/85bd6eb5-3ea8-4232-a2e8-7b397f732107">
