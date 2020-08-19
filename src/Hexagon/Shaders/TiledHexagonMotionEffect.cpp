

#include <Hexagon/Shaders/TiledHexagonMotionEffect.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Shaders
{


TiledHexagonMotionEffect::TiledHexagonMotionEffect()
   : Hexagon::Shaders::Base(obtain_vertex_source(), obtain_fragment_source())
   , initialized(false)
{
}


TiledHexagonMotionEffect::~TiledHexagonMotionEffect()
{
}


void TiledHexagonMotionEffect::initialize()
{
if (!initialized) Hexagon::Shaders::Base::initialize();
initialized = true;

}

void TiledHexagonMotionEffect::activate()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "TiledHexagonMotionEffect" << "::" << "activate" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
Hexagon::Shaders::Base::activate();

}

void TiledHexagonMotionEffect::deactivate()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "TiledHexagonMotionEffect" << "::" << "deactivate" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
Hexagon::Shaders::Base::deactivate();

}

void TiledHexagonMotionEffect::set_flat_color(ALLEGRO_COLOR flat_color)
{
Shader:set_vec3("tint", flat_color.r, flat_color.g, flat_color.b);
Shader::set_float("tint_intensity", 1.0);

}

void TiledHexagonMotionEffect::set_texture_width(int width)
{
Shader::set_int("texture_width", width);

}

void TiledHexagonMotionEffect::set_texture_height(int height)
{
Shader::set_int("texture_height", height);

}

void TiledHexagonMotionEffect::set_nyan_cat_texture(ALLEGRO_BITMAP* nyan_cat_texture)
{
Shader::set_sampler("nyan_cat_texture", nyan_cat_texture, 1);

}

void TiledHexagonMotionEffect::set_time(float time)
{
Shader::set_float("time", time);

}

std::string TiledHexagonMotionEffect::obtain_vertex_source()
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

std::string TiledHexagonMotionEffect::obtain_fragment_source()
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

  float HexDist(vec2 p)
  {
     p = abs(p);
     float c = dot(p, normalize(vec2(1,1.73)));
     c = max(c, p.x);
     return c;
  }

  vec4 HexCoords(vec2 uv)
  {
     vec2 r = vec2(1, 1.73);
     vec2 h = r*.5;
     vec2 a = mod(uv, r)-h;
     vec2 b = mod(uv-h, r)-h;

     vec2 gv;
     if (length(a) < length(b))
        gv = a;
     else
        gv = b;

     float x = atan(gv.x, gv.y);
     float y = 0.5-HexDist(gv);
     vec2 id = uv-gv;
     return vec4(x, y, id.x, id.y);
  }

  void main()
  {
     // https://www.youtube.com/watch?v=VmrIDyYiJBA


     vec2 resolution = vec2(texture_width, texture_height);
     vec2 uv = ((varying_texcoord - 0.5) * resolution.xy) / resolution.y;
     vec3 col = vec3(0.);


     //uv *= 5.;
     uv *= 6.;

     vec4 hc = HexCoords(uv);
     float c = smoothstep(.055, .06, hc.y*sin(hc.z*hc.w+time));

     col += c;


     gl_FragColor = vec4(col, 1.);
  }
)DELIM";
return source;

}
} // namespace Shaders
} // namespace Hexagon


