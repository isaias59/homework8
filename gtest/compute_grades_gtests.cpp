#include <gtest/gtest.h>
#include "compute_grades.hpp"
#include <sstream>

TEST(StudentTest, ComputeGrades) {
    Student student;
    
    std::istringstream input("Name: John Doe\nQuiz: 85 90 78\nHW: 80 70 90\nFinal: 88\n");
    input >> student;
    
    student.compute_grades();
    
    EXPECT_NEAR(student.quiz_avg, 86.5, 1e-1);
    EXPECT_NEAR(student.hw_avg, 80.0, 1e-1);
    EXPECT_EQ(student.course_score, 84);
    EXPECT_EQ(student.course_grade, "B");
}

std::string process_student(const std::string& input) {
    Student student;
    std::istringstream input_stream(input);
    input_stream >> student;

    student.compute_grades(); 

    std::ostringstream output_stream;
    output_stream << student;
    return output_stream.str();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
