/* STUDENTS: YOU MUST ADD YOUR PASSENGER UNIT TESTS TO THIS FILE. FORMAT YOUR
 * TESTS TO FIT THE SPECIFICATIONS GIVEN BY THE TESTS PROVIDED IN THIS FILE.
 *
 * Please note, the assessment tests for grading, will use the same include
 * files, class names, and function names for accessing students' code that you
 * find in this file.  So students, if you write your code so that it passes
 * these feedback tests, you can be assured that the auto-grader will at least
 * be able to properly link with your code.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/passenger.h"
#include "../src/route.h"
#include "../src/stop.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class PassengerTests : public ::testing::Test {

	protected:
  	Passenger* passenger;
		Passenger* passenger2;
	virtual void SetUp() {
    	passenger = new Passenger();
			passenger2 = new Passenger(30, "Brandon");
  	}

  	virtual void TearDown() {
    	delete passenger;
			delete passenger2;
  	}

};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(PassengerTests, IsOnbus) {
  	EXPECT_EQ(passenger->IsOnBus(), false);
  	passenger->GetOnBus();
  	EXPECT_EQ(passenger->IsOnBus(), true);
};
TEST_F(PassengerTests, Update1 ) {
  	EXPECT_EQ(passenger->GetTotalWait(), 0);
  	passenger->Update();
  	EXPECT_EQ(passenger->GetTotalWait(), 1);
};
TEST_F(PassengerTests, Update2) {
  	EXPECT_EQ(passenger->IsOnBus(), false);
  	passenger->GetOnBus();
  	EXPECT_EQ(passenger->IsOnBus(), true);
		passenger->Update();
		EXPECT_EQ(passenger->GetTotalWait(),1);
};
TEST_F(PassengerTests, GetDestination) {
		EXPECT_EQ(passenger2->GetDestination(), 30);
};
TEST_F(PassengerTests, Report1) {
	testing::internal::CaptureStdout();
	passenger2->Report(std::cout);
	std::string output1 = testing::internal::GetCapturedStdout();
	std::string expected1 = "Name: Brandon\n";
	expected1.append("Destination: 30\n");
	expected1.append("Total Wait: 0\n");
	expected1.append("\tWait at Stop: 0\n");
	expected1.append("\tTime on bus: 0\n");
	EXPECT_EQ(output1, expected1);

	testing::internal::CaptureStdout();
	passenger2->Update();
	passenger2->Report(std::cout);
	std::string output2 = testing::internal::GetCapturedStdout();
	std::string expected2 = "Name: Brandon\n";
	expected2.append("Destination: 30\n");
	expected2.append("Total Wait: 1\n");
	expected2.append("\tWait at Stop: 1\n");
	expected2.append("\tTime on bus: 0\n");
	EXPECT_EQ(output2, expected2);
}
TEST_F(PassengerTests, Report2) {
		testing::internal::CaptureStdout();
		passenger2->Update();
		passenger2->GetOnBus();
		passenger2->Update();
		passenger2->Report(std::cout);
		std::string output3 = testing::internal::GetCapturedStdout();
		std::string expected3 = "Name: Brandon\n";
		expected3.append("Destination: 30\n");
		expected3.append("Total Wait: 2\n");
		expected3.append("\tWait at Stop: 1\n");
		expected3.append("\tTime on bus: 1\n");
		EXPECT_EQ(output3, expected3);
};
TEST_F(PassengerTests, Report3) {
		testing::internal::CaptureStdout();
		passenger2->Update();
		passenger2->GetOnBus();
		passenger2->Update();
		passenger2->Update();
		passenger2->Update();
		passenger2->Report(std::cout);
		std::string output4 = testing::internal::GetCapturedStdout();
		std::string expected4 = "Name: Brandon\n";
		expected4.append("Destination: 30\n");
		expected4.append("Total Wait: 4\n");
		expected4.append("\tWait at Stop: 1\n");
		expected4.append("\tTime on bus: 3\n");
		EXPECT_EQ(output4, expected4);
};
TEST_F(PassengerTests, GETONBUS) {
		passenger2->GetOnBus();
		EXPECT_EQ(passenger2->GetTotalWait(),0);
};
