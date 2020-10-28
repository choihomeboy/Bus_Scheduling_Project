
#include <gtest/gtest.h>
#include "../src/bus.h"
#include "../src/passenger.h"
#include "../src/route.h"
#include "../src/stop.h"
#include "../src/random_passenger_generator.h"
class AllTests : public ::testing::Test {

	protected:
		Bus * bus1;
		Passenger* passenger1;
		Passenger* passenger2;
		Stop * stop_CC_EB_1;
		Stop * stop_CC_EB_2;
		Stop * stop_CC_EB_3;
		Stop * stop_CC_EB_4;
		Stop * stop_CC_WB_1;
		Stop * stop_CC_WB_2;
		Stop * stop_CC_WB_3;
		Stop * stop_CC_WB_4;
		Stop ** CC_EB_stops = new Stop *[4];
	  Stop ** CC_WB_stops = new Stop *[4];
	  std::list<Stop *> CC_EB_stops_list;
	  std::list<Stop *> CC_WB_stops_list;

		double * CC_EB_distances = new double[3];
		double * CC_WB_distances = new double[3];

		std::list<double> CC_EB_probs;  // realistic .15, .3, .025, .05, .05, 0
		std::list<double> CC_WB_probs;  // realistic .35, .05, .01, .01, .2, 0

		RandomPassengerGenerator * CC_EB_generator;
		RandomPassengerGenerator * CC_WB_generator;

		Route * CC_EB;
		Route * CC_WB;
	virtual void SetUp() {
  	passenger1 = new Passenger(21, "Yongwoo");
		passenger2 = new Passenger(30, "Brandon");
		//   West bank station
	  stop_CC_EB_1 = new Stop(0, 44.972392, -93.243774);
	  //   student union station
	  stop_CC_EB_2 = new Stop(1, 44.973580, -93.235071);
	  //   Oak St & Washington Ave
	  stop_CC_EB_3 = new Stop(2, 44.975392, -93.226632);
	  //   before transit
	  stop_CC_EB_4 = new Stop(3, 44.975837, -93.222174);

		//   SPSC
		stop_CC_WB_1 = new Stop(4, 44.984630, -93.186352);
		//   Buford & Gartner
		stop_CC_WB_2 = new Stop(5, 44.984482, -93.181657);
		//   Fairgrounds
		stop_CC_WB_3 = new Stop(6, 44.983703, -93.178846);
		//   Tway
		stop_CC_WB_4 = new Stop(7, 44.980663, -93.180808);

		CC_EB_stops_list.push_back(stop_CC_EB_1);
		CC_EB_stops[0] = stop_CC_EB_1;
		CC_EB_stops_list.push_back(stop_CC_EB_2);
		CC_EB_stops[1] = stop_CC_EB_2;
		CC_EB_stops_list.push_back(stop_CC_EB_3);
		CC_EB_stops[2] = stop_CC_EB_3;
		CC_EB_stops_list.push_back(stop_CC_EB_4);
		CC_EB_stops[3] = stop_CC_EB_4;

		CC_WB_stops_list.push_back(stop_CC_WB_1);
		CC_WB_stops[0] = stop_CC_WB_1;
		CC_WB_stops_list.push_back(stop_CC_WB_2);
		CC_WB_stops[1] = stop_CC_WB_2;
		CC_WB_stops_list.push_back(stop_CC_WB_3);
		CC_WB_stops[2] = stop_CC_WB_3;
		CC_WB_stops_list.push_back(stop_CC_WB_4);
		CC_WB_stops[3] = stop_CC_WB_4;



	  CC_EB_distances[0] = 4;
	  CC_EB_distances[1] = 4;
	  CC_EB_distances[2] = 2;

		CC_WB_distances[0] = 2;
		CC_WB_distances[1] = 1;
		CC_WB_distances[2] = 2;

		CC_EB_probs.push_back(.9);   // WB
		CC_EB_probs.push_back(.9);    // CMU
		CC_EB_probs.push_back(.9);  // O&W
		CC_EB_probs.push_back(.9);   // Pre-transit

		CC_WB_probs.push_back(.35);     // SPSC
		CC_WB_probs.push_back(.05);     // Buford
		CC_WB_probs.push_back(.01);     // State fair
		CC_WB_probs.push_back(.01);     // post-transit

		CC_EB_generator= new RandomPassengerGenerator(CC_EB_probs, CC_EB_stops_list);
		CC_WB_generator = new RandomPassengerGenerator(CC_WB_probs, CC_WB_stops_list);

    CC_EB = new Route("Campus Connector - Eastbound", CC_EB_stops,
															CC_EB_distances, 4, CC_EB_generator);
		CC_WB = new Route("Campus Connector - Westbound", CC_WB_stops,
															CC_WB_distances, 4, CC_WB_generator);

	}

