
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/Builds/Base.hpp>
#include <Hexagon/BuildSystem/BuildStages/Base.hpp>
#include <thread>


class BuildStageTestClass : public Hexagon::BuildSystem::BuildStages::Base
{
public:
   int call_counter;
   BuildStageTestClass() : Hexagon::BuildSystem::BuildStages::Base("BuildStageTestClass"), call_counter(0) {}
   virtual void execute() override { call_counter++; }
};


class ExceptionThrowingBuildStageTestClass : public Hexagon::BuildSystem::BuildStages::Base
{
public:
   ExceptionThrowingBuildStageTestClass()
      : Hexagon::BuildSystem::BuildStages::Base("ExceptionThrowingBuildStageTestClass")
   {}
   virtual void execute() override { throw std::runtime_error("exception thrown!"); }
};


class SleepingBuildStageTestClass : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   float length_in_seconds;
public:
   SleepingBuildStageTestClass(float length_in_seconds)
      : Hexagon::BuildSystem::BuildStages::Base("SleepingBuildStageTestClass")
      , length_in_seconds(length_in_seconds)
   {}
   virtual void execute() override {
      int length_in_milliseconds = (int)(length_in_seconds * 1000.0);
      std::this_thread::sleep_for(std::chrono::milliseconds(length_in_milliseconds));
   }
};


class BuildsBaseTestClass : public Hexagon::BuildSystem::Builds::Base
{
public:
   BuildsBaseTestClass()
      : Hexagon::BuildSystem::Builds::Base("BuildsBaseTestClass")
   {}
};


TEST(Hexagon_BuildSystem_Builds_BaseTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::Builds::Base base;
}


TEST(Hexagon_BuildSystem_Builds_BaseTest, has_the_expected_type)
{
   Hexagon::BuildSystem::Builds::Base base;
   EXPECT_EQ("Base", base.get_type());
}


TEST(Hexagon_BuildSystem_Builds_BaseTest, derived_classes_will_have_the_expected_type)
{
   BuildsBaseTestClass test_class;
   EXPECT_EQ("BuildsBaseTestClass", test_class.get_type());
}


TEST(Hexagon_BuildSystem_Builds_BaseTest, status__is_initialized_with_the_expected_value)
{
   BuildsBaseTestClass base_build;
   EXPECT_EQ(Hexagon::BuildSystem::Builds::Base::STATUS_NOT_STARTED, base_build.get_status());
}


TEST(Hexagon_BuildSystem_Builds_BaseTest,
   run__with_a_successful_build__will_set_the_status_to_finished)
{
   BuildsBaseTestClass base_build;
   base_build.run();
   EXPECT_EQ(Hexagon::BuildSystem::Builds::Base::STATUS_FINISHED, base_build.get_status());
}


TEST(Hexagon_BuildSystem_Builds_BaseTest,
   run__with_a_failed_build__will_set_the_status_to_failed)
{
   BuildsBaseTestClass base_build;
   base_build.set_build_stages({ new ExceptionThrowingBuildStageTestClass });
   base_build.run();
   EXPECT_EQ(Hexagon::BuildSystem::Builds::Base::STATUS_ERROR, base_build.get_status());
}


TEST(Hexagon_BuildSystem_Builds_BaseTest,
   run__with_build_stages__will_call_execute_on_each_build_stage)
{
   BuildsBaseTestClass base_build;
   base_build.set_build_stages({
      new BuildStageTestClass,
      new BuildStageTestClass,
   });

   base_build.run();

   std::vector<Hexagon::BuildSystem::BuildStages::Base*> build_stages = base_build.get_build_stages();
   for (auto &build_stage : build_stages)
   {
      EXPECT_EQ(1, dynamic_cast<BuildStageTestClass*>(build_stage)->call_counter);
   }
}


TEST(Hexagon_BuildSystem_Builds_BaseTest,
   run__when_a_build_stage_throws_an_exception__will_halt_execution_of_the_remaining_stages)
{
   BuildsBaseTestClass base_build;
   base_build.set_build_stages({
      new BuildStageTestClass,
      new BuildStageTestClass,
      new ExceptionThrowingBuildStageTestClass,
      new BuildStageTestClass,
   });

   base_build.run();

   std::vector<Hexagon::BuildSystem::BuildStages::Base*> build_stages = base_build.get_build_stages();

   ASSERT_EQ(4, build_stages.size());

   EXPECT_EQ(Hexagon::BuildSystem::BuildStages::Base::STATUS_FINISHED, build_stages[0]->get_status());
   EXPECT_EQ(Hexagon::BuildSystem::BuildStages::Base::STATUS_FINISHED, build_stages[1]->get_status());
   EXPECT_EQ(Hexagon::BuildSystem::BuildStages::Base::STATUS_ERROR, build_stages[2]->get_status());
   EXPECT_EQ(Hexagon::BuildSystem::BuildStages::Base::STATUS_NOT_STARTED, build_stages[3]->get_status());
}


TEST(Hexagon_BuildSystem_Builds_BaseTest,
   infer_duraiton_seconds__after_run__will_return_the_duration_of_build_in_seconds)
{
   float sleep_duration_seconds = 0.2;
   BuildsBaseTestClass base_build;
   base_build.set_build_stages({ new SleepingBuildStageTestClass(sleep_duration_seconds) });

   EXPECT_EQ(0, base_build.infer_duration_seconds());
   base_build.run();
   EXPECT_GT(base_build.infer_duration_seconds(), sleep_duration_seconds);
}


