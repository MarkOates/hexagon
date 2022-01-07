#pragma once



class CodePoint
{
private:
   int x;
   int y;

public:
   CodePoint(int x=0, int y=0);
   ~CodePoint();

   int get_x() const;
   int get_y() const;
   void set_x(int x);
   void set_y(int y);
};



#include <ostream>



bool operator<(const CodePoint &a, const CodePoint &b);
bool operator==(const CodePoint &a, const CodePoint &b);
std::ostream &operator<<(std::ostream &out, CodePoint &code_point);