  	virtual void TearDown() {
    	delete passenger1;
			delete passenger2;
			delete CC_EB;
			delete CC_WB;
  	}

};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

 TEST_F(AllTests, Stop) {
   	EXPECT_EQ(stop_CC_EB_1->AddPassengers(passenger1), 1);
   	std::list<Passenger *> temp = stop_CC_EB_1->GetPassengers();
		EXPECT_EQ(temp.front(), passenger1);
		// After Loading, no passenger left at the stop
		stop_CC_EB_1->LoadPassenger();
   	EXPECT_EQ(stop_CC_EB_1->GetPassengers().size(), 0);
		// Adding same person one more time at the stop is possible
		stop_CC_EB_1->AddPassengers(passenger1);
		stop_CC_EB_1->AddPassengers(passenger1);
		EXPECT_EQ(stop_CC_EB_1->GetPassengers().size(), 2);
		//Getters
		EXPECT_EQ(stop_CC_EB_1->GetId(), 0);
		EXPECT_EQ(stop_CC_EB_1->GetLongitude(), 44.972392);
		EXPECT_EQ(stop_CC_EB_1->GetLatitude(), -93.243774);
 };

 TEST_F(AllTests, Route) {
	  // Check clone
	  EXPECT_EQ(CC_EB->Clone()->GetDestinationStop(),CC_EB->GetDestinationStop());
	  EXPECT_EQ(CC_EB->Clone()->GetName(),CC_EB->GetName());
	  EXPECT_EQ(CC_EB->Clone()->GetStops(),CC_EB->GetStops());
	  EXPECT_EQ(CC_EB->Clone()->GetDestinationStop(),CC_EB -> GetDestinationStop());
		// Getters
		// Destination stop is second stop at the beginning
		EXPECT_EQ(CC_EB->GetDestinationStop()->GetId(), stop_CC_EB_1->GetId());
		// Changing destination stop
		CC_EB->NextStop();
		EXPECT_EQ(CC_EB->GetDestinationStop()->GetId(), stop_CC_EB_2->GetId());
		EXPECT_EQ(CC_EB->GetName(),"Campus Connector - Eastbound");
		EXPECT_EQ(CC_EB->GetRouteData().id, CC_EB->GetName());
		double temp_dist_left = CC_EB->GetDistanceLeft();
		CC_EB->SetTransitDistance();
		EXPECT_EQ(temp_dist_left > CC_EB->GetDistanceLeft(), true);
		// route update is done in bus update
 };

 TEST_F(AllTests, Bus) {
	 bus1 = new Bus("10000",CC_EB->Clone(),CC_WB->Clone(),10,1);
	 EXPECT_EQ(bus1->GetNumPassengers(),0);
	 bus1->LoadPassenger(passenger1);
	 EXPECT_EQ(bus1->GetNumPassengers(),1);
	 EXPECT_EQ(bus1->LoadPassenger(passenger1),true);
	 EXPECT_EQ(bus1->LoadPassenger(passenger1),true);
	 EXPECT_EQ(bus1->LoadPassenger(passenger1),true);
	 EXPECT_EQ(bus1->LoadPassenger(passenger1),true);
	 EXPECT_EQ(bus1->LoadPassenger(passenger1),true);
	 EXPECT_EQ(bus1->LoadPassenger(passenger1),true);
	 EXPECT_EQ(bus1->LoadPassenger(passenger1),true);
	 EXPECT_EQ(bus1->LoadPassenger(passenger1),true);
	 EXPECT_EQ(bus1->LoadPassenger(passenger1),true);
	 EXPECT_EQ(bus1->GetNumPassengers(),10);
	 for (int i=0; i<50; i++) {
		 bus1->LoadPassenger(passenger1);
	 }
	 EXPECT_EQ(bus1->LoadPassenger(passenger1),false);
	 EXPECT_EQ(bus1->LoadPassenger(passenger1),false);
	 bus1->UnloadPassenger(9);
	 bus1->UnloadPassenger(8);
	 bus1->UnloadPassenger(7);
	 bus1->UnloadPassenger(6);
	 bus1->UnloadPassenger(5);
	 bus1->UnloadPassenger(4);
	 bus1->UnloadPassenger(3);
	 bus1->UnloadPassenger(2);
	 bus1->UnloadPassenger(1);
	 int sum1=0;
	 int sum2=0;
	 std::list<Passenger *> temp_pass = bus1->GetPassengers();
	 for(std::list<Passenger *>::iterator it = temp_pass.begin();
 				it != temp_pass.end(); it++){
					sum1+=(*it)->GetTotalWait();
				}
	 bus1->Update();
	 std::list<Passenger *> temp_pass2 = bus1->GetPassengers();

	 for(std::list<Passenger *>::iterator it = temp_pass2.begin();
					it != temp_pass2.end(); it++){
						sum2+=(*it)->GetTotalWait();
					}
	 EXPECT_EQ(sum2,sum1+temp_pass.size());

	 // getters
	 BusData temp_busdata = bus1->GetBusData();
	 EXPECT_EQ(temp_busdata.id, bus1->GetName());
	 EXPECT_EQ(bus1->GetNextStop(), stop_CC_EB_2);
	 EXPECT_EQ(bus1->GetNumPassengers(), 1);
	 EXPECT_EQ(bus1->GetCapacity(), 10);
 };
