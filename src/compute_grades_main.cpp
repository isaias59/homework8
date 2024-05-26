#include <fstream>
#include "compute_grades.hpp"

using namespace std;

int main()
{
	cout << "\nHey";
	ifstream gradebook{ "gradebook.txt" };
	cout << "\nHey";

	Gradebook b;
	gradebook >> b;

	b.validate();
	b.compute_grades();
	b.sort();

	ofstream course_grades{ "course_grades.txt" };
	course_grades << b;
}
