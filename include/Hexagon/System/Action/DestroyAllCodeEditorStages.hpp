#pragma once


#include <Hexagon/Action.hpp>
#include <Hexagon/StageInterface.hpp>
#include <vector>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class DestroyAllCodeEditorStages : public ::Action
         {
         private:
            std::vector<StageInterface *>& stages;
            static std::vector<StageInterface *> dummy_stages;

         public:
            DestroyAllCodeEditorStages(std::vector<StageInterface *>& stages=get_dummy_stages_ref());
            virtual ~DestroyAllCodeEditorStages();

            void set_stages(std::vector<StageInterface *>& stages);
            std::vector<StageInterface *>& get_stages() const;
            static std::vector<StageInterface *> &get_dummy_stages_ref();
            virtual bool execute() override;
         };
      }
   }
}



