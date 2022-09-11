#include <stdio.h>
#include <unistd.h>
#include "includes/minishell.h"

char	*get_historypath(void)
{
	char	*tmp;
	char	*path;
	char	*final;

	tmp = getenv("_");
	path = ft_substr(tmp, 0, ft_strlen(tmp) - 12);
	final = ft_strjoin(path, "src/history/.history");
	free(path);
	return (final);
}

int main()
{
	char	*str = get_historypath();
	printf("%s\n", free(str));
	// free(str);
}