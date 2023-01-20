#include "../head/philo.h"

void init_data(t_data *data, int32_t ac, char **av)
{
    int32_t i;

    i = 1;
    data->amount_philos = ft_atoi(av[1]);
    if (ac != 5 && ac != 6)
        error_msg("Wrong input! usage: ./philo <param> <param> <param> <param>");
	if (data->amount_philos < 2)
		error_msg("Invalid input! Minimum 2 philosophers!");
	while (i < ac)
	{
		if (check_for_valid_arg(av[i]))
			error_msg("Arguments contain non digit Characters!\n");
		i++;
	}
    if (ft_atoi(av[3]) + ft_atoi(av[4]) > ft_atoi(av[2]))
		error_msg("Invalid input! The time to eat and sleep must not exceed the time to die!");
}

/* function checks for valid input (only digits or whitespaces)
 * returns 1 for invalid input
 * returns 0 for valid input								*/
int32_t check_for_valid_arg(char *av)
{
	int32_t i = 0;

	while (av[i] != '\0')
	{
		if (!ft_isdigit(av[i]) && whitespace(av[i]))
			return (1);
		i++;
	}
	return (0);
	// check later also if arguments make sense etc (if that makes sense lol)
}

/* function checks if c is any kind of whitespace
 * returns 0 if c is whitespace
 * returns 1 if c is something but whitespace	*/
int32_t whitespace(char c)
{
	if ((c >= 1 && c <= 31) || c == 127)
		return (0);
	return (1);
}