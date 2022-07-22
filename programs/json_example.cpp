
#include <lib/nlohmann/json.hpp>
#include <allegro5/allegro.h>


void to_json(nlohmann::json& j, const ALLEGRO_COLOR& color)
{
   j = nlohmann::json{
      {"r", color.r},
      {"g", color.g},
      {"b", color.b},
      {"a", color.a},
   };
}


void from_json(const nlohmann::json& j, ALLEGRO_COLOR& color)
{
   j.at("r").get_to(color.r);
   j.at("g").get_to(color.g);
   j.at("b").get_to(color.b);
   j.at("a").get_to(color.a);
}




#include <fstream> // for std::ofstream, std::ifstream
#include <iostream> // for std::cout


void write_to_file(std::string json_filename, ALLEGRO_COLOR color)
{
   std::ofstream outfile;
   outfile.open(json_filename, std::ofstream::out);
   nlohmann::json result;

   result["my_color"] = color;

   outfile << std::setw(3) << result << std::endl;
   outfile.close();
}


ALLEGRO_COLOR read_from_file(std::string json_filename)
{
   std::ifstream infile(json_filename);
   nlohmann::json j;
   ALLEGRO_COLOR result_color;

   infile >> j;

   if (!j.contains("my_color"))
   {
      std::cout << "Expecting \"" << json_filename << "\" to contain an object named \"my_color\" but it does not exist." << std::endl;
      return ALLEGRO_COLOR{0, 0, 0, 0};
   }
   else
   {
      j.at("my_color").get_to(result_color);
   }

   return result_color;
}


int main(int argc, char **argv)
{
   std::string my_filename = "/Users/markoates/Repos/hexagon/tmp/foobar.json";
   ALLEGRO_COLOR my_color = ALLEGRO_COLOR{0.2, 0.6, 0.4, 1.0};

   write_to_file(my_filename, my_color);
   ALLEGRO_COLOR color_as_read_from_file = read_from_file(my_filename);

   std::cout << "My color, loaded from a JSON file is:" << std::endl
             << "  r: " << my_color.r << std::endl
             << "  g: " << my_color.g << std::endl
             << "  b: " << my_color.b << std::endl
             << "  a: " << my_color.a << std::endl
             ;

   return 0;
}


