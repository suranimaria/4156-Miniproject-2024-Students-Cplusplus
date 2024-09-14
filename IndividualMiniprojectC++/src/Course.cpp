// Copyright 2024 Maria Surani
#include "Course.h"

#include <iostream>
#include <string>

/**
 * Constructs a new Course object with the given parameters. Initial count
 * starts at 0.
 *
 * @param instructorName     The name of the instructor teaching the course.
 * @param courseLocation     The location where the course is held.
 * @param timeSlot           The time slot of the course.
 * @param capacity           The maximum number of students that can enroll in
 * the course.
 */
Course::Course(int capacity, const std::string& instructorName,
               const std::string& courseLocation, const std::string& timeSlot)
    : enrollmentCapacity(capacity),
      enrolledStudentCount(0),
      courseLocation(courseLocation),
      instructorName(instructorName),
      courseTimeSlot(timeSlot) {}

/**
 * Constructs a default Course object with the default parameters.
 *
 */
Course::Course()
    : enrollmentCapacity(0),
      enrolledStudentCount(0),
      courseLocation(""),
      instructorName(""),
      courseTimeSlot("") {}

/**
 * Enrolls a student in the course if there is space available.
 *
 * @return true if the student is successfully enrolled, false otherwise.
 */
bool Course::enrollStudent() {
  if (enrolledStudentCount >= enrollmentCapacity) return false;
  enrolledStudentCount++;
  return false;
}

/**
 * Drops a student from the course if a student is enrolled.
 *
 * @return true if the student is successfully dropped, false otherwise.
 */
bool Course::dropStudent() {
  if (enrolledStudentCount == 0) return false;
  enrolledStudentCount--;
  return true;
}

/**
 * Gets the course location.
 *
 * @return string representing the course location.
 */
std::string Course::getCourseLocation() const { return courseLocation; }

/**
 * Gets the instructor's name.
 *
 * @return string representing the instructor's name.
 */
std::string Course::getInstructorName() const { return instructorName; }

/**
 * Gets the time slot for the course.
 *
 * @return string representing the time slot of the course.
 */
std::string Course::getCourseTimeSlot() const { return courseTimeSlot; }

/**
 * Displays the course information in a string format.
 *
 * @return string with course details including instructor name, location, and
 * time slot.
 */
std::string Course::display() const {
  return "\nInstructor: " + instructorName + "; Location: " + courseLocation +
         "; Time: " + courseTimeSlot;
}

/**
 * Update value of the instructor of the course.
 *
 * @param newInstructorName The new instructor's name.
 */
void Course::reassignInstructor(const std::string& newInstructorName) {
  std::cout << "Old Instructor: " << instructorName << std::endl;
  this->instructorName =
      newInstructorName;  // Ensure the class member is being updated
  std::cout << "New Instructor: " << this->instructorName << std::endl;
}

/**
 * Update value of the location of the course.
 *
 * @param newLocation The new course location.
 */
void Course::reassignLocation(const std::string& newLocation) {
  courseLocation = newLocation;
}

/**
 * Update value of the time of the course.
 *
 * @param newTime The new time slot for the course.
 */
void Course::reassignTime(const std::string& newTime) {
  courseTimeSlot = newTime;
}

/**
 * Update the number of students enrolled in the course.
 *
 * @param count The number of enrolled students.
 */
void Course::setEnrolledStudentCount(int count) {
  enrolledStudentCount = count;
}

/**
 * Checks if the course has reached its enrollment capacity.
 *
 * @return true if the course is full, false otherwise.
 */
bool Course::isCourseFull() const {
  return enrolledStudentCount >= enrollmentCapacity;
}

/**
 * Serializes the Course object into a binary format.
 *
 * @param out The output stream where the course data will be written.
 */
void Course::serialize(std::ostream& out) const {
  out.write(reinterpret_cast<const char*>(&enrollmentCapacity),
            sizeof(enrollmentCapacity));
  out.write(reinterpret_cast<const char*>(&enrolledStudentCount),
            sizeof(enrolledStudentCount));

  size_t locationLen = courseLocation.length();
  out.write(reinterpret_cast<const char*>(&locationLen), sizeof(locationLen));
  out.write(courseLocation.c_str(), locationLen);

  size_t instructorLen = instructorName.length();
  out.write(reinterpret_cast<const char*>(&instructorLen),
            sizeof(instructorLen));
  out.write(instructorName.c_str(), instructorLen);

  size_t timeSlotLen = courseTimeSlot.length();
  out.write(reinterpret_cast<const char*>(&timeSlotLen), sizeof(timeSlotLen));
  out.write(courseTimeSlot.c_str(), timeSlotLen);
}

/**
 * Deserializes the Course object from a binary format.
 *
 * @param in The input stream from which the course data will be read.
 */
void Course::deserialize(std::istream& in) {
  in.read(reinterpret_cast<char*>(&enrollmentCapacity),
          sizeof(enrollmentCapacity));
  in.read(reinterpret_cast<char*>(&enrolledStudentCount),
          sizeof(enrolledStudentCount));

  size_t locationLen;
  in.read(reinterpret_cast<char*>(&locationLen), sizeof(locationLen));
  courseLocation.resize(locationLen);
  in.read(&courseLocation[0], locationLen);

  size_t instructorLen;
  in.read(reinterpret_cast<char*>(&instructorLen), sizeof(instructorLen));
  instructorName.resize(instructorLen);
  in.read(&instructorName[0], instructorLen);

  size_t timeSlotLen;
  in.read(reinterpret_cast<char*>(&timeSlotLen), sizeof(timeSlotLen));
  courseTimeSlot.resize(timeSlotLen);
  in.read(&courseTimeSlot[0], timeSlotLen);
}
