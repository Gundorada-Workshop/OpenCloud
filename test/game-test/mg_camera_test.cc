#include <gtest/gtest.h>

#include "common/types.h"
#include "common/math.h"
#include "common/constants.h"

#include "engine/mg/mg_camera.h"

using namespace common;

// NOTE: Tests may fail here after implementing variable fps; failure is part of life :)

class mgCCameraTest : public ::testing::Test {
protected:
  void SetUp() override {
    new (&camera) mgCCamera();
    camera.StopCamera = false;
  }

  mgCCamera camera{ 8.0f };
};

//TEST_F(mgCCameraTest, ShouldNotMoveOnItsOwn) 
//{
//  vec3 orig_pos = camera.GetPos();
//
//  camera.Step();
//  EXPECT_TRUE(orig_pos == camera.GetPos());
//}
//
//TEST_F(mgCCameraTest, ShouldNotRotateOnItsOwn)
//{
//  vec3 orig_ref = camera.GetRef();
//
//  camera.Step();
//  EXPECT_TRUE(orig_ref == camera.GetRef());
//}
//
//TEST_F(mgCCameraTest, ShouldMoveToNextPos) 
//{
//  vec3 dest_pos = vec3(10.0f);
//  vec3 orig_pos = camera.GetPos();
//
//  camera.SetNextPos(dest_pos);
//  camera.Step();
//  EXPECT_TRUE(math::vector_distance(orig_pos, dest_pos) > math::vector_distance(camera.GetPos(), dest_pos));
//}
//
//TEST_F(mgCCameraTest, ShouldRotateToNextRef)
//{
//  vec3 dest_hpr = vec3(10.0f, 9.0f, 0.0f);
//  vec3 orig_hpr = camera.GetRef();
//
//  camera.SetNextRef(dest_hpr);
//  camera.Step();
//  EXPECT_TRUE(math::vector_distance(orig_hpr, dest_hpr) > math::vector_distance(camera.GetRef(), dest_hpr));
//}
//
//TEST_F(mgCCameraTest, ShouldStopAtNextPos)
//{
//  vec3 dest_pos = vec3(10.0f);
//
//  camera.SetNextPos(dest_pos);
//  camera.Step(100);
//  EXPECT_TRUE(camera.GetPos() == dest_pos);
//}
//
//TEST_F(mgCCameraTest, ShouldStopAtNextRef)
//{
//  vec3 dest_hpr = vec3(10.0f, 9.0f, 0.0f);
//
//  camera.SetNextRef(dest_hpr);
//  camera.Step(100);
//  EXPECT_TRUE(camera.GetRef() == dest_hpr);
//}
//
//TEST_F(mgCCameraTest, ShouldJumpToNextPos)
//{
//  vec3 dest_pos = vec3(10000.0f);
//
//  camera.SetNextPos(dest_pos);
//  camera.Step(-1);
//  EXPECT_TRUE(camera.GetPos() == dest_pos);
//}
//
//TEST_F(mgCCameraTest, ShouldJumpToNextRef)
//{
//  vec3 dest_hpr = vec3(180.0f, 180.0f, 0.0f);
//
//  camera.SetNextRef(dest_hpr);
//  camera.Step(-1);
//  EXPECT_TRUE(camera.GetRef() == dest_hpr);
//}
//
//TEST_F(mgCCameraTest, ShouldNotMoveOrRotateWhileItIsSuspended)
//{
//  vec3 orig_pos = camera.GetPos();
//  vec3 orig_hpr = camera.GetRef();
//  vec3 dest_pos = vec3(10000.0f);
//  vec3 dest_hpr = vec3(180.0f, 180.0f, 0.0f);
//
//  camera.SetNextPos(dest_pos);
//  camera.SetNextRef(dest_hpr);
//
//  camera.Suspend();
//
//  camera.Step();
//
//  EXPECT_TRUE(camera.GetPos() == orig_pos && camera.GetRef() == orig_hpr);
//
//  camera.Step(-1);
//
//  EXPECT_TRUE(camera.GetPos() == orig_pos && camera.GetRef() == orig_hpr);
//}
//
//TEST_F(mgCCameraTest, ShouldNotMoveOrRotateWhileAllCamerasAreSuspended)
//{
//  vec3 orig_pos = camera.GetPos();
//  vec3 orig_hpr = camera.GetRef();
//  vec3 dest_pos = vec3(10000.0f);
//  vec3 dest_hpr = vec3(180.0f, 180.0f, 0.0f);
//
//  camera.SetNextPos(dest_pos);
//  camera.SetNextRef(dest_hpr);
//
//  camera.StopCamera = true;
//
//  camera.Step();
//
//  EXPECT_TRUE(camera.GetPos() == orig_pos && camera.GetRef() == orig_hpr);
//
//  camera.Step(-1);
//
//  EXPECT_TRUE(camera.GetPos() == orig_pos && camera.GetRef() == orig_hpr);
//}
//
//TEST_F(mgCCameraTest, ShouldMoveAfterItsSuspensionStops)
//{
//  vec3 orig_pos = camera.GetPos();
//  vec3 orig_hpr = camera.GetRef();
//  vec3 dest_pos = vec3(10000.0f);
//  vec3 dest_hpr = vec3(180.0f, 180.0f, 0.0f);
//
//  camera.SetNextPos(dest_pos);
//  camera.SetNextRef(dest_hpr);
//
//  camera.Suspend();
//  camera.Resume();
//
//  camera.Step();
//
//  EXPECT_TRUE(camera.GetPos() != orig_pos && camera.GetRef() != orig_hpr);
//
//  camera.Step(-1);
//
//  EXPECT_TRUE(camera.GetPos() != orig_pos && camera.GetRef() != orig_hpr);
//}
//
//TEST_F(mgCCameraTest, ShouldNotMoveAfterStay)
//{
//  vec3 orig_pos = camera.GetPos();
//  vec3 orig_hpr = camera.GetRef();
//  vec3 dest_pos = vec3(10000.0f);
//  vec3 dest_hpr = vec3(180.0f, 180.0f, 0.0f);
//
//  camera.SetNextPos(dest_pos);
//  camera.SetNextRef(dest_hpr);
//
//  camera.Stay();
//
//  EXPECT_TRUE(camera.GetPos() == orig_pos && camera.GetRef() == orig_hpr);
//
//  camera.SetNextPos(dest_pos);
//  camera.SetNextRef(dest_hpr);
//
//  camera.Step();
//
//  EXPECT_TRUE(camera.GetPos() != orig_pos && camera.GetRef() != orig_hpr);
//}