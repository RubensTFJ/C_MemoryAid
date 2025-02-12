#include "memory_aid.h"
#include <stdarg.h>

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
	temp = NULL;
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


// #define CALL_FUNCTION(fn_ptr, ...) fn_ptr(__VA_ARGS__)

// void	caller(void *function, ...)
// {
//     va_list args;
    
//     // Start processing the variable arguments
//     va_start(args, function);
    
//     // Call the function pointer by casting it to the appropriate type
//     ((void(*)())function)(args);
//     ((void(*)())function)(__VA_ARGS__);
    
//     // End processing the variable arguments
//     va_end(args);
// }


int main(void)
{
	int	*test1;
	int	*test2;
	int	*test3;
	int	*test4;
	int	*test5;
	int	*test6;

	maid()->start();
	test1 = malloc(sizeof(int));
	test2 = malloc(sizeof(int));
	test3 = malloc(sizeof(int));
	test4 = malloc(sizeof(int));
	test5 = malloc(sizeof(int));
	test6 = malloc(sizeof(int));
	printf("mallocs\n");
	maid()->book(&test1);
	maid()->book(&test2);
	maid()->book(&test3);
	printf("books\n");
	test2 = NULL;
	printf("null\n");
	maid()->book(&test4);
	maid()->book(&test5);
	maid()->book(&test6);
	printf("more books\n");

	test1 = NULL;
	test2 = NULL;
	test3 = NULL;
	test4 = NULL;
	test5 = NULL;
	test6 = NULL;
	printf("more nulls\n");
	maid_alloc((void*)&test1, sizeof(int));
	printf("maid_alloc\n");
	maid_alloc((void*)&test1, sizeof(int));
	maid_alloc((void*)&test1, sizeof(int));
	maid_alloc((void*)&test1, sizeof(int));
	maid_alloc((void*)&test1, sizeof(int));
	maid_alloc((void*)&test1, sizeof(int));
	maid_alloc((void*)&test1, sizeof(int));

	test1 = NULL;
	printf("itoa malloc\n");
	ft_itoa(123);
	stack_func();
	printf("clean up\n");
	maid()->cleanup();
	printf("clean up\n");
	printf("before destroy\n");
	
	maid()->destroy();
    return (0);
}
