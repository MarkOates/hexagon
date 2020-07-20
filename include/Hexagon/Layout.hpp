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
      std::vector<StageInterface *>* stages;
      std::vector<std::tuple<std::string, std::string, float, float>> files;
      std::string daemus_command;
      int code_editor_height;
      int code_editor_width;

   public:
      Layout(std::string project_root="", std::vector<StageInterface *>* stages=nullptr, std::vector<std::tuple<std::string, std::string, float, float>> files={}, std::string daemus_command="", int code_editor_height=1350, int code_editor_width=1215);
      ~Layout();

      void set_stages(std::vector<StageInterface *>* stages);
      void set_files(std::vector<std::tuple<std::string, std::string, float, float>> files);

      std::string get_project_root();
      std::vector<StageInterface *>* get_stages();
      std::vector<std::tuple<std::string, std::string, float, float>> get_files();
      std::string get_daemus_command();
      int get_code_editor_height();
      int get_code_editor_width();
   bool place_and_load_code_editor(std::vector<StageInterface *>* stages_ptr=nullptr, std::string filename="", std::string file_category="undefined_file_category", float x=0.0f, float y=0.0f);
   void create();
   };
}



