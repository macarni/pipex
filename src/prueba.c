#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
// WRITE_END 1
// READ_END 0

int main(void)
{
	int fd[2];
	int status;
	pid_t pid;
	int archivo;
	char **cmd;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{ //hijo escribe por lo que cerramos el de lectura
		close(fd[0]); //vamos ESCRIBIR en el pipe, asi que se cierra el de lectura
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		cmd = calloc(sizeof(char *), 2);
		cmd[0] = "ls -la";
		cmd[1] = 0;
		execve("/bin/ls", cmd, NULL);
		free(cmd);
	}
	else if (pid == -1)
	{

	}
	else
	{ //padre lee, así que cerramos el de escritura
		close(fd[1]);
		pid = fork(); //segundo hijo
		if (pid == 0)
		{ 
			//solo hereda el de lectura abierto (porque el de escritura está cerrado por el padre)
			archivo = open("outfile", O_CREAT | O_RDWR | O_TRUNC, 0644);
			dup2(fd[0], STDIN_FILENO); //queremos que lea del extremo de lectura del pipe (el que el padre tiene abierto)
			close(fd[0]);
			dup2(archivo, STDOUT_FILENO); //para que escriba en el archvo abierto
			cmd = calloc(sizeof(char *), 2);
			cmd[0] = "wc -c";
			cmd[1] = 0;
			execve("/usr/bin/wc", cmd, NULL);
			free(cmd);
		}
		else 
		{
			close(fd[0]); //para que se cierre el extremo cuando ya no es necesario
		}
	}
	//un wait para cada hijo
	wait(&status);
	wait(&status);
	return (0);
}