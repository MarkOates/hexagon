#pragma once


#include <gtest/gtest.h>


namespace Testing
{
   class WithAllegroRenderingFixture : public ::testing::Test
   {
   private:

   public:
      WithAllegroRenderingFixture();
      virtual ~WithAllegroRenderingFixture();


   virtual void SetUp() override;
   virtual void TearDown() override;
   };
}



