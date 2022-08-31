#pragma once




namespace Hexagon
{
   class Packet
   {
   private:
      int searches_count;
      int saves_count;

   protected:


   public:
      Packet(int searches_count=0, int saves_count=0);
      ~Packet();

      int get_searches_count() const;
      int get_saves_count() const;
      int calculate_score();
   };
}



