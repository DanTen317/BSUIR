#include "Customer.h"

Customer::Customer(std::string name, int age, bool is_student)
	: is_student(is_student), Human(name, age) {}

int Customer::get_discount()
{
	if (this->age <= 14)
		return 30;
	else if (this->is_student == true || this->age >=60)
		return 20;
	else
		return 0;
}

void Customer::print() const
{
	Human::print();
	std::cout << "is a customer"<<std::endl;
}

Ticket Customer::buy_ticket(Performance& performance, int place[2])
{
	Ticket ticket(performance, place);
	ticket.make_discount(this->get_discount());
	performance.take_place(place);
	return ticket;
}
