/*
 * Parker Thompson
 * project2_Thompson_pjt0012.cpp
 * compilation instructions: g++ -o project2_Thompson_pjt0012.cpp
 * Program that simulates a duel between 3 individuals, providing the
 * respective results for both strategy 1 and strategy 2 (with 
 * strategy 2 being superior to strategy 1).
 * 
 * REFERENCES:
 * I used the hints provided by Dr. Li to help me complete this
 * project. 
 * 
 */

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
using namespace std; 


//********************************************
//**************DECLARATIONS******************
//********************************************

//constants 
const int TOTAL_RUNS = 10000;
const int AARON_PROB = 33; 
const int BOB_PROB = 50;

//instance variables
int Aaron_wins1 = 0; //strategy 1 wins 
int Aaron_wins2 = 0; //strategy 2 wins 
int Bob_wins = 0; 
int Charlie_wins = 0; 

//function declarations 
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
void Aaron_shoots1(bool& B_alive, bool& C_alive);
void Bob_shoots(bool& A_alive, bool& C_alive);
void Charlie_shoots(bool& A_alive, bool& B_alive);
void Aaron_shoots2(bool& B_alive, bool& C_alive);
void strategy_1(void);
void strategy_2(void);

//test prototypes declarations 
void test_at_least_two_alive(void);
void test_Aaron_shoots1(void);
void test_Bob_shoots(void);
void test_Charlie_shoots(void);
void test_Aaron_shoots2(void);

//pause function declaration
void Press_any_key(void);


//********************************************
//******************MAIN**********************
//********************************************

int main() {
	cout << "*** Welcome to Thompson's Duel Simulator ***\n";
	cout << fixed << showpoint << setprecision(2);
	srand(time(0));
	
	test_at_least_two_alive();
	Press_any_key();
	test_Aaron_shoots1();
	Press_any_key();
	test_Bob_shoots();
	Press_any_key();
	test_Charlie_shoots();
	Press_any_key();
	test_Aaron_shoots2();
	Press_any_key();

	//strategy 1 
	cout << "Ready to test strategy 1 (run 10,000 times):\n";
	Press_any_key();

	for (int i = 0; i < TOTAL_RUNS; i++) {
		strategy_1();
	}
	cout << "Aaron won " << Aaron_wins1 << "/10000 duels or "
	 	 << (static_cast<float>(Aaron_wins1) / TOTAL_RUNS) * 100
		 << "%\n";
	
	cout << "Bob won " << Bob_wins << "/10000 duels or "
		 << (static_cast<float>(Bob_wins) / TOTAL_RUNS) * 100
		 << "%\n";

	cout << "Charlie won " << Charlie_wins << "/10000 duels or "
		 << (static_cast<float>(Charlie_wins) / TOTAL_RUNS) * 100
		 << "%\n"
		 << endl; 
	

	//strategy 2 (reinitializes Bob and Charlie's wins to 0 beforehand)
	Bob_wins = 0;
	Charlie_wins = 0;
	cout << "Ready to test strategy 2 (run 10,000 times):\n";
	Press_any_key();

	for (int i = 0; i < TOTAL_RUNS; i++) {
		strategy_2();
	}
	cout << "Aaron won " << Aaron_wins2 << "/10000 duels or "
		<< (static_cast<float>(Aaron_wins2) / TOTAL_RUNS) * 100
		<< "%\n";

	cout << "Bob won " << Bob_wins << "/10000 duels or "
		<< (static_cast<float>(Bob_wins) / TOTAL_RUNS) * 100
		<< "%\n";

	cout << "Charlie won " << Charlie_wins << "/10000 duels or "
		<< (static_cast<float>(Charlie_wins) / TOTAL_RUNS) * 100
		<< "%\n"
		<< endl;


	if (Aaron_wins1 > Aaron_wins2) {
		cout << "Strategy 1 is beter than strategy 2.\n";
	}
	else {
		cout << "Strategy 2 is beter than strategy 1.\n";
	}
}


