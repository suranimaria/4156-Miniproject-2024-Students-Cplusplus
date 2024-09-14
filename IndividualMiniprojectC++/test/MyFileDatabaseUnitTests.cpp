// Copyright 2024 Maria Surani
#include "MyFileDatabase.h"
#include <gtest/gtest.h>

void SetUpDatabase(MyFileDatabase& db, std::shared_ptr<Course>& course) {
    course = std::make_shared<Course>(5, "Jane Doe", "100 CSP", "2:40-3:55");
    course->setEnrolledStudentCount(3);

    std::map<std::string, std::shared_ptr<Course>> coursesList = {{"156", course}};
    
    Department dept("CS", coursesList, "Joe Doe", 3000);
    std::map<std::string, Department> mapping = {{"CS", dept}};

    db.setMapping(mapping);
}

TEST(MyFileDatabaseUnitTests, SerializationTest) {
    MyFileDatabase db {1, "test.bin"};
    std::shared_ptr<Course> originalCourse;
    SetUpDatabase(db, originalCourse); 
    db.saveContentsToFile();

    MyFileDatabase deserializedDB {0, "test.bin"};
    auto mappingDeserialized = deserializedDB.getDepartmentMapping();

    EXPECT_EQ(mappingDeserialized.size(), 1);
    ASSERT_TRUE(mappingDeserialized.find("CS") != mappingDeserialized.end());

    const Department& deptDeserialized = mappingDeserialized.at("CS");
    EXPECT_EQ(deptDeserialized.getDepartmentChair(), "Joe Doe");
    EXPECT_EQ(deptDeserialized.getNumberOfMajors(), 3000);

    auto deserialized_courses = deptDeserialized.getCourseSelection();
    EXPECT_EQ(deserialized_courses.size(), 1);

    auto deserialized_course = deserialized_courses.at("156");

    EXPECT_EQ(deserialized_course->getInstructorName(), originalCourse->getInstructorName());
    EXPECT_EQ(deserialized_course->getCourseLocation(), originalCourse->getCourseLocation());
    EXPECT_EQ(deserialized_course->getCourseTimeSlot(), originalCourse->getCourseTimeSlot());
}

TEST(MyFileDatabaseUnitTests, DisplayTest) {
    MyFileDatabase db {1, "test.bin"};
    std::shared_ptr<Course> dummyCourse;
    SetUpDatabase(db, dummyCourse); 

    std::string expected = 
    "For the CS department:\n"
    "CS 156: \n"
    "Instructor: Jane Doe; Location: 100 CSP; Time: 2:40-3:55\n\n";
    
    EXPECT_EQ(db.display(), expected);
}
