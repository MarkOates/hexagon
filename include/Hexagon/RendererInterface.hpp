#pragma once




namespace Hexagon
{
   class RendererInterface
   {
   private:

   protected:


   public:
      RendererInterface();
      virtual ~RendererInterface();

      virtual void render() = 0;
   };
}



