#include <stdio.h>
#include <unistd.h>

int main()
{
	int		ret;
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		ret = ttyslo(STDIN_FILENO);
		printf("child: %d\n", ret);
	}
	else
	{
		ret = isatty(STDIN_FILENO);
		printf("parent: %d\n", ret);
	}
}
