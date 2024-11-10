#include "memory_aid.h"

void	hotel_destroy(t_mem_hotel *this)
{
	int			number;
	t_mem_room	*room;

	number = 0;
	while (number < this->size)
	{
		room = &this->listing[number];
		if (room->occupied)
		{
			free(room->reference);
			room->occupied = false;
		}
		number++;
	}
	free(this->listing);
	free(this);
}

void	hotel_checkin(t_mem_hotel *this, void** guest)
{
	t_mem_room  *room;

	this->size += (this->vacancy == this->size);
	room = &this->listing[this->vacancy];
	room->guest = guest;
	room->reference = *guest;
	room->occupied = true;
	while (this->vacancy < this->capacity && this->listing[this->vacancy].occupied)
		this->vacancy++;
	if (this->vacancy >= this->capacity)
	{
		this->listing = realloc(this->listing, sizeof(t_mem_room) * this->capacity + HOTEL_EXPANSION);
		this->capacity += HOTEL_EXPANSION;
	}
}

void	*new_hotel(void)
{
	t_mem_hotel	*this;

	this = calloc(sizeof(t_mem_hotel), 1);
	this->listing = calloc(sizeof(t_mem_room), HOTEL_EXPANSION);
	this->capacity = HOTEL_EXPANSION;
	this->checkin = hotel_checkin;
	this->destroy = hotel_destroy;
	return (this);
}