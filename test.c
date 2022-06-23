#include <stdlib.h>
#include <stdio.h>

int	nbr_len(long nbr)
{
	long	i;

	i = 1;
	if (nbr < 0)
	{
		i++;
		nbr *= -1;
	}
	while (nbr > 9)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

int	ft_div(long len)
{
	long	i;

	i = 1;
	if (len == 1)
		return (1);
	while (len > 1)
	{
		i *= 10;
		len--;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	int		len_2;
	long	nbr;
	char	*chard;

	i = 0;
	nbr = n;
	len = nbr_len(nb);
	len_2 = len;
	printf("%d\n", len);
	chard = (char *)malloc(sizeof(char) * (len + 1));
	if (chard == NULL)
		return (NULL);
	if (nbr < 0)
	{
		nbr *= -1;
		chard[i++] = '-';
		len--;
	}
	while (i < nbr_len())
		chard[i++] = ((nbr / ft_div(len--)) % 10) + 48;
	chard[i] = '\0';
	return (chard);
}

int main()
{
	int n = 2147483647;
	char *tmp1;

	tmp1 = ft_itoa(n);
	printf("%s\n", tmp1);
	free (tmp1);
}