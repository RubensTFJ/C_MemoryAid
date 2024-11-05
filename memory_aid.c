#include "memory_aid.h"

t_memory_aid *maid(void)
{
    static t_full_memory_aid memory_aid;

    return ((t_memory_aid*)&memory_aid);
}

void    maid_calloc(void** pointer, int size)
{
    t_full_memory_aid *this;

    this = ((t_full_memory_aid*)(maid()));
    maid_add_guests(pointer);
    maid_housekeep();
}

void    maid_alloc(void** pointer, int size)
{
    t_room              *new_room;
    t_vector            *hotel;

    *pointer = malloc(size);
    new_room = malloc(sizeof(t_room));
    new_room->space = *pointer;
    new_room->guest = pointer;
    ((t_full_memory_aid*)maid())->hotel->push_back(new_room);
    maid_housekeep();
}

void    maid_share(void*, void*);
void    maid_pass(void*, void*);
void    maid_check(void*);
void    maid_cleanup(void);

void    maid_housekeep()
{
    t_full_memory_aid   *this;
    t_room      **rooms;
    int         number;

    this = (t_full_memory_aid*)maid();
    rooms = this->hotel->array;
    number = 0;
    while (number < this->hotel->size)
    {
        if (*rooms[number]->guest != rooms[number]->space)
        {
            free(rooms[number]->space);
            free(rooms[number]);
            rooms[number] = (void*)0;
        }
        number++;
    }
}

// void    maid_add_guests(void** pointer)
// {
//     t_full_memory_aid *this;

//     this = ((t_full_memory_aid*)(maid()));
//     this->guests->push_back(pointer);
// }