// Copyright 2024 Maria Surani
#include <gtest/gtest.h>

#include "Course.h"

class CourseUnitTests : public ::testing::Test {
 protected:
  static Course* course;

  static void SetUpTestSuite() {
    course = new Course(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
  }

  static void TearDownTestSuite() { delete course; }
};

Course* CourseUnitTests::course = nullptr;

TEST_F(CourseUnitTests, ToStringTest) {
  std::string expectedResult =
      "\nInstructor: Griffin Newbold; Location: 417 IAB; Time: 11:40-12:55";
  ASSERT_EQ(expectedResult, course->display());
}

TEST_F(CourseUnitTests, EnrollStudentTest) {
  course->setEnrolledStudentCount(249);
  course->enrollStudent();
  ASSERT_TRUE(course->isCourseFull());
}

TEST_F(CourseUnitTests, DropStudentTest) {
  course->setEnrolledStudentCount(250);
  course->dropStudent();
  ASSERT_FALSE(course->isCourseFull());
}

TEST_F(CourseUnitTests, GetCourseLocationTest) {
  ASSERT_EQ(course->getCourseLocation(), "417 IAB");
}

TEST_F(CourseUnitTests, GetInstructorNameTest) {
  ASSERT_EQ(course->getInstructorName(), "Griffin Newbold");
}

TEST_F(CourseUnitTests, GetCourseTimeSlotTest) {
  ASSERT_EQ(course->getCourseTimeSlot(), "11:40-12:55");
}

TEST_F(CourseUnitTests, ReassignInstructorTest) {
  course->reassignInstructor("Jane Doe");
  ASSERT_EQ(course->getInstructorName(), "Jane Doe");
}

TEST_F(CourseUnitTests, ReassignLocationTest) {
  course->reassignLocation("156 CSP");
  ASSERT_EQ(course->getCourseLocation(), "156 CSP");
}

TEST_F(CourseUnitTests, ReassignTimeTest) {
  course->reassignTime("13:00-14:00");
  ASSERT_EQ(course->getCourseTimeSlot(), "13:00-14:00");
}

TEST_F(CourseUnitTests, IsCourseFullTest) {
  course->setEnrolledStudentCount(251); 
  ASSERT_TRUE(course->isCourseFull());

  course->setEnrolledStudentCount(0); 
  ASSERT_FALSE(course->isCourseFull());
}

TEST_F(CourseUnitTests, SerializeDeserializeTest) {
  std::stringstream ss;
  course->serialize(ss);

  Course deserializedCourse;
  deserializedCourse.deserialize(ss);

  ASSERT_EQ(deserializedCourse.getInstructorName(), course->getInstructorName());
  ASSERT_EQ(deserializedCourse.getCourseLocation(), course->getCourseLocation());
  ASSERT_EQ(deserializedCourse.getCourseTimeSlot(), course->getCourseTimeSlot());
}
