#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/StageFactory.hpp>
#include <Hexagon/System/Config.hpp>
#include <gtest/gtest.h>


namespace Testing
{
   class WithStageFactoryFixture : public ::testing::Test
   {
   private:
      Hexagon::System::Config config;
      AllegroFlare::FontBin font_bin;
      Hexagon::StageFactory stage_factory;

   public:
      WithStageFactoryFixture();
      virtual ~WithStageFactoryFixture();


      AllegroFlare::FontBin &get_font_bin_ref();
      Hexagon::StageFactory &get_stage_factory_ref();
   virtual void SetUp() override;
   virtual void TearDown() override;
   };
}



