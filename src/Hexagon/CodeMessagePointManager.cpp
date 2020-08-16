

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

void CodeMessagePointManager::delete_row(int row)
{
for (int i=0; i<code_message_points.size(); i++)
{
   if (code_message_points[i].get_y() == row)
   {
      code_message_points.erase(code_message_points.begin() + i);
      i--;
   }
   else if (code_message_points[i].get_y() >= row)
   {
      code_message_points[i].move_to(code_message_points[i].get_x(), code_message_points[i].get_y()-1);
   }
}
return;

}

void CodeMessagePointManager::insert_row()
{
return;

}
} // namespace Hexagon


