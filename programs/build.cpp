#include <allegro5/allegro.h> // for compatibility with union/Makefile
#include <Hexagon/BuildSystem/BuildFactory.hpp>
#include <Hexagon/BuildSystem/ReportRenderer.hpp>
#include <iostream>


int main(int argc, char **argv)
{
   Hexagon::BuildSystem::BuildFactory build_factory;
   Hexagon::BuildSystem::Builds::Base* build = build_factory.create_make_quintessence_build();
   build->run();

   Hexagon::BuildSystem::ReportRenderer report_renderer(build);
   std::cout << report_renderer.build_text_report() << std::endl;

   return 0;
}


