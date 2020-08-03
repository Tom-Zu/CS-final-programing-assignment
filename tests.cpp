// Authors: Quansen Wang & Tom Zu


#include <iostream>
#include <vector>
#include "movies.h"
#include "tests.h"

using namespace std;

void assertTrue();

int main(int argc, char const *argv[])
{
	Movie b1;

	// if (argc < 1) {
	// 	cerr << "Usage: " << argv[0] << " test number from 1 to 3"
	// }

	// int testNum = argv[1]

	//insert data to b1
	b1.insert("m1",1.0);
    b1.insert("m2",2.0);
    b1.insert("m3",3.0);
    b1.insert("m4",4.0);
    b1.insert("m5",5.0);
    b1.insert("m6",6.0);
    b1.insert("m7",7.0);
    b1.insert("m8",8.0);
    b1.insert("m9",9.0);

    cout << "PreOrder printing test begins" << endl;
    b1.printPreOrder();
    cout << endl;

    cout << "Insert Function test begins";
    cout << endl;
    cout << "Before the insert: " << endl;
    b1.printPreOrder();
    b1.insert("testName1", 5.0);
    b1.insert("testName2", 6.0);
    cout << "After the insert" << endl;
    b1.printPreOrder();

    cout << "Find the best movie test begins" << endl;
    cout << "Expected expression: \"Best movie is m9 with rating 9\"" << endl;
    cout << "Actual expression: " << endl;
    b1.findHighestRating("m");
    cout << endl;

	return 0;
}