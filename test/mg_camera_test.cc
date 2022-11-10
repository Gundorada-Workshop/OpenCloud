#include "gtest/gtest.h"
#include "glm/glm.hpp"
#include "mg_camera.h"

// NOTE: Tests may fail here after implementing variable fps; failure is part of life :)

class mgCCameraTest : public ::testing::Test {
protected:
  void SetUp() override {
    camera.SetPos(glm::vec3(0.0f));
    camera.SetNextPos(glm::vec3(0.0f));
    camera.SetRef(glm::vec3(0.0f));
    camera.SetNextRef(glm::vec3(0.0f));
    camera.SetRoll(0.0f);
    camera.Resume();
    camera.StopCamera = false;
  }

  mgCCamera camera{ 8.0f };
};

TEST_F(mgCCameraTest, ShouldNotMoveOnItsOwn) 
{
  glm::vec3 orig_pos = camera.GetPos();

  camera.Step();
  EXPECT_TRUE(orig_pos == camera.GetPos());
}

TEST_F(mgCCameraTest, ShouldNotRotateOnItsOwn)
{
  glm::vec3 orig_ref = camera.GetRef();

  camera.Step();
  EXPECT_TRUE(orig_ref == camera.GetRef());
}

TEST_F(mgCCameraTest, ShouldMoveToNextPos) 
{
  glm::vec3 dest_pos = glm::vec3(10.0f);
  glm::vec3 orig_pos = camera.GetPos();

  camera.SetNextPos(dest_pos);
  camera.Step();
  EXPECT_TRUE(glm::distance(orig_pos, dest_pos) > glm::distance(camera.GetPos(), dest_pos));
}

TEST_F(mgCCameraTest, ShouldRotateToNextRef)
{
  glm::vec3 dest_hpr = glm::vec3(10.0f, 9.0f, 0.0f);
  glm::vec3 orig_hpr = camera.GetRef();

  camera.SetNextRef(dest_hpr);
  camera.Step();
  EXPECT_TRUE(glm::distance(orig_hpr, dest_hpr) > glm::distance(camera.GetRef(), dest_hpr));
}

TEST_F(mgCCameraTest, ShouldStopAtNextPos)
{
  glm::vec3 dest_pos = glm::vec3(10.0f);

  camera.SetNextPos(dest_pos);
  camera.Step(100);
  EXPECT_TRUE(camera.GetPos() == dest_pos);
}

TEST_F(mgCCameraTest, ShouldStopAtNextRef)
{
  glm::vec3 dest_hpr = glm::vec3(10.0f, 9.0f, 0.0f);

  camera.SetNextRef(dest_hpr);
  camera.Step(100);
  EXPECT_TRUE(camera.GetRef() == dest_hpr);
}

TEST_F(mgCCameraTest, ShouldJumpToNextPos)
{
  glm::vec3 dest_pos = glm::vec3(10000.0f);

  camera.SetNextPos(dest_pos);
  camera.Step(-1);
  EXPECT_TRUE(camera.GetPos() == dest_pos);
}

TEST_F(mgCCameraTest, ShouldJumpToNextRef)
{
  glm::vec3 dest_hpr = glm::vec3(180.0f, 180.0f, 0.0f);

  camera.SetNextRef(dest_hpr);
  camera.Step(-1);
  EXPECT_TRUE(camera.GetRef() == dest_hpr);
}

TEST_F(mgCCameraTest, ShouldNotMoveOrRotateWhileItIsSuspended)
{
  glm::vec3 orig_pos = camera.GetPos();
  glm::vec3 orig_hpr = camera.GetRef();
  glm::vec3 dest_pos = glm::vec3(10000.0f);
  glm::vec3 dest_hpr = glm::vec3(180.0f, 180.0f, 0.0f);

  camera.SetNextPos(dest_pos);
  camera.SetNextRef(dest_hpr);

  camera.Suspend();

  camera.Step();

  EXPECT_TRUE(camera.GetPos() == orig_pos && camera.GetRef() == orig_hpr);

  camera.Step(-1);

  EXPECT_TRUE(camera.GetPos() == orig_pos && camera.GetRef() == orig_hpr);
}

TEST_F(mgCCameraTest, ShouldNotMoveOrRotateWhileAllCamerasAreSuspended)
{
  glm::vec3 orig_pos = camera.GetPos();
  glm::vec3 orig_hpr = camera.GetRef();
  glm::vec3 dest_pos = glm::vec3(10000.0f);
  glm::vec3 dest_hpr = glm::vec3(180.0f, 180.0f, 0.0f);

  camera.SetNextPos(dest_pos);
  camera.SetNextRef(dest_hpr);

  camera.StopCamera = true;

  camera.Step();

  EXPECT_TRUE(camera.GetPos() == orig_pos && camera.GetRef() == orig_hpr);

  camera.Step(-1);

  EXPECT_TRUE(camera.GetPos() == orig_pos && camera.GetRef() == orig_hpr);
}

TEST_F(mgCCameraTest, ShouldMoveAfterItsSuspensionStops)
{
  glm::vec3 orig_pos = camera.GetPos();
  glm::vec3 orig_hpr = camera.GetRef();
  glm::vec3 dest_pos = glm::vec3(10000.0f);
  glm::vec3 dest_hpr = glm::vec3(180.0f, 180.0f, 0.0f);

  camera.SetNextPos(dest_pos);
  camera.SetNextRef(dest_hpr);

  camera.Suspend();
  camera.Resume();

  camera.Step();

  EXPECT_TRUE(camera.GetPos() != orig_pos && camera.GetRef() != orig_hpr);

  camera.Step(-1);

  EXPECT_TRUE(camera.GetPos() != orig_pos && camera.GetRef() != orig_hpr);
}

TEST_F(mgCCameraTest, ShouldNotMoveAfterStay)
{
  glm::vec3 orig_pos = camera.GetPos();
  glm::vec3 orig_hpr = camera.GetRef();
  glm::vec3 dest_pos = glm::vec3(10000.0f);
  glm::vec3 dest_hpr = glm::vec3(180.0f, 180.0f, 0.0f);

  camera.SetNextPos(dest_pos);
  camera.SetNextRef(dest_hpr);

  camera.Stay();

  EXPECT_TRUE(camera.GetPos() == orig_pos && camera.GetRef() == orig_hpr);

  camera.SetNextPos(dest_pos);
  camera.SetNextRef(dest_hpr);

  camera.Step();

  EXPECT_TRUE(camera.GetPos() != orig_pos && camera.GetRef() != orig_hpr);
}