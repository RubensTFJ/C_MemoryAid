
#ifndef MEMORY_AID_H
# define MEMORY_AID_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define HOTEL_EXPANSION  500
# define HERE  write(2, "here\n", 5);
# define THERE  write(2, "there\n", 6);

typedef struct s_mem_hotel t_mem_hotel;
typedef struct s_super_memory_aid t_super_memory_aid;
typedef struct s_memory_aid t_memory_aid;

typedef struct s_vector {
	void	**array;
	int		size;
	void	*(*push_back)(void*);
	void	*(*for_each)(void*(*)());
	void	*(*check)(void*);
	void	(*cleanup)(void);
} t_vector;

typedef struct s_reference {
	void**  reference;
} t_reference;

typedef struct s_mem_room {
	void**  guest;
	void*   reference;
	bool	occupied;
} t_mem_room;

typedef struct s_mem_hotel {
	t_mem_room  *listing;
	int			vacancy;
	int			size;
	int			capacity;
	void		(*checkin)(t_mem_hotel *, void**);
	void		(*for_each)(t_mem_room*, void*(*)());
	void		(*destroy)(t_mem_hotel*);
} t_mem_hotel;

typedef struct s_super_memory_aid {
	void			(*alloc)(void*, int);
	t_memory_aid	*(*start)(void);
	void			(*share)(void*, void*);
	void			(*pass)(void*, void*);
	void			(*check)(void*);
	void			(*cleanup)(void);
	void			(*manual)(void);
	void			(*book)(void*);
	void			(*efficiency)(void);
	void			(*destroy)(void);

	void		(*housekeep)(void);
	int			automatic;
	t_mem_hotel *hotel;
} t_super_memory_aid;

typedef struct s_memory_aid {
	void			(*alloc)(void*, int);
	t_memory_aid	*(*start)(void);
	void			(*share)(void*, void*);
	void			(*pass)(void*, void*);
	void			(*check)(void*);
	void			(*cleanup)(void);
	void			(*manual)(void);
	void			(*book)(void*);
	void			(*efficiency)(void);
	void			(*destroy)(void);
} t_memory_aid;

void			maid_alloc(void**, int);
// void			maid_share(void*, void*);
// void			maid_pass(void*, void*);
// void			maid_check(void*);
// void			maid_cleanup(void);
void			*new_hotel(void);
t_memory_aid	*maid(void);

#endif