//********************************************
//*************IMPLEMENTATIONS****************
//********************************************

bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
	if (A_alive) {
		if (B_alive || C_alive) {
			return true;
		}
	}
	else if (B_alive && C_alive) {
		return true;
	}
	else {
		return false;
	}
}


void Aaron_shoots1(bool& B_alive, bool& C_alive) {
	int shot_attempt = rand() % 100;
	if (shot_attempt <= AARON_PROB) {
		if (C_alive) {
			C_alive = false; 
		}
		else {
			B_alive = false; 
		}
	}
}


void Bob_shoots(bool& A_alive, bool& C_alive) {
	int shot_attempt = rand() % 100;
	if (shot_attempt <= BOB_PROB) {
		if (C_alive) {
			C_alive = false;
		}
		else {
			A_alive = false;
		}
	}
}


void Charlie_shoots(bool& A_alive, bool& B_alive) {
	if (B_alive) {
		B_alive = false;
	}
	else {
		A_alive = false; 
	}
}


void Aaron_shoots2(bool& B_alive, bool& C_alive) {
	if (!B_alive || !C_alive) {
		int shot_attempt = rand() % 100;
		if (shot_attempt <= AARON_PROB) {
			if (C_alive) {
				C_alive = false;
			}
			else {
				B_alive = false;
			}
		}
	}
}


void strategy_1(void) {
	bool A_alive = true; 
	bool B_alive = true;
	bool C_alive = true;
	while (at_least_two_alive(A_alive, B_alive, C_alive)) {
		if (A_alive) {
			Aaron_shoots1(B_alive, C_alive);
		}
		
		if (B_alive) {
			Bob_shoots(A_alive, C_alive);
		}

		if (C_alive) {
			Charlie_shoots(A_alive, B_alive);
		}
	}
	
	if (A_alive) {
		Aaron_wins1++;
	}
	else if (B_alive) {
		Bob_wins++;
	}
	else {
		Charlie_wins++;
	}
}


void strategy_2(void) {
	bool A_alive = true;
	bool B_alive = true;
	bool C_alive = true;
	while (at_least_two_alive(A_alive, B_alive, C_alive)) {
		if (A_alive) {
			Aaron_shoots2(B_alive, C_alive);
		}

		if (B_alive) {
			Bob_shoots(A_alive, C_alive);
		}

		if (C_alive) {
			Charlie_shoots(A_alive, B_alive);
		}
	}

	if (A_alive) {
		Aaron_wins2++;
	}
	else if (B_alive) {
		Bob_wins++;
	}
	else {
		Charlie_wins++;
	}
}


void test_at_least_two_alive(void) {
	cout << "Unit Testing 1: Function - at_least_two_alive()\n";

	cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(true, true, true));
	cout << "\tCase passed ...\n";

	cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(false, true, true));
	cout << "\tCase passed ...\n";

	cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
	assert(true == at_least_two_alive(true, false, true));
	cout << "\tCase passed ...\n";

	cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
	assert(true == at_least_two_alive(true, true, false));
	cout << "\tCase passed ...\n";

	cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
	assert(false == at_least_two_alive(false, false, true));
	cout << "\tCase passed ...\n";

	cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
	assert(false == at_least_two_alive(false, true, false));
	cout << "\tCase passed ...\n";

	cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(true, false, false));
	cout << "\tCase passed ...\n";

	cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(false, false, false));
	cout << "\tCase passed ...\n";
}


