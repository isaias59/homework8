#include "compute_grades.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;

void Student::validate() const {
    if (last_name.empty() || first_name.empty()) {
        throw std::runtime_error("Student name is incomplete.");
    }
    if (quiz.empty()) {
        throw std::runtime_error("Quiz scores are missing.");
    }
    if (hw.empty()) {
        throw std::runtime_error("Homework scores are missing.");
    }
    if (final_score < 0 || final_score > 100) {
        throw std::runtime_error("Final score is out of valid range.");
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

    in >> dummy; // Read the "Quiz" label
    s.quiz.clear(); // Clear any existing quiz scores
    int quiz_score;
    while (in >> quiz_score) { // Read quiz scores
        s.quiz.push_back(quiz_score);
        if (in.peek() == '\n' || in.peek() == 'H') break; // Stop at new line or HW label
    }

    in >> dummy; // Read the "HW" label
    s.hw.clear(); // Clear any existing homework scores
    int hw_score;
    while (in >> hw_score) { // Read homework scores
        s.hw.push_back(hw_score);
        if (in.peek() == '\n' || in.peek() == 'F') break; // Stop at new line or Final label
    }

    in >> dummy >> s.final_score; // Read the "Final" label and the final score

    return in;
}


std::ostream& operator<<(std::ostream& out, const Student& s) {
    out << "Name: " << s.first_name << " " << s.last_name << "\n";
    out << "HW Ave: " << s.hw_avg << "\n";
    out << "QZ Ave: " << s.quiz_avg << "\n";
    out << "Final: " << s.final_score << "\n";
    out << "Total: " << s.course_score << "\n";
    out << "Grade: " << s.course_grade << "\n";
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
