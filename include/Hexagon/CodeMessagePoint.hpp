#pragma once



#include <string>



class CodeMessagePoint
{
public:
   enum type_t
   {
      NONE,
      ERROR,
      TEST_FAILURE,
      POSITION,
   };

private:
   int x, y, length;
   int cursor_placement_offset;
   std::string message;
   type_t type;

public:
   CodeMessagePoint(
      int x=0,
      int y=0,
      int length=0,
      int cursor_placement_offset=0,
      std::string message="",
      CodeMessagePoint::type_t type=NONE
   );
   ~CodeMessagePoint();

   int get_x();
   int get_x2();
   int get_y();
   int get_length();
   int get_cursor_placement_offset();
   std::string get_message();
   CodeMessagePoint::type_t get_type();
   bool infer_at_point(int x, int y);

   void move_to(int new_x, int new_y);

   bool operator==(const CodeMessagePoint &other) const;
};



