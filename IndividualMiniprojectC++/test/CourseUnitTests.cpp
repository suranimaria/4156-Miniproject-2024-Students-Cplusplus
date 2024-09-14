// Copyright 2024 Maria Surani
#include <gtest/gtest.h>

#include "Course.h"

class CourseUnitTests : public ::testing::Test {
 protected:
  static Course* testCourse;

  static void SetUpTestSuite() {
    testCourse = new Course(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
  }

  static void TearDownTestSuite() { delete testCourse; }
};

Course* CourseUnitTests::testCourse = nullptr;

TEST_F(CourseUnitTests, ToStringTest) {
  std::string expectedResult =
      "\nInstructor: Griffin Newbold; Location: 417 IAB; Time: 11:40-12:55";
  ASSERT_EQ(expectedResult, testCourse->display());
}

TEST_F(CourseUnitTests, EnrollStudentTest) {
  int initialCount = testCourse->getEnrolledStudentCount();
  testCourse->enrollStudent();
  ASSERT_EQ(testCourse->getEnrolledStudentCount(), initialCount + 1);
}

TEST_F(CourseUnitTests, DropStudentTest) {
  testCourse->setEnrolledStudentCount(10);
  int initialCount = testCourse->getEnrolledStudentCount();
  testCourse->dropStudent();
  ASSERT_EQ(testCourse->getEnrolledStudentCount(), initialCount - 1);
}

TEST_F(CourseUnitTests, GetCourseLocationTest) {
  ASSERT_EQ(testCourse->getCourseLocation(), "417 IAB");
}

TEST_F(CourseUnitTests, GetInstructorNameTest) {
  ASSERT_EQ(testCourse->getInstructorName(), "Griffin Newbold");
}

TEST_F(CourseUnitTests, GetCourseTimeSlotTest) {
  ASSERT_EQ(testCourse->getCourseTimeSlot(), "11:40-12:55");
}

TEST_F(CourseUnitTests, ReassignInstructorTest) {
  testCourse->reassignInstructor("Jane Doe");
  ASSERT_EQ(testCourse->getInstructorName(), "Jane Doe");
}

TEST_F(CourseUnitTests, ReassignLocationTest) {
  testCourse->reassignLocation("156 CSP");
  ASSERT_EQ(testCourse->getCourseLocation(), "156 CSP");
}

TEST_F(CourseUnitTests, ReassignTimeTest) {
  testCourse->reassignTime("13:00-14:00");
  ASSERT_EQ(testCourse->getCourseTimeSlot(), "13:00-14:00");
}

TEST_F(CourseUnitTests, SetEnrolledStudentCountTest) {
  testCourse->setEnrolledStudentCount(42);
  ASSERT_EQ(testCourse->getEnrolledStudentCount(), 42);
}

TEST_F(CourseUnitTests, IsCourseFullTest) {
  testCourse->setEnrolledStudentCount(251); 
  ASSERT_TRUE(testCourse->isCourseFull());

  testCourse->setEnrolledStudentCount(0); 
  ASSERT_FALSE(testCourse->isCourseFull());
}

TEST_F(CourseUnitTests, SerializeDeserializeTest) {
  std::stringstream ss;
  testCourse->serialize(ss);

  Course deserializedCourse;
  deserializedCourse.deserialize(ss);

  ASSERT_EQ(deserializedCourse.getInstructorName(), testCourse->getInstructorName());
  ASSERT_EQ(deserializedCourse.getCourseLocation(), testCourse->getCourseLocation());
  ASSERT_EQ(deserializedCourse.getCourseTimeSlot(), testCourse->getCourseTimeSlot());
}
