#include "Ticket.h"
#include "Customer.h"

int main() {
	std::string date = "17:00 20.01.2024";
	std::vector<int> size = { 10,20 };	
	std::string name = "GoodTheatre";
	std::string address = "addr";
	Theatre theatre1(name, address, size);
	std::cout << theatre1.get_theatre_hall_size()[0]<<" "<< theatre1.get_theatre_hall_size()[1]<<std::endl;

	name = "Great performance";
	Actor actor1("Dimon", 25, "Good actor");
	Performance perf1(name, date, 25, theatre1);
	perf1.new_role("Ivan", actor1);


	int place[2] = {1,1};
	/*Ticket tic1(perf1, place);
	tic1.print_ticket();*/

	Customer cust1("Bob", 14, false);

	place[0] = 1; place[1] = 2;
	Ticket tic1 = cust1.buy_ticket(perf1, place);
	Ticket tic2 = cust1.buy_ticket(perf1, place);
	tic2.print_ticket();
	return 0;
}