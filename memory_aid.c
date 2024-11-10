#include "memory_aid.h"

static inline t_super_memory_aid *sudo(t_memory_aid *toreturn)
{
	return ((t_super_memory_aid*)toreturn);
}

void	maid_alloc(void** pointer, int size)
{
	t_super_memory_aid  *this;

	this = sudo(maid());
	*pointer = malloc(size);
	this->hotel->checkin(this->hotel, pointer);
	if (this->automatic)
		this->housekeep();
}

void	maid_housekeep(void)
{
	t_mem_hotel *hotel;
	t_mem_room  *room;
	int			clear;
	int			number;

	hotel = sudo(maid())->hotel;
	number = 0;
	room = hotel->listing;
	while (number < hotel->size)
	{
		if (room->occupied && *(room->guest) != room->reference)
		{
			printf("freed room %i\n", number);
			free(room->reference);
			room->guest = NULL;
			room->occupied = false;
			if (number < hotel->vacancy)
				hotel->vacancy = number;
		}
		++room;
		++number;
	}
	while (hotel->size > 0 && (hotel->listing[hotel->size - 1].occupied == false))
		hotel->size--;
}

void	maid_destroy(void)
{
	sudo(maid())->hotel->destroy(sudo(maid())->hotel);
}

void	maid_manual(void)
{
	sudo(maid())->automatic = 0;
}

void	maid_book_memory(void **guest)
{
	t_super_memory_aid	*this;

	this = sudo(maid());
	this->hotel->checkin(this->hotel, guest);
	if (this->automatic)
		this->housekeep();
}

t_memory_aid	*maid_start(void)
{
	sudo(maid())->hotel = new_hotel();
	return (maid());
}

t_memory_aid *maid(void)
{
	static t_super_memory_aid memory_aid = {
		.alloc = (void*)maid_alloc,
		.start = maid_start,
		// .share = maid_share,
		// .pass = maid_pass,
		// .check = maid_check,
		.cleanup = maid_housekeep,
		.manual = maid_manual,
		.book = (void*)maid_book_memory,
		.destroy = maid_destroy,
		.housekeep = maid_housekeep,
		.automatic = 1,
	};

	return ((t_memory_aid*)&memory_aid);
}