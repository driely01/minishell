# minishell
<img width="400" alt="Screen Shot 2023-09-22 at 4 42 51 PM" src="https://github.com/driely01/minishell/assets/41493879/ca9facdf-b4fb-4b6b-a0b2-1651ebe5020f">
<!-- <img width="226" alt="Screen Shot 2023-09-22 at 4 44 18 PM" src="https://github.com/driely01/minishell/assets/41493879/8d407699-00fa-43ce-a4a6-3978fefa8d9f"> -->

> The project subject:

```
https://cdn.intra.42.fr/pdf/pdf/93145/en.subject.pdf
```

### about the project
First you need to study the behavior of the actual `bash` and see how it work under the hood, then you need to learn about the following system calls `access` `open` `read` `close` `fork` `wait & waitpid` `kill` `exit` `getcwd` `chdir` `execve` `dup & dup2` `pipe` `perror`, and now the main idea of this project is to execute the cmds with pipes or without and execute the builtin commands like `cd` `pwd` `echo` `export` `unset` `exit` `env` and execute the heredoc the same like in bash. But before to execute all this you should first parce the line who enter as a input to see if it doesn't contain any syntax errors or invalid input.

**Resources**
1. Bash: [Check it](https://www.gnu.org/software/bash/manual/bash.html)
2. open and other system calls: [Check it](https://man.freebsd.org/cgi/man.cgi?query=open&apropos=0&sektion=2&manpath=FreeBSD+13.2-RELEASE+and+Ports&arch=default&format=html)
<!--
## Parsing Part
<img width="1400" alt="Screen Shot 2023-06-14 at 10 54 08 AM" src="https://github.com/driely01/minishell/assets/41493879/e9711cc1-0906-4be4-aec7-ca4e2053da2d">
-->
## how tokenizer work
<img width="2481" alt="Screen Shot 2023-09-22 at 4 33 52 PM" src="https://github.com/driely01/minishell/assets/41493879/8725a07a-16e8-4409-be7f-b2953868a53a">

<!--
## Execution Part
```
https://www.figma.com/community/file/1269608787526815167/minishell-execution-part
```
<img width="1454" alt="Screen Shot 2023-09-22 at 4 26 15 PM" src="https://github.com/driely01/minishell/assets/41493879/af9f7284-c5bd-4a09-8f75-3c40a0f99573">
-->
