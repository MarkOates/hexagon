#pragma once



class StageRendererInterface
{
public:
   StageRendererInterface();
   virtual ~StageRendererInterface();

   virtual void render() = 0;
};



