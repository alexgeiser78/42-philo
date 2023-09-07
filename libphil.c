#include "philo.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					negative;
	int					result;

	i = 0;
	negative = 1;
	result = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		negative = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * negative);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	else
		return (0);
}
