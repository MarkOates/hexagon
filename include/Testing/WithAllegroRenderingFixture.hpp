#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <gtest/gtest.h>


namespace Testing
{
   class WithAllegroRenderingFixture : public ::testing::Test
   {
   private:
      ALLEGRO_DISPLAY* display;
      AllegroFlare::FontBin font_bin;

   public:
      WithAllegroRenderingFixture();
      virtual ~WithAllegroRenderingFixture();


   virtual void SetUp() override;
   virtual void TearDown() override;
   };
}



