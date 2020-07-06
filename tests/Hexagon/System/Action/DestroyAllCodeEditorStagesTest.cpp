
#include <gtest/gtest.h>

#include <Hexagon/System/Action/DestroyAllCodeEditorStages.hpp>



class CodeEditorTestStage : public StageInterface
{
public:
   CodeEditorTestStage() : StageInterface(StageInterface::CODE_EDITOR) {}
   virtual void render() override {}
   virtual void process_local_event(std::string event_name, ActionData action_data=ActionData()) override {}
   virtual void process_event(ALLEGRO_EVENT &event) override {}
};

class OneLineInputBoxTestStage : public StageInterface
{
public:
   OneLineInputBoxTestStage() : StageInterface(StageInterface::ONE_LINE_INPUT_BOX) {}
   virtual void render() override {}
   virtual void process_local_event(std::string event_name, ActionData action_data=ActionData()) override {}
   virtual void process_event(ALLEGRO_EVENT &event) override {}
};

class FileNavigatorTestStage : public StageInterface
{
public:
   FileNavigatorTestStage() : StageInterface(StageInterface::FILE_NAVIGATOR) {}
   virtual void render() override {}
   virtual void process_local_event(std::string event_name, ActionData action_data=ActionData()) override {}
   virtual void process_event(ALLEGRO_EVENT &event) override {}
};

class MissingFileTestStage : public StageInterface
{
public:
   MissingFileTestStage() : StageInterface(StageInterface::MISSING_FILE) {}
   virtual void render() override {}
   virtual void process_local_event(std::string event_name, ActionData action_data=ActionData()) override {}
   virtual void process_event(ALLEGRO_EVENT &event) override {}
};


TEST(Hexagon_System_Action_DestroyAllCodeEditorStagesTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::DestroyAllCodeEditorStages destroy_all_code_editor_stages;
}

TEST(Hexagon_System_Action_DestroyAllCodeEditorStagesTest, execute__returns_the_expected_response)
{
   Hexagon::System::Action::DestroyAllCodeEditorStages destroy_all_code_editor_stages;
   EXPECT_EQ(true, destroy_all_code_editor_stages.execute());
}

TEST(Hexagon_System_Action_DestroyAllCodeEditorStagesTest,
   execute__modifieds_the_stages_by_removing_all_code_editor_types)
{
   CodeEditorTestStage *code_editor1 = new CodeEditorTestStage();
   CodeEditorTestStage *code_editor2 = new CodeEditorTestStage();
   OneLineInputBoxTestStage *one_line_input_box = new OneLineInputBoxTestStage();
   FileNavigatorTestStage *file_navigator = new FileNavigatorTestStage();
   MissingFileTestStage *missing_file = new MissingFileTestStage();

   std::vector<StageInterface *> stages = {
      code_editor1,
      one_line_input_box,
      code_editor2,
      missing_file,
      file_navigator,
   };

   std::vector<StageInterface *> expected_result_stages = {
      one_line_input_box,
      file_navigator,
   };

   Hexagon::System::Action::DestroyAllCodeEditorStages destroy_all_code_editor_stages(stages);
   EXPECT_EQ(true, destroy_all_code_editor_stages.execute());

   EXPECT_EQ(expected_result_stages, stages);

   delete one_line_input_box;
   delete file_navigator;
}
