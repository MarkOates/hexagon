#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro_flare/placement3d.h>
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
   ALLEGRO_FONT* get_any_font();
   placement3d centered_placement(float width=0.0f, float height=0.0f);
   };
}



