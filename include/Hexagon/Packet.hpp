#pragma once




namespace Hexagon
{
   class Packet
   {
   private:
      int searches_count;
      int saves_count;

   public:
      Packet(int searches_count=0, int saves_count=0);
      ~Packet();

      int get_searches_count();
      int get_saves_count();
      int calculate_score();
   };
}



