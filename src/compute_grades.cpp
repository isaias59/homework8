#include "compute_grades.hpp"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <stdexcept>

double compute_average(const std::vector<int>& scores) {
    if (scores.empty()) return 0.0;
    return std::accumulate(scores.begin(), scores.end(), 0.0) / scores.size();
}

void Student::validate() const {
    auto validate_score = [](int score) {
        if (score < 0 || score > 100) {
            throw std::domain_error("Error: invalid percentage " + std::to_string(score));
        }
        };

    for (int score : quiz) validate_score(score);
    for (int score : hw) validate_score(score);
    validate_score(static_cast<int>(final_score));
}

void Student::compute_quiz_avg() {
    if (quiz.size() > 1) {
        auto min_it = std::min_element(quiz.begin(), quiz.end());
        quiz.erase(min_it);
    }
    quiz_avg = compute_average(quiz);
}

void Student::compute_hw_avg() {
    hw_avg = compute_average(hw);
}

void Student::compute_course_score() {
    course_score = static_cast<int>(0.4 * quiz_avg + 0.3 * hw_avg + 0.3 * final_score + 0.5);
}

void Student::compute_course_grade() {
    if (course_score >= 97) course_grade = "A+";
    else if (course_score >= 93) course_grade = "A";
    else if (course_score >= 90) course_grade = "A-";
    else if (course_score >= 87) course_grade = "B+";
    else if (course_score >= 83) course_grade = "B";
    else if (course_score >= 80) course_grade = "B-";
    else if (course_score >= 77) course_grade = "C+";
    else if (course_score >= 73) course_grade = "C";
    else if (course_score >= 70) course_grade = "C-";
    else if (course_score >= 67) course_grade = "D+";
    else if (course_score >= 63) course_grade = "D";
    else if (course_score >= 60) course_grade = "D-";
    else course_grade = "F";
}

void Student::compute_grades() {
    compute_quiz_avg();
    compute_hw_avg();
    compute_course_score();
    compute_course_grade();
}

std::strong_ordering Student::operator<=>(const Student& other) const {
    return std::tie(last_name, first_name) <=> std::tie(other.last_name, other.first_name);
}

bool Student::operator==(const Student& other) const {
    return std::tie(last_name, first_name) == std::tie(other.last_name, other.first_name);
}

std::istream& operator>>(std::istream& in, Student& s) {
    std::string keyword;
    while (in >> keyword) {
        if (keyword == "Name:") {
            in >> s.first_name;
            in >> std::ws;
            std::getline(in, s.last_name);
        }
        else if (keyword == "Quiz:") {
            int score;
            while (in >> score) {
                s.quiz.push_back(score);
            }
            in.clear();
        }
        else if (keyword == "HW:") {
            int score;
            while (in >> score) {
                s.hw.push_back(score);
            }
            in.clear();
        }
        else if (keyword == "Final:") {
            in >> s.final_score;
        }
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (in.peek() == '\n') break;
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Student& s) {
    out << "Name: " << s.first_name << " " << s.last_name << "\n";
    out << "HW Ave: " << s.hw_avg << "\n";
    out << "QZ Ave: " << s.quiz_avg << "\n";
    out << "Final: " << s.final_score << "\n";
    out << "Total: " << s.course_score << "\n";
    out << "Grade: " << s.course_grade << "\n\n";
    return out;
}

void Gradebook::compute_grades() {
    for (auto& student : students) {
        student.compute_grades();
    }
}

void Gradebook::sort() {
    std::ranges::sort(students);
}

void Gradebook::validate() const {
    for (const auto& student : students) {
        student.validate();
    }
}

std::istream& operator>>(std::istream& in, Gradebook& b) {
    Student s;
    while (in >> s) {
        b.students.push_back(s);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Gradebook& b) {
    for (const auto& student : b.students) {
        out << student;
    }
    return out;
}

