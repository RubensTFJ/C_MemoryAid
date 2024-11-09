#include "memory_aid.h"

typedef struct s_itoa {
    char    arr[12];
    char    *str;
} t_itoa;

t_itoa   ft_itoa(int number)
{
    t_itoa  	ascii;
	void		*temp;
	int			index;
	int			sign;

	// printf("before first malloc\n");

	maid()->alloc(&temp, sizeof(t_mem_room));
	// printf("first malloc ok\n");

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

void	stack_func(void)
{
	t_itoa  			ascii;
	t_mem_hotel			a;
	t_super_memory_aid	b;
	void				*temp;
	int					index;
	int					sign;

	ascii = (t_itoa){"asdasd", NULL};
	a = (t_mem_hotel){NULL};
}

int main(void)
{
	int	*test1;

	HERE;
	maid()->manual(0);
	// printf("manual ok\n");
	maid()->alloc(&test1, sizeof(int));
	test1 = NULL;
	ft_itoa(3232);
	// printf("itoa ok\n");
	// printf("itoa ok\n");
	stack_func();
	ft_itoa(3232);
	stack_func();
	ft_itoa(3232);

    return (0);
}
