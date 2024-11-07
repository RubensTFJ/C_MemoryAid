// #include <stdio.h>

typedef struct s_vector {
    void    **array;
    int     size;
    void    *(*push_back)(void*);
    void    *(*for_each)(void*(*)());
    void    *(*check)(void*);
    void    (*cleanup)(void);
} t_vector;

typedef struct s_reference {
    void**  reference;
} t_reference;

typedef struct s_mem_room {
    void**  guest;
    void*   reference;
    char    occupied;
} t_mem_room;

typedef struct s_mem_hotel {
    t_mem_room  *listing;
    int         vacancy;         
    int         size;
    int         capacity;
    void        *(*checkin)(void**);
    void        *(*for_each)(t_mem_room*,void*(*)());
} t_mem_hotel;

typedef struct s_super_memory_aid {
    void        *(*alloc)(void**, int);
    void        *(*share)(void*, void*);
    void        *(*pass)(void*, void*);
    void        *(*check)(void*);
    void        (*cleanup)(void);

    void        (*housekeep)(void);
    t_mem_hotel *hotel;
} t_super_memory_aid;

typedef struct s_memory_aid {
    void*(*alloc)(void**, int);
    void*(*share)(void*, void*);
    void*(*pass)(void*, void*);
    void*(*check)(void*);
    void(*cleanup)(void);
} t_memory_aid;


void            maid_alloc(void**, int);
void            maid_share(void*, void*);
void            maid_pass(void*, void*);
void            maid_check(void*);
void            maid_cleanup(void);
t_memory_aid    *maid(void);

