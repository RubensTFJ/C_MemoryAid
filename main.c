#include "memory_aid.h"

typedef struct s_itoa {
    char    arr[12];
    char    *str;
} t_itoa;

t_itoa   ft_itoa(int number)
{
    t_itoa  	ascii;
	int			index;
	int			sign;

	sign = (number > 0) - (number < 0);
	index = 11;
    ascii.arr[index] = 0;
	while (number || index == 11)
	{
		ascii.arr[--index] = (number % 10) * sign + '0';
		number = number / 10;
	}
	if (sign < 0)
		ascii.arr[--index] = '-';
    ascii.str = &ascii.arr[index];
    return (ascii);
}

int main(void)
{
    printf("%s\n", ft_itoa(1234567890).str);
    return (0);
}
