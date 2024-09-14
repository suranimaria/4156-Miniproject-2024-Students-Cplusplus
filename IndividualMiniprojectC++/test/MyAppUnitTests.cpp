// Copyright 2024 Maria Surani
#include "MyApp.h"
#include <gtest/gtest.h>

TEST(MyAppUnitTests, SetupRunTest) {
    MyApp::run("setup");
    MyApp::onTermination();

    MyApp::run("run");
    MyFileDatabase* db = MyApp::getDatabase();
    std::string expected = 
    "For the CHEM department:\n"
    "CHEM 1403: \nInstructor: Ruben M Savizky; Location: 309 HAV; Time: 6:10-7:25\n"
    "CHEM 1500: \nInstructor: Joseph C Ulichny; Location: 302 HAV; Time: 6:10-9:50\n"
    "CHEM 2045: \nInstructor: Luis M Campos; Location: 209 HAV; Time: 1:10-2:25\n"
    "CHEM 2444: \nInstructor: Christopher Eckdahl; Location: 309 HAV; Time: 11:40-12:55\n"
    "CHEM 2494: \nInstructor: Talha Siddiqui; Location: 202 HAV; Time: 1:10-5:00\n"
    "CHEM 3080: \nInstructor: Milan Delor; Location: 209 HAV; Time: 10:10-11:25\n"
    "CHEM 4071: \nInstructor: Jonathan S Owen; Location: 320 HAV; Time: 8:40-9:55\n"
    "CHEM 4102: \nInstructor: Dalibor Sames; Location: 320 HAV; Time: 10:10-11:25\n\n"

    "For the COMS department:\n"
    "COMS 1004: \nInstructor: Adam Cannon; Location: 417 IAB; Time: 11:40-12:55\n"
    "COMS 3134: \nInstructor: Brian Borowski; Location: 301 URIS; Time: 4:10-5:25\n"
    "COMS 3157: \nInstructor: Jae Lee; Location: 417 IAB; Time: 4:10-5:25\n"
    "COMS 3203: \nInstructor: Ansaf Salleb-Aouissi; Location: 301 URIS; Time: 10:10-11:25\n"
    "COMS 3251: \nInstructor: Tony Dear; Location: 402 CHANDLER; Time: 1:10-3:40\n"
    "COMS 3261: \nInstructor: Josh Alman; Location: 417 IAB; Time: 2:40-3:55\n"
    "COMS 3827: \nInstructor: Daniel Rubenstein; Location: 207 Math; Time: 10:10-11:25\n"
    "COMS 4156: \nInstructor: Gail Kaiser; Location: 501 NWC; Time: 10:10-11:25\n\n"

    "For the ECON department:\n"
    "ECON 1105: \nInstructor: Waseem Noor; Location: 309 HAV; Time: 2:40-3:55\n"
    "ECON 2257: \nInstructor: Tamrat Gashaw; Location: 428 PUP; Time: 10:10-11:25\n"
    "ECON 3211: \nInstructor: Murat Yilmaz; Location: 310 FAY; Time: 4:10-5:25\n"
    "ECON 3213: \nInstructor: Miles Leahey; Location: 702 HAM; Time: 4:10-5:25\n"
    "ECON 3412: \nInstructor: Thomas Piskula; Location: 702 HAM; Time: 11:40-12:55\n"
    "ECON 4415: \nInstructor: Evan D Sadler; Location: 309 HAV; Time: 10:10-11:25\n"
    "ECON 4710: \nInstructor: Matthieu Gomez; Location: 517 HAM; Time: 8:40-9:55\n"
    "ECON 4840: \nInstructor: Mark Dean; Location: 142 URIS; Time: 2:40-3:55\n\n"

    "For the IEOR department:\n"
    "IEOR 2500: \nInstructor: Uday Menon; Location: 627 MUDD; Time: 11:40-12:55\n"
    "IEOR 3404: \nInstructor: Christopher J Dolan; Location: 303 MUDD; Time: 10:10-11:25\n"
    "IEOR 3658: \nInstructor: Daniel Lacker; Location: 310 FAY; Time: 10:10-11:25\n"
    "IEOR 4102: \nInstructor: Antonius B Dieker; Location: 209 HAM; Time: 10:10-11:25\n"
    "IEOR 4106: \nInstructor: Kaizheng Wang; Location: 501 NWC; Time: 10:10-11:25\n"
    "IEOR 4405: \nInstructor: Yuri Faenza; Location: 517 HAV; Time: 11:40-12:55\n"
    "IEOR 4511: \nInstructor: Michael Robbins; Location: 633 MUDD; Time: 9:00-11:30\n"
    "IEOR 4540: \nInstructor: Krzysztof M Choromanski; Location: 633 MUDD; Time: 7:10-9:40\n\n"

    "For the PHYS department:\n"
    "PHYS 1001: \nInstructor: Szabolcs Marka; Location: 301 PUP; Time: 2:40-3:55\n"
    "PHYS 1221: \nInstructor: James G. Mccann; Location: 301 PUP; Time: 4:10-5:25\n"
    "PHYS 1520: \nInstructor: Victor G. Moffat; Location: 630 MUDD; Time: 4:10-5:25\n"
    "PHYS 2000: \nInstructor: Frank E. L. Banta; Location: 402 CHANDLER; Time: 1:10-3:40\n"
    "PHYS 3801: \nInstructor: Katherine M. McMahon; Location: 603 MUDD; Time: 4:10-5:25\n"
    "PHYS 4205: \nInstructor: Michael P. Larkin; Location: 309 HAV; Time: 6:10-9:50\n\n";

    EXPECT_EQ(db->display(), expected);
}

TEST(MyAppUnitTests, OverrideDatabaseTest) {
    MyFileDatabase* customDb = new MyFileDatabase{1, ""};

    std::shared_ptr<Course> course = std::make_shared<Course>(5, "Jane Doe", "100 CSP", "2:40-3:55");
    course->setEnrolledStudentCount(3);

    std::map<std::string, std::shared_ptr<Course>> coursesList = {{"156", course}};
    
    Department dept("CS", coursesList, "Joe Doe", 3000);
    std::map<std::string, Department> mapping = {{"CS", dept}};

    customDb->setMapping(mapping);

    MyApp::overrideDatabase(customDb);
    MyFileDatabase* db = MyApp::getDatabase();

    const auto& dbMappingOverriden = db->getDepartmentMapping();
    ASSERT_EQ(dbMappingOverriden.size(), mapping.size());
    
    auto it = dbMappingOverriden.find("CS");
    ASSERT_NE(it, dbMappingOverriden.end()); 
    
    const Department& dbDeptOverriden = it->second;

    EXPECT_EQ(dbDeptOverriden.getDepartmentChair(), dept.getDepartmentChair());
    EXPECT_EQ(dbDeptOverriden.getNumberOfMajors(), dept.getNumberOfMajors());

    const auto& dbCoursesOverriden = dbDeptOverriden.getCourseSelection();

    ASSERT_EQ(dbCoursesOverriden.size(), coursesList.size());
    auto courseIt = dbCoursesOverriden.find("156");
    ASSERT_NE(courseIt, dbCoursesOverriden.end());

    const auto& dbCourse = courseIt->second;

    EXPECT_EQ(dbCourse->getInstructorName(), course->getInstructorName());
    EXPECT_EQ(dbCourse->getCourseLocation(), course->getCourseLocation());
    EXPECT_EQ(dbCourse->getCourseTimeSlot(), course->getCourseTimeSlot());
}