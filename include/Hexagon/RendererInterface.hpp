#pragma once




namespace Hexagon
{
   class RendererInterface
   {
   private:

   public:
      RendererInterface();
      virtual ~RendererInterface();

      virtual void render() = 0;
   };
}



