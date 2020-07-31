#pragma once


#include <gtest/gtest.h>
#include <string>


namespace Testing
{
   class WithAllegroRenderingFixture : public ::testing::Test
   {
   private:

   public:
      WithAllegroRenderingFixture();
      ~WithAllegroRenderingFixture();


   std::string run();
   };
}



