

#include <Hexagon/Shaders/TruchetVineSquiggle.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace Shaders
{


TruchetVineSquiggle::TruchetVineSquiggle()
   : Hexagon::Shaders::Base(obtain_vertex_source(), obtain_fragment_source())
   , initialized(false)
{
}


TruchetVineSquiggle::~TruchetVineSquiggle()
{
}


void TruchetVineSquiggle::initialize()
{
   if (!initialized) Hexagon::Shaders::Base::initialize();
   initialized = true;
}

void TruchetVineSquiggle::activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TruchetVineSquiggle::activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TruchetVineSquiggle::activate: error: guard \"initialized\" not met");
   }
   Hexagon::Shaders::Base::activate();
}

void TruchetVineSquiggle::deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TruchetVineSquiggle::deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TruchetVineSquiggle::deactivate: error: guard \"initialized\" not met");
   }
   Hexagon::Shaders::Base::deactivate();
}

void TruchetVineSquiggle::set_flat_color(ALLEGRO_COLOR flat_color)
{
   Shader:set_vec3("tint", flat_color.r, flat_color.g, flat_color.b);
   Shader::set_float("tint_intensity", 1.0);
}

void TruchetVineSquiggle::set_texture_width(int width)
{
   Shader::set_int("texture_width", width);
}

void TruchetVineSquiggle::set_texture_height(int height)
{
   Shader::set_int("texture_height", height);
}

void TruchetVineSquiggle::set_time(float time)
{
   Shader::set_float("time", time);
}

std::string TruchetVineSquiggle::obtain_vertex_source()
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

std::string TruchetVineSquiggle::obtain_fragment_source()
{
   static const std::string source = R"DELIM(
     uniform sampler2D al_tex;
     uniform float tint_intensity;
     uniform vec3 tint;
     varying vec4 varying_color;
     varying vec2 varying_texcoord; // 0 ... n number of pixels
     uniform int texture_width;
     uniform int texture_height;
     uniform float time;

     float Hash21(vec2 p) {
        p = fract(p*vec2(234.34, 435.345));
        p += dot(p, p+34.23);
        return fract(p.x*p.y);
     }

     void main()
     {
        vec2 resolution = vec2(texture_width, texture_height);
        vec2 uv = (varying_texcoord*resolution.xy) / resolution.y;

        vec3 col = vec3(0.);

        //uv += time * .2;
        uv *= 5.;
        vec2 gv = fract(uv) - 0.5;
        vec2 id = floor(uv);

        float n = Hash21(id); // random number between 0 and 1
        float width = .1;

        // https://www.youtube.com/watch?v=2R7h76GoIJM

        if (n<.5) gv.x *= -1.;
        float d = abs(abs(gv.x + gv.y)-.5);

        vec2 cUv = gv-sign(gv.x+gv.y+.001)*.5;
        d = length(cUv)-.5;
        float mask = smoothstep(.01, -.01, abs(d)-width);

        float angle = atan(cUv.x, cUv.y); // -pi to pi
        float checker = mod(id.x+id.y, 2.)*2.-1.;
        float flow = sin(time + checker * angle * 10.);
        col += flow*mask;
        //col += n;
        //col.rg += id * .3;

        //col += checker;
        //if (gv.x > .48 || gv.y > .48) col = vec3(1,0,0);

        gl_FragColor = vec4(col, 1.);
     }
   )DELIM";
   return source;
}


} // namespace Shaders
} // namespace Hexagon


