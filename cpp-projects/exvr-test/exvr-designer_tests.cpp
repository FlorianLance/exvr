
// catch
#include "catch.hpp"


//using namespace tool;


#include "experiment/experiment.hpp"

TEST_CASE("glm mat4x4 comparison with geometry::Mat4"){

    tool::ex::Experiment exp("test");
    // https://www.froglogic.com/blog/tip-of-the-week/unit-tests-for-qt-based-applications-with-catch/

//    SECTION("Matrix 3x3"){
//        REQUIRE(geo::equals(dm1,from_glm(glmdm1)));
//        REQUIRE(dm1.determinant() == glm::determinant(glmdm1));
//    }

//    SECTION("Look at"){
//        auto lightView1 = from_glm(glm::lookAt(
//            glm::vec3(-2.0f, 4.0f, -1.0f),
//            glm::vec3( 0.0f, 0.0f,  0.0f),
//            glm::vec3( 0.0f, 1.0f,  0.0f)
//        ));

//        auto lightView2 = geo::Mat4f::LookAt(
//            geo::Pt3f{-2.0f, 4.0f, -1.0f},
//            geo::Vec3f{0.0f, 0.0f,  0.0f},
//            geo::Vec3f{0.0f, 1.0f,  0.0f}
//        );

//        REQUIRE(geo::equals(clean(lightView1),clean(lightView2)));
//    }


}

