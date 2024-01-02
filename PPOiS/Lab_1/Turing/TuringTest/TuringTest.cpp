#include "pch.h"
#include "CppUnitTest.h"
#include <sstream>
#include <vector>

#include "../console.h"
//#include "../Machine.h"
//#include "../Rule.h"
//#include "../Tape.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TuringTest
{
	TEST_CLASS(TuringTest)
	{
	public:
		TEST_METHOD(AddSymbolTest1)
		{
			Machine turing_machine;
			char symbol[3] = { '0','1','0' };
			for (char one_symbol : symbol) {
				turing_machine.write(one_symbol);
			}
			int i = 0;
			for (char symb : turing_machine.get_tape()) {
				Assert::AreEqual(symb,symbol[i]);
				i++;
			}
		}

		TEST_METHOD(PrintMachineTest1)
		{
			Machine turing_machine;
			char symbol[3] = { '0','1','0' };
			for (char one_symbol : symbol) {
				turing_machine.write(one_symbol);
			}

			std::stringstream buf;
			std::streambuf* oldbuf = std::cout.rdbuf(buf.rdbuf());

			print_machine(turing_machine);
			std::cout.rdbuf(oldbuf);
			std::string output = buf.str();
			std::string expected_output = "-----\n0 1 0 \n-----\n";
			Assert::AreEqual(output, expected_output);
		}
		TEST_METHOD(MoveHeadTest1)
		{
			Machine turing_machine;
			char symbol[3] = { '0','1','0' };
			for (char one_symbol : symbol) {
				turing_machine.write(one_symbol);
			}
			turing_machine.head_move(RIGHT);
			turing_machine.head_move(RIGHT);
			turing_machine.head_move(LEFT);
			turing_machine.head_move(WAIT);

			Assert::AreEqual(turing_machine.get_head_position(), 1);
		}
		TEST_METHOD(RewriteSymbolTest1)
		{
			Machine turing_machine;
			char symbol[3] = { '0','1','0' };
			for (char one_symbol : symbol) {
				turing_machine.write(one_symbol);
			}
			turing_machine.rewrite(ONE);
			
			char result_symbol[3] = {'1','1','0'};
			int i = 0;
			for (char symb : turing_machine.get_tape()) {
				Assert::AreEqual(symb, result_symbol[i]);
				i++;
			}
		}
		TEST_METHOD(RewriteSymbolTest2)
		{
			Machine turing_machine;
			char symbol[3] = { '0','1','0' };
			for (char one_symbol : symbol) {
				turing_machine.write(one_symbol);
			}

			turing_machine.head_move(RIGHT);
			turing_machine.rewrite(ZERO);

			char result_symbol[3] = { '0','0','0' };
			int i = 0;
			for (char symb : turing_machine.get_tape()) {
				Assert::AreEqual(symb, result_symbol[i]);
				i++;
			}
		}

		TEST_METHOD(CreateRuleTestt1)
		{
			Machine turing_machine;
			turing_machine.new_rule("0", '1', "1", '0', '>');
			Assert::AreEqual(turing_machine.get_rules()[0][0],'0');
			Assert::AreEqual(turing_machine.get_rules()[0][1], '1');
			Assert::AreEqual(turing_machine.get_rules()[0][2], '1');
			Assert::AreEqual(turing_machine.get_rules()[0][3], '0');
			Assert::AreEqual(turing_machine.get_rules()[0][4], '>');	
			std::stringstream buf;
			std::streambuf* oldbuf = std::cout.rdbuf(buf.rdbuf());

			print_rules(turing_machine);
			std::cout.rdbuf(oldbuf);
			std::string output = buf.str();

			std::string expected_output = "0 1 1 0 > ";
			Assert::AreEqual(output, expected_output);
		}
		TEST_METHOD(CreateRuleTest2) {
			Machine turing_machine;
			std::stringstream buf;
			std::streambuf* oldbuf = std::cout.rdbuf(buf.rdbuf());
			turing_machine.new_rule("0", '1', "1", '0', '>');
			turing_machine.new_rule("0", '1', "1", '0', '>');
			
			std::cout.rdbuf(oldbuf);
			std::string output = buf.str();
			std::string expected_output = "Rule with this id already exist. \n";
			Assert::AreEqual(output, expected_output);

			std::stringstream buf_2;
			std::streambuf* oldbuf_2 = std::cout.rdbuf(buf_2.rdbuf());

			print_rules(turing_machine);
			std::cout.rdbuf(oldbuf_2);
			std::string output_2 = buf_2.str();
			expected_output = "0 1 1 0 > ";
			Assert::AreEqual(output_2, expected_output);
		}
		TEST_METHOD(DeleteRuleTest1)
		{
			Machine turing_machine;
			turing_machine.new_rule("0", '1', "1", '0', '>');
			turing_machine.new_rule("1", '0', "0", '0', '_');
			Assert::IsTrue(turing_machine.get_rules().size()== 2);
			turing_machine.delete_rule(1);

			std::stringstream buf;
			std::streambuf* oldbuf = std::cout.rdbuf(buf.rdbuf());

			print_rules(turing_machine);
			std::cout.rdbuf(oldbuf);
			std::string output = buf.str();
			std::string expected_output = "0 1 1 0 > ";
			Assert::AreEqual(output, expected_output);
		}

		TEST_METHOD(DoStepTest1) {
			Machine turing_machine;
			char symbol[3] = { '1','1','0' };
			for (char one_symbol : symbol) {
				turing_machine.write(one_symbol);
			}
			turing_machine.new_rule("0", '1', "1", '0', '>');
			turing_machine.new_rule("1", '1', "-1", '1', '_');
			turing_machine.do_step(turing_machine);
			//turing_machine.run_machine(turing_machine);

			std::stringstream buf;
			std::streambuf* oldbuf = std::cout.rdbuf(buf.rdbuf());

			Assert::IsTrue(turing_machine.get_head_position() == 1);
			print_machine(turing_machine);
			std::cout.rdbuf(oldbuf);
			std::string output = buf.str();
			std::string expected_output = "-----\n0 1 0 \n-----\n";
			Assert::AreEqual(output, expected_output);
		}

		TEST_METHOD(RunMachineTest1) {
			Machine turing_machine;
			char symbol[3] = { '1','1','0' };
			for (char one_symbol : symbol) {
				turing_machine.write(one_symbol);
			}
			turing_machine.new_rule("0", '1', "1", '0', '>');
			turing_machine.new_rule("1", '1', "-1", '1', '_');
			turing_machine.run_machine(turing_machine);

			std::stringstream buf;
			std::streambuf* oldbuf = std::cout.rdbuf(buf.rdbuf());

			print_machine(turing_machine);
			std::cout.rdbuf(oldbuf);
			std::string output = buf.str();
			std::string expected_output = "-----\n0 1 0 \n-----\n";
			Assert::AreEqual(output, expected_output);
			Assert::IsTrue(turing_machine.get_head_position() == 1);
		}
		TEST_METHOD(RunMachineTest2) {
			Machine turing_machine;
			char symbol[3] = { '1','1','0' };
			for (char one_symbol : symbol) {
				turing_machine.write(one_symbol);
			}
			turing_machine.new_rule("0", '1', "1", '0', '<');
			turing_machine.new_rule("1", '1', "-1", '1', '_');
			turing_machine.run_machine(turing_machine);

			std::stringstream buf;
			std::streambuf* oldbuf = std::cout.rdbuf(buf.rdbuf());

			print_machine(turing_machine);
			std::cout.rdbuf(oldbuf);
			std::string output = buf.str();
			std::string expected_output = "-------\nE 0 1 0 \n-------\n";
			Assert::AreEqual(output, expected_output);
			Assert::IsTrue(turing_machine.get_head_position() == 0);
		}
	};
}
