#include <unistd.h>
#include <sys/wait.h>
int main()
{
	pid_t	pid;

	pid = fork();
	if (!pid)
		execve("./a.out", NULL, NULL);
	else
		wait(NULL);
}