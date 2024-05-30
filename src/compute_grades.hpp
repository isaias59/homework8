#ifndef COMUPTER_GRADES_HPP
#define COMPUTER_GRADES_HPP

#include <compare>
#include <iosfwd>
#include <string>
#include <vector>
#include<iomanip>

class Student {
public:
	void validate() const;
	void compute_grade();

	std::strong_ordering operator <=> (const Student& other) const;
	bool operator == (const Student& other)const;

	friend std::istream& operator>>(std::istream& in, Student& s);
	friend std::ostream& operator<<(std::ostream& out, const Student& s);

private:
	//these are read in
	std::string last_name = "Name";
	std::string first_name = "Missing";
	std::vector<int> quiz;
	std::vector<int> hw;
	double final_score = 0.0;

	//these are computed
	double quiz_avg;
	double hw_avg;
	int course_score;
	std::string course_grade;

	void compute_quiz_avg();
	void compute_hw_avg();
	void compute_course_score();

};

class Gradebook {
public:
	void compute_grades();
	void sort();
	void validate()const;

	friend std::istream& operator>>(std::istream& in, Gradebook& b);
	friend std::ostream& operator<<(std::ostream& out, const Gradebook& b);

private:
	std::vector<Student> students;
};

#endif
