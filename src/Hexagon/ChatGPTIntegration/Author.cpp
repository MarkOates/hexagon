

#include <Hexagon/ChatGPTIntegration/Author.hpp>




namespace Hexagon
{
namespace ChatGPTIntegration
{


Author::Author(uint32_t id, std::string identifier, std::string display_name, std::string avatar_bitmap_identifier, ALLEGRO_COLOR display_background_color)
   : id(id)
   , identifier(identifier)
   , display_name(display_name)
   , avatar_bitmap_identifier(avatar_bitmap_identifier)
   , display_background_color(display_background_color)
{
}


Author::~Author()
{
}


void Author::set_id(uint32_t id)
{
   this->id = id;
}


void Author::set_identifier(std::string identifier)
{
   this->identifier = identifier;
}


void Author::set_display_name(std::string display_name)
{
   this->display_name = display_name;
}


void Author::set_avatar_bitmap_identifier(std::string avatar_bitmap_identifier)
{
   this->avatar_bitmap_identifier = avatar_bitmap_identifier;
}


void Author::set_display_background_color(ALLEGRO_COLOR display_background_color)
{
   this->display_background_color = display_background_color;
}


uint32_t Author::get_id() const
{
   return id;
}


std::string Author::get_identifier() const
{
   return identifier;
}


std::string Author::get_display_name() const
{
   return display_name;
}


std::string Author::get_avatar_bitmap_identifier() const
{
   return avatar_bitmap_identifier;
}


ALLEGRO_COLOR Author::get_display_background_color() const
{
   return display_background_color;
}




} // namespace ChatGPTIntegration
} // namespace Hexagon