void test_Aaron_shoots1(void) {
	cout << "Unit Testing 2: Function - Aaron_shoots1(B_alive, C_alive)\n";

	bool test_B_alive;
	bool test_C_alive;

	cout << "\tCase 1: Bob alive, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
	test_B_alive = true;
	test_C_alive = true; 
	Aaron_shoots1(test_B_alive, test_C_alive);
	assert(true == test_B_alive);
	
	cout << "\tCase 2: Bob dead, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
	test_B_alive = false;
	test_C_alive = true; 
	Aaron_shoots1(test_B_alive, test_C_alive);
	assert(false == test_B_alive);

	cout << "\tCase 3: Bob alive, Charlie dead\n";
	cout << "\t\tAaron is shooting at Bob\n";
	test_B_alive = true;
	test_C_alive = false;
	Aaron_shoots1(test_B_alive, test_C_alive);
	assert(false == test_C_alive);
}


void test_Bob_shoots(void) {
	cout << "Unit Testing 3: Function - Bob_shoots(A_alive, C_alive)\n";

	bool test_A_alive;
	bool test_C_alive;

	cout << "\tCase 1: Aaron alive, Charlie alive\n";
	cout << "\t\tBob is shooting at Charlie\n";
	test_A_alive = true;
	test_C_alive = true; 
	Bob_shoots(test_A_alive, test_C_alive);
	assert(true == test_A_alive);

	cout << "\tCase 2: Aaron dead, Charlie alive\n";
	cout << "\t\tBob is shooting at Charlie\n";
	test_A_alive = false;
	test_C_alive = true;
	Bob_shoots(test_A_alive, test_C_alive);
	assert(false == test_A_alive);

	cout << "\tCase 3: Aaron alive, Charlie dead\n";
	cout << "\t\tBob is shooting at Aaron\n";
	test_A_alive = true;
	test_C_alive = false;
	Bob_shoots(test_A_alive, test_C_alive);
	assert(false == test_C_alive);
}


void test_Charlie_shoots(void) {
	cout << "Unit Testing 4: Function - Charlie_shoots(A_alive, B_alive)\n";

	bool test_A_alive;
	bool test_B_alive;

	cout << "\tCase 1: Aaron alive, Bob alive\n";
	cout << "\t\tCharlie is shooting at Bob\n";
	test_A_alive = true;
	test_B_alive = true; 
	Charlie_shoots(test_A_alive, test_B_alive);
	assert(true == test_A_alive);

	cout << "\tCase 2: Aaron dead, Bob alive\n";
	cout << "\t\tCharlie is shooting at Bob\n";
	test_A_alive = false;
	test_B_alive = true;
	Charlie_shoots(test_A_alive, test_B_alive);
	assert(false == test_A_alive);

	cout << "\tCase 3: Aaron alive, Bob dead\n";
	cout << "\t\tCharlie is shooting at Aaron\n";
	test_A_alive = true;
	test_B_alive = false;
	Charlie_shoots(test_A_alive, test_B_alive);
	assert(false == test_B_alive);
}


void test_Aaron_shoots2(void) {
	cout << "Unit Testing 5: Function - Aaron_shoots2(B_alive, C_alive)\n";

	bool test_B_alive;
	bool test_C_alive; 

	cout << "\tCase 1: Bob alive, Charlie alive\n";
	cout << "\t\tAaron intentionally misses his first shot\n";
	cout << "\t\tBoth Bob and Charlie are alive\n";
	test_B_alive = true;
	test_C_alive = true; 
	Aaron_shoots2(test_B_alive, test_C_alive);
	assert(true == test_B_alive);
	assert(true == test_C_alive);

	cout << "\tCase 2: Bob dead, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
	test_B_alive = false;
	test_C_alive = true;
	Aaron_shoots2(test_B_alive, test_C_alive);
	assert(false == test_B_alive);

	cout << "\tCase 3: Bob alive, Charlie dead\n";
	cout << "\t\tAaron is shooting at Bob\n";
	test_B_alive = true;
	test_C_alive = false;
	Aaron_shoots2(test_B_alive, test_C_alive);
	assert(false == test_C_alive);
}


void Press_any_key(void) {
	cout << "Press any key to continue...";
	cin.ignore(255, '\n'); //Pause Command for Linux terminal
	cout << "\n";
}