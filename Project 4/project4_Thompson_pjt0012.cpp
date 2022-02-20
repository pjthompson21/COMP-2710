/**
 * Parker Thompson
 * project4_Thompson_pjt0012.cpp 
 * compilation instructions: g++ project4_Thompson_pjt0012.cpp
 *                           ./a.out
 * 
 * REFERENCES:
 * I utilized the hints provided by Dr. Li to help me 
 * complete this assignment. 
 * 
 **/

#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <assert.h>
using namespace std;


//********************************************
//**************STRUCTURE*********************
//********************************************

struct trivia_node {
    string question;
    string answer; 
    int point; 
    trivia_node* next; 
};

//creates pointer to triva_node 
typedef trivia_node* ptr_node; 



//********************************************
//**************DECLARATIONS******************
//********************************************

//function declarations 
void init_question_list(ptr_node&);
void add_question(ptr_node&);
int ask_question(ptr_node, int);
void Unit_test();
void clear();

//instance variables 
int num_of_questions;
int point_total = 0;



//********************************************
//******************MAIN**********************
//********************************************

#define UNIT_TESTING
//#define trivia_quiz

int main() {
    ptr_node node_list = new trivia_node; 
    string user_response = "y";

#ifdef trivia_quiz
    init_question_list(node_list);

    cout << "*** Welcome to Thompson's trivia quiz game! ***\n";

    while (user_response == "y" || user_response == "Y") {
        add_question(node_list);
        cout << "Continue? (y/n): ";
        cin >> user_response;
        clear();
    }
    

    ask_question(node_list, num_of_questions);
    cout << "*** Thank you for playing! Goodbye ***";
    return 0;

#endif

//Method for testing
#ifdef UNIT_TESTING 
    Unit_test();
    return 0;
#endif
}



//********************************************
//*************IMPLEMENTATIONS****************
//********************************************

void init_question_list(ptr_node& q_list) {
    ptr_node cur_ptr = new trivia_node;
    cur_ptr->question = "How long was the shortest war on record?";
    cur_ptr->answer = "38";
    cur_ptr->point = 100;
    cur_ptr->next = new trivia_node;
    q_list = cur_ptr;

    cur_ptr = q_list->next;
    cur_ptr->question = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
    cur_ptr->answer = "Bank of Italy";
    cur_ptr->point = 50;
    cur_ptr->next = new trivia_node;
    
    cur_ptr = cur_ptr->next;
    cur_ptr->question = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)";
    cur_ptr->answer = "Wii Sports"; 
    cur_ptr->point = 20;
    cur_ptr->next = NULL;

    num_of_questions = 3;
}



void add_question(ptr_node& q_list) { 
    ptr_node new_ptr = new trivia_node;

    cout << "Enter a question: ";
    getline(cin, new_ptr->question);

    cout << "Enter an answer: ";
    getline(cin, new_ptr->answer);

    cout << "Enter points awarded: ";
    cin >> new_ptr->point;

    new_ptr->next = q_list;
    q_list = new_ptr;
    num_of_questions++;
}


int ask_question(ptr_node q_list, int num_ask) {
    ptr_node cur_ptr = new trivia_node;
    string user_answer;
    cur_ptr = q_list;

    if (q_list == NULL) {
        return 0;
    }
    
    if (num_ask < 1) {
        cout << "Warning - The number of trivia to be asked must be "
             << "equal to or greater than 1.";
        return 1;
    } 
    else if (num_of_questions < num_ask) {
        cout << "Warning - There is only " << num_of_questions
             << " trivia in the question list.";
        return 1;
    }
    else {
        cout << "\n";
        for (int i = 0; i < num_ask; i++) {
            cout << "Question: " << cur_ptr->question << endl;
            cout << "Answer: "; 
            getline(cin, user_answer);
            if (user_answer.compare(cur_ptr->answer) == 0) {
                cout << "Correct! Points awarded: "
                     << cur_ptr->point << "\n";
                point_total += cur_ptr->point;

                cout << "Total points: " << point_total << endl;
            }
            else {
                cout << "Incorrect. Correct answer is "
                     << cur_ptr->answer << endl;
                
                cout << "Total points " << point_total << endl;
            }

            cur_ptr = cur_ptr->next;
            clear();
        }
    }
    return 0;
}


void Unit_test() {
    ptr_node node_list = new trivia_node;
    init_question_list(node_list);

    cout << "*** This is a debugging version ***" << endl;
    cout << "Unit Test Case 1: Ask no question. "
         << "The program should give a warning message. "
         << endl;
    assert(ask_question(node_list, 0) == 1);
    cout << "\nCase 1 Passed\n\n";

    cout << "Unit Test Case 2.1: Ask 1 question in the linked list. "
         << "The tester enters an incorrect answer."
         << endl;
    ask_question(node_list, 1);
    assert(point_total == 0);
    cout << "Case 2.1 Passed\n\n"; 

    cout << "Unit Test Case 2.2: Ask 1 question in the linked list. "
         << "The tester enters the correct answer."
         << endl;
    ask_question(node_list, 1);
    assert(point_total == 100);
    cout << "Case 2.2 Passed\n\n";
    point_total = 0;

    cout << "Unit Test Case 3: Ask all the questions of the last trivia in the linked list."
         << endl; 
    ask_question(node_list, 3);
    assert(num_of_questions == 3);
    cout << "Case 3 Passed\n\n";

    cout << "Unit Test Case 4: Ask 5 questions in the linked list."
         << endl;
    int num_ask = 5;
    assert(ask_question(node_list, num_ask) == 1);
    cout << "\nCase 4 Passed\n\n";

    cout << "*** End of debugging version ***" << endl;
}

void clear() {
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}