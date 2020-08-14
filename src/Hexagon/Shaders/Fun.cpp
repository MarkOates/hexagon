

#include <Hexagon/Shaders/Fun.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Shaders
{


Fun::Fun()
   : Hexagon::Shaders::Base(obtain_vertex_source(), obtain_fragment_source())
   , initialized(false)
{
}


Fun::~Fun()
{
}


void Fun::initialize()
{
if (!initialized) Hexagon::Shaders::Base::initialize();
initialized = true;

}

void Fun::activate()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Fun" << "::" << "activate" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
Hexagon::Shaders::Base::activate();

}

void Fun::deactivate()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Fun" << "::" << "deactivate" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
Hexagon::Shaders::Base::deactivate();

}

void Fun::set_flat_color(ALLEGRO_COLOR flat_color)
{
Shader:set_vec3("tint", flat_color.r, flat_color.g, flat_color.b);
Shader::set_float("tint_intensity", 1.0);

}

void Fun::set_texture_width(int width)
{
Shader::set_int("texture_width", width);

}

void Fun::set_texture_height(int height)
{
Shader::set_int("texture_height", height);

}

void Fun::set_nyan_cat_texture(ALLEGRO_BITMAP* nyan_cat_texture)
{
Shader::set_sampler("nyan_cat_texture", nyan_cat_texture, 1);

}

void Fun::set_time(float time)
{
Shader::set_float("time", time);

}

std::string Fun::obtain_vertex_source()
{
static const std::string source = R"DELIM(
  attribute vec4 al_pos;
  attribute vec4 al_color;
  attribute vec2 al_texcoord;
  uniform mat4 al_projview_matrix;
  varying vec4 varying_color;
  varying vec2 varying_texcoord;
  uniform int texture_width;
  uniform int texture_height;
  uniform float time;

  void main()
  {
     varying_color = al_color;
     varying_texcoord = al_texcoord;
     gl_Position = al_projview_matrix * al_pos;
  }
)DELIM";
return source;

}

std::string Fun::obtain_fragment_source()
{
static const std::string source = R"DELIM(
  uniform sampler2D al_tex;
  uniform sampler2D nyan_cat_texture;
  uniform float tint_intensity;
  uniform vec3 tint;
  varying vec4 varying_color;
  varying vec2 varying_texcoord; // 0 ... n number of pixels
  uniform int texture_width;
  uniform int texture_height;
  uniform float time;

  void main()
  {
     vec2 resolution = vec2(texture_width, texture_height);
     vec2 uv = (varying_texcoord*resolution.xy) / resolution.y;
     vec3 col = vec3(0.);
     gl_FragColor = vec4(col, 1.);
  }
)DELIM";
return source;

}
} // namespace Shaders
} // namespace Hexagon


