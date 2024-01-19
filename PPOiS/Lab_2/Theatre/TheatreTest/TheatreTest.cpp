#include "pch.h"
#include "CppUnitTest.h"
#include "../Customer.h"
#include "../Date.h"
#include "../Actor.h"
#include "../Ticket.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TheatreTest
{
	TEST_CLASS(HumanTest) {
public:
	TEST_METHOD(TestCustomerCreationForChild)
	{
		std::stringstream buf;
		std::streambuf* oldbuf = std::cout.rdbuf(buf.rdbuf());

		Customer i("Bob", 14, false);
		i.print();
		std::cout << "discount: " << i.get_discount() << "%";

		std::cout.rdbuf(oldbuf);
		std::string output = buf.str();
		std::string expected_output = "Bob\nis a customer\ndiscount: 30%";
		Assert::AreEqual(output, expected_output);
	}
	TEST_METHOD(TestCustomerCreationForOrdinary)
	{
		std::stringstream buf;
		std::streambuf* oldbuf = std::cout.rdbuf(buf.rdbuf());

		Customer i("Bob", 30, false);
		i.print();
		std::cout << "discount: " << i.get_discount() << "%";

		std::cout.rdbuf(oldbuf);
		std::string output = buf.str();
		std::string expected_output = "Bob\nis a customer\ndiscount: 0%";
		Assert::AreEqual(output, expected_output);
	}
	TEST_METHOD(TestCustomerCreationForStudent)
	{
		std::stringstream buf;
		std::streambuf* oldbuf = std::cout.rdbuf(buf.rdbuf());

		Customer i("Bob", 18, true);
		i.print();
		std::cout << "discount: " << i.get_discount() << "%";

		std::cout.rdbuf(oldbuf);
		std::string output = buf.str();
		std::string expected_output = "Bob\nis a customer\ndiscount: 20%";
		Assert::AreEqual(output, expected_output);
	}
	TEST_METHOD(TestActorCreation) {
		std::stringstream buf;
		std::streambuf* oldbuf = std::cout.rdbuf(buf.rdbuf());

		Actor i("Bob", 18, "Honored man");
		i.print();

		std::cout.rdbuf(oldbuf);
		std::string output = buf.str();
		std::string expected_output = "Bob\nis an actor\nHonored man\n";
		Assert::AreEqual(output, expected_output);
	}
	};
	TEST_CLASS(DateTest)
	{
	public:
		TEST_METHOD(TestDateUncorrectTime) {

			Date date("144:30 01.09.2023");

			Assert::AreEqual(date.get_time().get_hours(), 12);
			Assert::AreEqual(date.get_time().get_minutes(), 00);
			Assert::AreEqual(date.get_day(), 1);
			Assert::AreEqual(date.get_month(), 9);
			Assert::AreEqual(date.get_year(), 2023);
		}
		TEST_METHOD(TestDateUncorrectDate) {

			Date date("14:30 01.112.1212");

			Assert::AreEqual(date.get_time().get_hours(), 14);
			Assert::AreEqual(date.get_time().get_minutes(), 30);
			Assert::AreEqual(date.get_day(), 1);
			Assert::AreEqual(date.get_month(), 1);
			Assert::AreEqual(date.get_year(), 1970);
		}
		TEST_METHOD(TestDateUncorrectDateFeb) {

			Date date("14:30 29.02.2023");

			Assert::AreEqual(date.get_time().get_hours(), 14);
			Assert::AreEqual(date.get_time().get_minutes(), 30);
			Assert::AreEqual(date.get_day(), 1);
			Assert::AreEqual(date.get_month(), 1);
			Assert::AreEqual(date.get_year(), 1970);

			Date date2("14:30 29.02.2024");

			Assert::AreEqual(date2.get_time().get_hours(), 14);
			Assert::AreEqual(date2.get_time().get_minutes(), 30);
			Assert::AreEqual(date2.get_day(), 29);
			Assert::AreEqual(date2.get_month(), 2);
			Assert::AreEqual(date2.get_year(), 2024);
		}
		TEST_METHOD(TestDateUncorrectDateDay) {

			Date date("14:30 32.01.2023");

			Assert::AreEqual(date.get_time().get_hours(), 14);
			Assert::AreEqual(date.get_time().get_minutes(), 30);
			Assert::AreEqual(date.get_day(), 1);
			Assert::AreEqual(date.get_month(), 1);
			Assert::AreEqual(date.get_year(), 1970);
		}
	};
	TEST_CLASS(TheatreTest) {
		TEST_METHOD(TestTheatreCreation) {
			std::vector<int> size = { 10,20 };
			std::string name = "GoodTheatre";
			std::string address = "Minsk, Fine st., 13";
			Theatre theatre1(name, address, size);
			std::string expected_output = "GoodTheatre\nMinsk, Fine st., 13\n";
			Assert::AreEqual(theatre1.info(), expected_output);
			Assert::AreEqual(theatre1.get_name(), name);
			Assert::IsTrue(size == theatre1.get_theatre_hall_size());
		}

	};
	TEST_CLASS(PerformanceTest) {
		TEST_METHOD(TestPerformanceCreation) {
			std::vector<int> size = { 12,16 };
			std::string name = "BigTheatre";
			std::string address = "Minsk, Green st., 21";
			std::string date = "17:00 20.01.2024";
			Theatre theatre1(name, address, size);

			name = "Great performance";
			Performance perf1(name, date, 25, theatre1);
			std::string expected_output = "BigTheatre\n"
				"Great performance\n17:0 20.1.2024\n25.000000";
			Assert::AreEqual(perf1.info(), expected_output);
		}
		TEST_METHOD(TestRolesCreation) {
			Performance perf1;
			Actor actor1("Dimon", 25, "Good actor");
			Actor actor2("Alexei", 19, "Funny actor");
			perf1.new_role("Ivan", actor1);
			perf1.new_role("Bard", actor2);
			Role expected1("Ivan", actor1);
			Role expected2("Bard", actor2);
			Assert::IsTrue(perf1.get_role(1) == expected1);
			Assert::IsTrue(perf1.get_role(2) == expected2);
		}
	};
	TEST_CLASS(TicketTest) {
		TEST_METHOD(TestTicketCreation) {
			std::stringstream buf;
			std::streambuf* oldbuf = std::cout.rdbuf(buf.rdbuf());

			std::string date = "17:00 20.01.2024";
			std::vector<int> size = { 10,20 };
			std::string name = "GoodTheatre";
			std::string address = "addr";
			Theatre theatre1(name, address, size);

			name = "Great performance";
			Performance perf1(name, date, 25, theatre1);

			int place[2] = { 1,1 };
			Ticket tic1(perf1, place);
			tic1.print_ticket();
			std::cout.rdbuf(oldbuf);
			std::string output = buf.str();

			std::string expected_output = "GG11201\nGreat performance\n"
				"1 1\n25";
			Assert::AreEqual(expected_output, output);
		}
		TEST_METHOD(ThestTicketBuying) {
			std::stringstream buf;
			std::streambuf* oldbuf = std::cout.rdbuf(buf.rdbuf());

			std::string date = "17:00 20.01.2024";
			std::vector<int> size = { 10,16 };
			std::string name = "GoodTheatre";
			std::string address = "addr";
			Theatre theatre1(name, address, size);

			name = "Great performance";
			Performance perf1(name, date, 25, theatre1);

			int place[2] = { 1,2 };

			Customer cust1("Bob", 14, false);
			
			Ticket tic2 = cust1.buy_ticket(perf1, place);
			tic2.print_ticket();
			std::cout.rdbuf(oldbuf);
			std::string output = buf.str();
			std::string expected_output = "GG12201\nGreat performance\n"
				"1 2\n17.5";
			Assert::AreEqual(expected_output, output);
		}
		TEST_METHOD(ThestTicketBuyingButPlaceIsTaken) {
			std::stringstream buf;
			std::streambuf* oldbuf = std::cout.rdbuf(buf.rdbuf());

			std::string date = "17:00 20.01.2024";
			std::vector<int> size = { 10,16 };
			std::string name = "GoodTheatre";
			std::string address = "addr";
			Theatre theatre1(name, address, size);

			name = "Great performance";
			Performance perf1(name, date, 25, theatre1);

			int place[2] = { 1,2 };

			Customer cust1("Bob", 14, false);

			Ticket tic1 = cust1.buy_ticket(perf1, place);
			Ticket tic2 = cust1.buy_ticket(perf1, place);
			tic2.print_ticket();
			std::cout.rdbuf(oldbuf);
			std::string output = buf.str();
			std::string expected_output = "place is taken\nGreat performance\n"
				"1 2\n17.5";
			Assert::AreEqual(expected_output, output);
		}
	};
}
