#

typedef struct s_vector {
    void    **array;
    int     size;
    void*(*push_back)(void*);
    void*(*for_each)(void*(*)());
    void*(*check)(void*);
    void(*cleanup)(void);
} t_vector;

typedef struct s_room {
    void**  guest;
    void*   space;
    // bool    occupied;
} t_room;

typedef struct s_full_memory_aid {
    void*(*alloc)(void**, int);
    void*(*share)(void*, void*);
    void*(*pass)(void*, void*);
    void*(*check)(void*);
    void(*cleanup)(void);

    void(*housekeep)(void);
    void(*add_guests)(void**);
    t_vector    *hotel;
} t_full_memory_aid;

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

