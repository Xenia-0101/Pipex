
Pipex
===

Allowed Functions
---

### access

Checks to see if a file or directory specified by *path* can be accessed or has specific permissions <br>

~~~
int access(const char *path, int amode);
~~~

#### Params: <br>
- **path:** specifies the file or directory we want to check <br>
- **amode:** specifies what permissions we are looking for, possible options are F_OK (checks for file existence) or a bitwise OR combination of R_OK, W_OK, X_OK (read, write, execute permissions). <br>
#### Return: <br>
- **0** if file exists or permissions are granted, else **-1**

---

### dup2

Copies *fd1* into *fd2*, *fd2* then refers to the same file as *fd1*. <br>
File previously reffered to by *fd2* is closed.

~~~
int dup2(int fd1, int fd2);
~~~

#### Return: <br>
- *fd2* on sucess, else *-1*

#### Notes: <br>
- 0 < *fd2* < OPEN_MAX
- if *fd1* == *fd2*, *fd2* is not closed
- if *fd2* does not exist, it will be created
- if file refferenced by *fd1* does not have required permissions, dup2 fails
dup2 can be used to replace any open file descriptor, including the reserved values 0, 1 and 2 (stdin, stdout, stderr), which can be useful for redirecting output of one fd to another

~~~
int main(void)
{
	int fd;

	// test access
	printf("Access: %d\n", access("z_write.txt", F_OK));
	printf("Read: %d\n", access("z_write.txt", R_OK));
	printf("Write: %d\n", access("z_write.txt", W_OK));
	printf("Read or Write: %d\n", access("z_write.txt", R_OK | W_OK));

	if (!access("z_write.txt", F_OK) && !access("z_write.txt", W_OK))
	{
		fd = open("z_write.txt", O_WRONLY);
		// redirect fd to stdout
		dup2(fd, 1);
		close(fd);
		// print to stdout
		write(1, "Redirecting data\n", 18);
	}
	else
		printf("File does not exist or has not write permission.\n");
	return (0);
}
~~~

---

### execve

Executes a program from a file by replacing the current process img with a new one.

~~~
int execve(const char *path, char *const argv[], char *const envp[]);
~~~

#### params
- **path:** filepath of the file containing image of a process to be run
- **argv:** arguents to be passed to the new program
- **envp:** environment variables

~~~
// test execve
char *argv[5] = {"ls", "includes", ".", "-la", NULL};

execve("/bin/ls", argv, NULL);

printf("This line will not be executed\n");

~~~

---

### fork

Creates a new process, the **child process**, which runs concurrently with the original, **parent**, process. After the child process is created, the instructions following fork() call are executed .

~~~
pid_t fork(void);
~~~

#### return:
- on success:
	- PID of the child in the parent process
	- 0 in the child process
- on failure:
	- -1 in the parent
	- no child is created
	- errno is set

~~~
int pid = fork();
printf("pid: %d\n", pid);

if (pid == -1)
	return (1);
if (pid == 0)
	printf("In the child process\n");
else
	printf("In the parent process\n");
~~~

---

### pipe

A unidirectional connection between two processes used for inter-process communication.

~~~
int pipe(int fd[2]);
~~~

#### params:
- **fd[2]:** an array of two filedescriptors, *fd[0]* - read end, *fd[1]* - write end

~~~
void main(void)
{
	// testing pipes
	int fd[2];
	int pid;
	char buff[17];

	// create a pipe - will be inherited by child
	if (pipe(fd) == -1)
	{
		perror("pipe fail");
		exit(1);
	}

	// fork the process
	pid = fork();
	if (pid == -1)
	{
		perror("fork fail");
		exit(1);
	}

	// in the child - read from the pipe and write to stdout
	if (pid == 0)
	{
		printf("Child process\n");
		close(fd[1]);
		read(fd[0], buff, 17);
		write(1, buff, 17);
		close(fd[0]);
	}
	// in the parent - use write end of the pipe to send a msg
	if (pid > 0)
	{
		printf("Parent process\n");
		// close(fd[0]);
		write(fd[1], "msg from parent\n", 17);
		// close(fd[1]);
	}
	printf("Finished\n");
	return (0);
}
~~~

---

### unlink

Deletes a name from the filesystem. If the name is connected to a file which is not in use, it deletes the file.

#### return
- 0 on success, else -1

---

### wait

Blocks the parent process until one of its child terminates.

#### return
- child PID on success, else -1

Sources
---

- ### pipex guides <br>

	https://reactive.so/post/42-a-comprehensive-guide-to-pipex/ <br>
	https://42-cursus.gitbook.io/guide/rank-02/pipex/understand-pipex <br>


- ### functions <br>

	- **access** <br>
		https://pubs.opengroup.org/onlinepubs/009695299/functions/access.html <br>

	- **dup2** <br>
		https://www.geeksforgeeks.org/dup-dup2-linux-system-call/ <br>

	- **wait** <br>
		https://www.geeksforgeeks.org/wait-system-call-c/ <br>

	- **waitpid** <br>
		https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-waitpid-wait-specific-child-process-end


