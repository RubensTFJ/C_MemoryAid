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
	this->hotel->checkin(pointer);
	if (!this->automatic)
		this->housekeep(this);
}

void	maid_housekeep(t_super_memory_aid *this)
{
	t_mem_hotel *hotel;
	t_mem_room  *listing;
	t_mem_room  *room;
	int		 number;

	hotel = this->hotel;
	listing = hotel->listing;
	number = 0;
	printf("housekeep\n");
	while (number < hotel->size)
	{
		room = &listing[number];
		printf("house keep %p, %p\n", *(room->guest), room->reference);
		if (room->occupied && *(room->guest) != room->reference)
		{
			printf("freed room %i\n", number);
			free(room->reference);
			room->occupied = false;
			if (number < hotel->vacancy)
				hotel->vacancy = number;
		}
		number++;
	}
	while (hotel->size > 0 && (hotel->listing[hotel->size - 1].occupied == false))
		hotel->size--;
	printf("hotel size = %i\n", hotel->size);
	
}

void	hotel_checkin(void** guest)
{
	t_mem_hotel *hotel;
	t_mem_room  *room;

	hotel = sudo(maid())->hotel;
	hotel->size += (hotel->vacancy == hotel->size);
	room = &hotel->listing[hotel->vacancy];
	room->guest = guest;
	room->reference = *guest;
	room->occupied = true;
	printf("hotel vacancy & size before %i, %i\n", hotel->vacancy, hotel->size);
	while (hotel->vacancy < hotel->capacity && hotel->listing[hotel->vacancy].occupied)
		hotel->vacancy++;
	printf("hotel vacancy & size after %i, %i\n", hotel->vacancy, hotel->size);
	if (hotel->vacancy >= hotel->capacity)
	{
		hotel->listing = realloc(hotel->listing, sizeof(t_mem_room) * hotel->capacity + HOTEL_EXPANSION);
		hotel->capacity += HOTEL_EXPANSION;
	}
}

void	do_nothing(void)
{
	return ;
}

void	hotel_destroy(t_mem_hotel *this)
{
	free(this->listing);
	free(this);
}

void	*new_hotel(void)
{
	t_mem_hotel	*this;

	this = calloc(sizeof(t_mem_hotel), 1);
	this->listing = calloc(sizeof(t_mem_room), HOTEL_EXPANSION);
	this->size = 0;
	this->capacity = HOTEL_EXPANSION;
	this->checkin = hotel_checkin;
	this->destroy = hotel_destroy;
	return (this);
}

// void	maid_automatic(void)
// {
// 	sudo(maid())
// }

void	maid_destroy(void)
{
	sudo(maid())->hotel->destroy(sudo(maid())->hotel);
}

void	maid_manual(int	size)
{
	t_super_memory_aid	*this;

	this = sudo(maid());
	this->automatic = size;
	this->hotel = new_hotel();
}

void	maid_book_memory(void **guest)
{
	t_super_memory_aid	*this;

	this = sudo(maid());
	this->hotel->checkin(guest);
	if (!this->automatic)
		this->housekeep(this);
}

t_memory_aid *maid(void)
{
	static t_super_memory_aid memory_aid = {
		.alloc = maid_alloc,
		// .share = maid_share,
		// .pass = maid_pass,
		// .check = maid_check,
		.cleanup = maid_housekeep,
		.book = maid_book_memory,
		.housekeep = maid_housekeep,
		.destroy = maid_destroy,
		.manual = maid_manual,
	};

	return ((t_memory_aid*)&memory_aid);
}