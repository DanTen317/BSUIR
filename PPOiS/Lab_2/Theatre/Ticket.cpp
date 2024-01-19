#include "Ticket.h"


//void Ticket::make_discount(Customer customer)
//{
//	this->price = this->price * (1 - customer.get_discount());
//	
//}

void Ticket::create_id()
{
	id += performance.theatre.get_name()[0];
	id += performance.name[0];
	id += std::to_string(place[0]) + std::to_string(place[1])
		+ std::to_string(performance.date.get_day()) + std::to_string(performance.date.get_month());
}

Ticket::Ticket(Performance& performance, int place[2])
	:performance(performance),price(performance.price)
{
	this->place.push_back(place[0]);
	this->place.push_back(place[1]);
	if (!performance.place_is_taken({ this->place[0], this->place[1] })) {
		create_id();
	}
	else
		id = "place is taken";
}

void Ticket::print_ticket()
{
	for (char i : id) {
		std::cout << i;
	}
	std::cout << std::endl << performance.name << std::endl;
	std::cout << place[0] << " " << place[1] << std::endl << price;

}

void Ticket::make_discount(int discount)
{
	this->price = this->price * (1.0 - discount/100.0);
}