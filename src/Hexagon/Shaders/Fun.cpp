

#include <Hexagon/Shaders/Fun.hpp>
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
  uniform float tint_intensity;
  uniform vec3 tint;
  varying vec4 varying_color;
  varying vec2 varying_texcoord;
  uniform int texture_width;
  uniform int texture_height;
  //float texture_width;
  //float texture_height;
  //float texelSize;

  void main()
  {
     vec4 tmp = texture2D(al_tex, varying_texcoord);
     float inverse_tint_intensity = 1.0 - tint_intensity;
     tmp.r = (tmp.r * inverse_tint_intensity + tint.r * tint_intensity) * tmp.a;
     tmp.g = (tmp.g * inverse_tint_intensity + tint.g * tint_intensity) * tmp.a;
     tmp.b = (tmp.b * inverse_tint_intensity + tint.b * tint_intensity) * tmp.a;
     tmp.a = tmp.a;

     //ivec2 textureSize2d = textureSize(al_tex,0);

     vec2 uv = varying_texcoord.xy / 1.0;
     uv -= 0.5;
     uv.x *= (float(texture_width)/float(texture_height));
     float d = length(uv);
     float c = d;

     if (d < .3) c = 1.; else c = 0.;

     //gl_FragColor = vec4(uv.x, uv.y, 0, 1.);
     gl_FragColor = vec4(vec3(c), 1.);
  }
)DELIM";
return source;

}
} // namespace Shaders
} // namespace Hexagon


