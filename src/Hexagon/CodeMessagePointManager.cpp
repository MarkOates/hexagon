

#include <Hexagon/CodeMessagePointManager.hpp>



namespace Hexagon
{


CodeMessagePointManager::CodeMessagePointManager()
   : code_message_points({})
{
}


CodeMessagePointManager::~CodeMessagePointManager()
{
}


void CodeMessagePointManager::append(CodeMessagePoint code_message_point)
{
code_message_points.push_back(code_message_point);
return;

}

void CodeMessagePointManager::clear()
{
code_message_points.clear();
return;

}

void CodeMessagePointManager::delete_row()
{
return;

}

void CodeMessagePointManager::insert_row()
{
return;

}
} // namespace Hexagon


