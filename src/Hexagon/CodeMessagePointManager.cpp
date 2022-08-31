

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


std::vector<CodeMessagePoint> CodeMessagePointManager::get_code_message_points() const
{
   return code_message_points;
}


std::vector<CodeMessagePoint> &CodeMessagePointManager::get_code_message_points_ref()
{
   return code_message_points;
}


void CodeMessagePointManager::append(CodeMessagePoint code_message_point)
{
   code_message_points.push_back(code_message_point);
   return;
}

void CodeMessagePointManager::set_code_message_points(std::vector<CodeMessagePoint> code_message_points)
{
   this->code_message_points = code_message_points;
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

void CodeMessagePointManager::shift_rows_down_at_and_after(int row)
{
   for (auto &code_message_point : code_message_points)
   {
      if (code_message_point.get_y() >= row)
         code_message_point.move_to(code_message_point.get_x(), code_message_point.get_y()+1);
   }
   return;
}


} // namespace Hexagon


