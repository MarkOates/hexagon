#pragma once




namespace Hexagon
{
   namespace RulersAndMeasurements
   {
      class CodeEditorDimentions
      {
      private:

      protected:


      public:
         CodeEditorDimentions();
         ~CodeEditorDimentions();

         float calculate_max_half_surface_width(float surface_width=1.0f, float cell_width=1.0f, int num_columns=1);
      };
   }
}



