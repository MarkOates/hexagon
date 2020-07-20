#pragma once


#include <Hexagon/StageInterface.hpp>
#include <string>
#include <tuple>
#include <vector>


namespace Hexagon
{
   class Layout
   {
   private:
      std::string project_root;
      std::vector<std::tuple<std::string, float, float>> file;
      std::string daemus_command;
      int display_default_height;
      int code_editor_width;
      std::vector<StageInterface *>& stages;
      static std::vector<StageInterface *> dummy_stages;

   public:
      Layout(std::string project_root="", std::vector<std::tuple<std::string, float, float>> file={}, std::string daemus_command="", int display_default_height=1350, int code_editor_width=1215, std::vector<StageInterface *>& stages=get_dummy_stages_ref());
      ~Layout();

      void set_file(std::vector<std::tuple<std::string, float, float>> file);
      void set_stages(std::vector<StageInterface *>& stages);

      std::string get_project_root();
      std::vector<std::tuple<std::string, float, float>> get_file();
      std::string get_daemus_command();
      int get_display_default_height();
      int get_code_editor_width();
      std::vector<StageInterface *>& get_stages();
      static std::vector<StageInterface *> &get_dummy_stages_ref();
   bool place_and_load_code_editor(std::vector<StageInterface *>* stages_ptr=nullptr, std::string filename="", std::string file_category="undefined_file_category", float x=0.0f, float y=0.0f);
   };
}



