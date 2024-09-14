// Copyright 2024 Maria Surani
#include <gtest/gtest.h>
#include <memory>
#include <sstream>

#include "Department.h"
#include "Course.h"

using namespace std;

class DepartmentUnitTests : public ::testing::Test {
 protected:
  static Department* testDepartment;
  static shared_ptr<Course> testCourse;

  static void SetUpTestSuite() {
    testCourse = make_shared<Course>(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
    testDepartment = new Department("COMS", {{"1001", testCourse}}, "John Doe", 500);
  }

  static void TearDownTestSuite() {
    delete testDepartment;
  }
};

Department* DepartmentUnitTests::testDepartment = nullptr;
shared_ptr<Course> DepartmentUnitTests::testCourse = nullptr;

TEST_F(DepartmentUnitTests, GetNumberOfMajorsTest) {
  ASSERT_EQ(testDepartment->getNumberOfMajors(), 500);
}

TEST_F(DepartmentUnitTests, GetDepartmentChairTest) {
  ASSERT_EQ(testDepartment->getDepartmentChair(), "John Doe");
}

TEST_F(DepartmentUnitTests, GetCourseSelectionTest) {
  auto courses = testDepartment->getCourseSelection();
  ASSERT_EQ(courses.size(), 1);
  ASSERT_EQ(courses["1001"], testCourse);
}

TEST_F(DepartmentUnitTests, AddPersonToMajorTest) {
  int initialMajors = testDepartment->getNumberOfMajors();
  testDepartment->addPersonToMajor();
  ASSERT_EQ(testDepartment->getNumberOfMajors(), initialMajors + 1);
}

TEST_F(DepartmentUnitTests, DropPersonFromMajorTest) {
  testDepartment->addPersonToMajor();  // Increment first
  int initialMajors = testDepartment->getNumberOfMajors();
  testDepartment->dropPersonFromMajor();
  ASSERT_EQ(testDepartment->getNumberOfMajors(), initialMajors - 1);
}

TEST_F(DepartmentUnitTests, AddCourseTest) {
  auto newCourse = make_shared<Course>(100, "Maria Surani", "301 URIS", "10:00-11:00");
  testDepartment->addCourse("2002", newCourse);
  
  auto courses = testDepartment->getCourseSelection();
  ASSERT_EQ(courses.size(), 2);
  ASSERT_EQ(courses["2002"], newCourse);
}

TEST_F(DepartmentUnitTests, CreateCourseTest) {
  testDepartment->createCourse("2003", "Jane Doe", "101 IAB", "2:00-3:00", 150);

  auto courses = testDepartment->getCourseSelection();
  ASSERT_EQ(courses.size(), 3);
  ASSERT_EQ(courses["2003"]->getInstructorName(), "Jane Doe");
}

TEST_F(DepartmentUnitTests, DisplayTest) {
  string expectedResult = "COMS 1001: \nInstructor: Griffin Newbold; Location: 417 IAB; Time: 11:40-12:55\n";
  ASSERT_EQ(testDepartment->display().substr(0, expectedResult.size()), expectedResult);
}

TEST_F(DepartmentUnitTests, SerializeDeserializeTest) {
  stringstream ss;

  // Serialize the department object
  testDepartment->serialize(ss);

  // Create a new department object to deserialize into
  Department deserializedDepartment;
  deserializedDepartment.deserialize(ss);

  // Verify that the deserialized object has the same values
  ASSERT_EQ(deserializedDepartment.getDepartmentChair(), testDepartment->getDepartmentChair());
  ASSERT_EQ(deserializedDepartment.getNumberOfMajors(), testDepartment->getNumberOfMajors());

  auto deserializedCourses = deserializedDepartment.getCourseSelection();
  auto originalCourses = testDepartment->getCourseSelection();
  ASSERT_EQ(deserializedCourses.size(), originalCourses.size());
  ASSERT_EQ(deserializedCourses["1001"]->getInstructorName(), originalCourses["1001"]->getInstructorName());
  ASSERT_EQ(deserializedCourses["1001"]->getCourseLocation(), originalCourses["1001"]->getCourseLocation());
}
