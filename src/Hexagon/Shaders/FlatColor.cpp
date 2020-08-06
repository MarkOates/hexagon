

#include <Hexagon/Shaders/FlatColor.hpp>



namespace Hexagon
{
namespace Shaders
{


FlatColor::FlatColor()
   : Hexagon::Shaders::Base(obtain_vertex_source(), obtain_fragment_source())
   , initialized(false)
{
}


FlatColor::~FlatColor()
{
}


void FlatColor::initialize()
{
if (!initialized) Hexagon::Shaders::Base::initialize();
initialized = true;

}

void FlatColor::activate()
{
if (!initialized)
{
   throw std::runtime_error("[Shaders::FlatColor] Attempting to activate() shader before it has been initialized");
}
Hexagon::Shaders::Base::activate();

}

void FlatColor::set_flat_color(ALLEGRO_COLOR flat_color)
{
Shader:set_vec3("tint", flat_color.r, flat_color.g, flat_color.b);
Shader::set_float("tint_intensity", 1.0);

}

std::string FlatColor::obtain_vertex_source()
{
static const std::string source = R"DELIM(
  attribute vec4 al_pos;
  attribute vec4 al_color;
  attribute vec2 al_texcoord;
  uniform mat4 al_projview_matrix;
  varying vec4 varying_color;
  varying vec2 varying_texcoord;

  void main()
  {
     varying_color = al_color;
     varying_texcoord = al_texcoord;
     gl_Position = al_projview_matrix * al_pos;
  }
)DELIM";
return source;

}

std::string FlatColor::obtain_fragment_source()
{
static const std::string source = R"DELIM(
  uniform sampler2D al_tex;
  uniform float tint_intensity;
  uniform vec3 tint;
  varying vec4 varying_color;
  varying vec2 varying_texcoord;

  void main()
  {
     vec4 tmp = texture2D(al_tex, varying_texcoord);
     float inverse_tint_intensity = 1.0 - tint_intensity;
     tmp.r = (tmp.r * inverse_tint_intensity + tint.r * tint_intensity) * tmp.a;
     tmp.g = (tmp.g * inverse_tint_intensity + tint.g * tint_intensity) * tmp.a;
     tmp.b = (tmp.b * inverse_tint_intensity + tint.b * tint_intensity) * tmp.a;
     tmp.a = tmp.a;
     gl_FragColor = tmp;
  }
)DELIM";
return source;

}
} // namespace Shaders
} // namespace Hexagon


