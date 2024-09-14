#include "MyApp.h"
#include "RouteController.h"
#include <gtest/gtest.h>

// Helper function to set up the database and initialize routes
void SetUpDatabase(RouteController& routeController) {
    MyApp::run("setup");  

    crow::SimpleApp app;  
    routeController.initRoutes(app);  
    routeController.setDatabase(MyApp::getDatabase()); 
}

TEST(RouteControllerUnitTests, IndexTest) {
    RouteController routeController;
    crow::response res{};

    routeController.index(res);

    std::string expected = 
        "Welcome, in order to make an API call direct your browser or Postman to "
        "an endpoint \n\n This can be done using the following format: \n\n "
        "http://127.0.0.1:8080/endpoint?arg=value";

    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, expected);
}

TEST(RouteControllerUnitTests, RetrieveDepartmentTest) {
    RouteController routeController;
    SetUpDatabase(routeController);

    std::string expected = 
    "PHYS 1001: \n"
    "Instructor: Szabolcs Marka; Location: 301 PUP; Time: 2:40-3:55\n"
    "PHYS 1221: \n"
    "Instructor: James G. Mccann; Location: 301 PUP; Time: 4:10-5:25\n"
    "PHYS 1520: \n"
    "Instructor: Victor G. Moffat; Location: 630 MUDD; Time: 4:10-5:25\n"
    "PHYS 2000: \n"
    "Instructor: Frank E. L. Banta; Location: 402 CHANDLER; Time: 1:10-3:40\n"
    "PHYS 3801: \n"
    "Instructor: Katherine M. McMahon; Location: 603 MUDD; Time: 4:10-5:25\n"
    "PHYS 4205: \n"
    "Instructor: Michael P. Larkin; Location: 309 HAV; Time: 6:10-9:50\n";

    crow::request req{};
    crow::response res{};

    req.url_params = crow::query_string{"?deptCode=PHYS"};
    routeController.retrieveDepartment(req, res);
    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, expected);

    req.url_params.clear();
    res.body.clear();
    res.code = 0;

    req.url_params = crow::query_string{"?deptCode=none"};
    routeController.retrieveDepartment(req, res);
    EXPECT_EQ(res.code, 404);
    EXPECT_EQ(res.body, "Department Not Found");

    req.url_params.clear();
    res.body.clear();
    res.code = 0;

    routeController.retrieveDepartment(req, res);
    EXPECT_EQ(res.code, 400);
    EXPECT_EQ(res.body, "Department code must be included in the request.");
}

TEST(RouteControllerUnitTests, RetrieveCourseTest) {
    RouteController routeController;
    SetUpDatabase(routeController);

    crow::request req{};
    crow::response res{};
    req.url_params = crow::query_string{"?deptCode=PHYS&courseCode=1001"};
    routeController.retrieveCourse(req, res);
    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, "\nInstructor: Szabolcs Marka; Location: 301 PUP; Time: 2:40-3:55");

    req.url_params.clear();
    res.body.clear();
    res.code = 0;
    req.url_params = crow::query_string{"?deptCode=PHYS&courseCode=9999"};
    routeController.retrieveCourse(req, res);
    EXPECT_EQ(res.code, 404);
    EXPECT_EQ(res.body, "Course Not Found");

    req.url_params.clear();
    res.body.clear();
    res.code = 0;
    req.url_params = crow::query_string{"?deptCode=PHYS"};
    routeController.retrieveCourse(req, res);
    EXPECT_EQ(res.code, 400);
    EXPECT_EQ(res.body, "Both department code and course code must be included in the request.");
}

TEST(RouteControllerUnitTests, IsCourseFullTest) {
    RouteController routeController;
    SetUpDatabase(routeController);

    crow::request req{};
    crow::response res{};
    req.url_params = crow::query_string{"?deptCode=PHYS&courseCode=1001"};
    routeController.isCourseFull(req, res);
    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, "false"); 
}

TEST(RouteControllerUnitTests, GetMajorCountFromDeptTest) {
    RouteController routeController;
    SetUpDatabase(routeController);

    crow::request req{};
    crow::response res{};
    req.url_params = crow::query_string{"?deptCode=PHYS"};
    routeController.getMajorCountFromDept(req, res);
    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, "There are: 200 majors in the department"); 
}

