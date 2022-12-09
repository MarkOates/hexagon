

#include <Hexagon/Shaders/Smiley.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace Shaders
{


Smiley::Smiley()
   : Hexagon::Shaders::Base(obtain_vertex_source(), obtain_fragment_source())
   , initialized(false)
{
}


Smiley::~Smiley()
{
}


void Smiley::initialize()
{
   if (!initialized) Hexagon::Shaders::Base::initialize();
   initialized = true;
}

void Smiley::activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Smiley::activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Smiley::activate: error: guard \"initialized\" not met");
   }
   Hexagon::Shaders::Base::activate();
}

void Smiley::set_flat_color(ALLEGRO_COLOR flat_color)
{
   Shader:set_vec3("tint", flat_color.r, flat_color.g, flat_color.b);
   Shader::set_float("tint_intensity", 1.0);
}

void Smiley::set_texture_width(int width)
{
   Shader::set_int("texture_width", width);
}

void Smiley::set_texture_height(int height)
{
   Shader::set_int("texture_height", height);
}

std::string Smiley::obtain_vertex_source()
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

std::string Smiley::obtain_fragment_source()
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

     float Circle(vec2 uv, vec2 p, float r, float blur)
     {
        float d = length(uv-p);
        float c = smoothstep(r, r-blur, d);
        return c;
     }

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

        vec3 col = vec3(0.);
        float mask = Circle(uv, vec2(0.), .4, .05);

        mask -= Circle(uv, vec2(-.13, .2), .07, .01);
        mask -= Circle(uv, vec2(.13, .2), .07, .01);

        float mouth = Circle(uv, vec2(0.), .3, .02);
        mouth -= Circle(uv, vec2(0., 0.1), .3, .02);

        mask -= mouth;
        //col = vec3(mouth);
        col = vec3(1., 1., 0.) * mask;

        gl_FragColor = vec4(col, 1.);
     }
   )DELIM";
   return source;
}


} // namespace Shaders
} // namespace Hexagon


