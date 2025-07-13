#include "philo.h"

void	error_exit(void)
{
	write(1, "Error\n", 6);
	exit(0);
}

void	check_number(long long result, int i, char *str)
{
	if (result > 2147483647 || result < -2147483648)
		error_exit();
	if (str[i] != '\0')
		error_exit();
}

int	ft_atoi(char *str)
{
	int		sign;
	int		i;
	long	result;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647 || result < -2147483648)
			error_exit();
		i++;
	}
	check_number(result, i, str);
	return (sign * result);
}