#include "memory_aid.h"

t_memory_aid *maid(void)
{
    static t_super_memory_aid memory_aid;

    return ((t_memory_aid*)&memory_aid);
}

// void    maid_calloc(void** pointer, int size)
// {
//     t_super_memory_aid *this

//     this = ((t_super_memory_aid*)(maid()));
//     maid_add_guests(pointer);
//     maid_housekeep();
// }

void    maid_alloc(void** pointer, int size)
{
    t_super_memory_aid  *this;

    this = (t_super_memory_aid*)maid();
    *pointer = malloc(size);
    this->hotel->checkin(pointer);
    this->housekeep(this->hotel);
    // (t_mem_hotel*){ malloc(sizeof(t_mem_hotel)) } = (t_mem_hotel) {0};
}

void    maid_share(void*, void*);
void    maid_pass(void*, void*);
void    maid_check(void*);
void    maid_cleanup(void);

void    maid_housekeep(t_mem_hotel *this)
{
    t_mem_room  *listing;
    t_mem_room  *room;
    int         number;

    listing = this->listing;
    number = 0;
    while (number < this->size)
    {
        room = &listing[number];
        if (*room->guest != room->reference)
        {
            free(room->reference);
            room->occupied = 0;
            if (number < this->vacancy)
                this->vacancy = number;
        }
        number++;
    }
}

void    hotel_checkin(void** guest)
{
    t_mem_hotel *hotel;
    t_mem_room  *room;

    hotel = ((t_super_memory_aid*)maid())->hotel;
    room = &hotel->listing[hotel->vacancy];
    room->guest = guest;
    room->reference = *guest;
    room->occupied = 1;
    while (hotel->vacancy < hotel->capacity && hotel->listing[hotel->vacancy].occupied)
        hotel->vacancy++;
    if (hotel->vacancy >= hotel->capacity)
    {
        hotel->listing = realloc(hotel->listing, sizeof(t_mem_room) * hotel->capacity + 500);
        hotel->capacity += 500;
    }
}