TEST(RouteControllerUnitTests, IdentifyDeptChairTest) {
    RouteController routeController;
    SetUpDatabase(routeController);

    crow::request req{};
    crow::response res{};
    req.url_params = crow::query_string{"?deptCode=PHYS"};
    routeController.identifyDeptChair(req, res);
    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, "Marcia L. Newson is the department chair."); 
}

TEST(RouteControllerUnitTests, FindCourseLocationTest) {
    RouteController routeController;
    SetUpDatabase(routeController);

    crow::request req{};
    crow::response res{};
    req.url_params = crow::query_string{"?deptCode=PHYS&courseCode=1001"};
    routeController.findCourseLocation(req, res);
    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, "301 PUP is where the course is located."); 
}

TEST(RouteControllerUnitTests, FindCourseInstructorTest) {
    RouteController routeController;
    SetUpDatabase(routeController);

    crow::request req{};
    crow::response res{};
    req.url_params = crow::query_string{"?deptCode=PHYS&courseCode=1001"};
    routeController.findCourseInstructor(req, res);
    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, "Szabolcs Marka is the instructor for the course.");  
}

TEST(RouteControllerUnitTests, FindCourseTimeTest) {
    RouteController routeController;
    SetUpDatabase(routeController);

    crow::request req{};
    crow::response res{};
    req.url_params = crow::query_string{"?deptCode=PHYS&courseCode=1001"};
    routeController.findCourseTime(req, res);
    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, "The course meets at: 2:40-3:55");
}

TEST(RouteControllerUnitTests, AddMajorToDeptTest) {
    RouteController routeController;
    SetUpDatabase(routeController);

    crow::request req{};
    crow::response res{};
    req.url_params = crow::query_string{"?deptCode=PHYS"};
    routeController.addMajorToDept(req, res);
    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, "Attribute was updated successfully");
}

TEST(RouteControllerUnitTests, SetEnrollmentCountTest) {
    RouteController routeController;
    SetUpDatabase(routeController);

    crow::request req{};
    crow::response res{};
    req.url_params = crow::query_string{"?deptCode=PHYS&courseCode=1001&count=42"};
    routeController.setEnrollmentCount(req, res);
    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, "Attribute was updated successfully.");
}

TEST(RouteControllerUnitTests, SetCourseLocationTest) {
    RouteController routeController;
    SetUpDatabase(routeController);

    crow::request req{};
    crow::response res{};
    req.url_params = crow::query_string{"?deptCode=PHYS&courseCode=1001&location=New Room"};
    routeController.setCourseLocation(req, res);
    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, "Attribute was updated successfully.");
}

TEST(RouteControllerUnitTests, SetCourseInstructorTest) {
    RouteController routeController;
    SetUpDatabase(routeController);

    crow::request req{};
    crow::response res{};
    req.url_params = crow::query_string{"?deptCode=PHYS&courseCode=1001&instructor=Jane Doe"};
    routeController.setCourseInstructor(req, res);
    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, "Attribute was updated successfully.");
}

TEST(RouteControllerUnitTests, SetCourseTimeTest) {
    RouteController routeController;
    SetUpDatabase(routeController);

    crow::request req{};
    crow::response res{};
    req.url_params = crow::query_string{"?deptCode=PHYS&courseCode=1001&time=14:10"};
    routeController.setCourseTime(req, res);
    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, "Attribute was updated successfully.");
}


TEST(RouteControllerUnitTests, RemoveMajorFromDeptTest) {
    RouteController routeController;
    SetUpDatabase(routeController);

    crow::request req{};
    crow::response res{};
    req.url_params = crow::query_string{"?deptCode=PHYS"};
    routeController.removeMajorFromDept(req, res);
    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, "Attribute was updated successfully");
}

// TEST(RouteControllerUnitTests, DropStudentFromCourseTest) {
//     RouteController routeController;
//     SetUpDatabase(routeController);

//     crow::request req{};
//     crow::response res{};
//     req.url_params = crow::query_string{"?deptCode=PHYS&courseCode=1001"};
//     routeController.dropStudentFromCourse(req, res);
//     EXPECT_EQ(res.code, 200);
//     EXPECT_EQ(res.body, "Student has been dropped");
// }
