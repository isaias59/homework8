#include "compute_grades.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;

void Student::validate() const {
    if (last_name == "Name" || first_name == "Missing" || quiz.empty() || hw.empty()) {
        throw std::runtime_error("Student data is incomplete or invalid.");
    }
}


void Student::compute_quiz_avg() {
    if (!quiz.empty()) {
        quiz_avg = accumulate(quiz.begin(), quiz.end(), 0.0) / quiz.size();
    }
    else {
        quiz_avg = 0.0;
    }
}

void Student::compute_hw_avg() {
    if (!hw.empty()) {
        hw_avg = accumulate(hw.begin(), hw.end(), 0.0) / hw.size();
    }
    else {
        hw_avg = 0.0;
    }
}

void Student::compute_course_score() {
    compute_quiz_avg();
    compute_hw_avg();
    course_score = static_cast<int>(0.4 * hw_avg + 0.6 * quiz_avg);
}

void Student::compute_grade() {
    compute_course_score();
    if (course_score >= 90) {
        course_grade = "A";
    }
    else if (course_score >= 80) {
        course_grade = "B";
    }
    else if (course_score >= 70) {
        course_grade = "C";
    }
    else if (course_score >= 60) {
        course_grade = "D";
    }
    else {
        course_grade = "F";
    }
}

std::strong_ordering Student::operator<=>(const Student& other) const {
    return last_name <=> other.last_name;
}

bool Student::operator==(const Student& other) const {
    return last_name == other.last_name && first_name == other.first_name;
}

std::istream& operator>>(std::istream& in, Student& s) {
    string dummy;
    in >> dummy >> s.last_name >> s.first_name;

    in >> dummy; // Quiz
    int quiz_score;
    while (in >> quiz_score) {
        s.quiz.push_back(quiz_score);
        if (in.peek() == '\n') break;
    }

    in >> dummy; // HW
    int hw_score;
    while (in >> hw_score) {
        s.hw.push_back(hw_score);
        if (in.peek() == '\n') break;
    }

    in >> dummy >> s.final_score; // Final

    return in;
}

std::ostream& operator<<(std::ostream& out, const Student& s) {
    out << s.last_name << ", " << s.first_name << " - "
        << "Quizzes: " << s.quiz_avg << ", "
        << "HW: " << s.hw_avg << ", "
        << "Final Score: " << s.course_score << ", "
        << "Grade: " << s.course_grade;
    return out;
}

void Gradebook::compute_grades() {
    for (Student& student : students) {
        student.compute_grade();
    }
}

void Gradebook::sort() {
    std::sort(students.begin(), students.end());
}

void Gradebook::validate() const {
    for (const Student& student : students) {
        student.validate();
    }
}

std::istream& operator>>(std::istream& in, Gradebook& b) {
    Student student;
    while (in >> student) {
        b.students.push_back(student);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Gradebook& b) {
    for (const Student& student : b.students) {
        out << student << "\n";
    }
    return out;
}
