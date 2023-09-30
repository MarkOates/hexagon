

#include <Hexagon/AdvancedComponentNavigator/AdvancedComponentNavigator.hpp>

#include <Blast/StringSplitter.hpp>
#include <Hexagon/AdvancedComponentNavigator/ComponentSearcher.hpp>
#include <Hexagon/ClipboardData.hpp>
#include <algorithm>
#include <allegro_flare/useful_php.h>
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace AdvancedComponentNavigator
{


AdvancedComponentNavigator::AdvancedComponentNavigator(std::string project_root)
   : project_root(project_root)
   , cursor_position(0)
   , cursor_position_static(false)
   , nodes({})
   , mode("navigating_list")
   , search_text("")
{
}


AdvancedComponentNavigator::~AdvancedComponentNavigator()
{
}


void AdvancedComponentNavigator::set_project_root(std::string project_root)
{
   this->project_root = project_root;
}


void AdvancedComponentNavigator::set_cursor_position_static(bool cursor_position_static)
{
   this->cursor_position_static = cursor_position_static;
}


void AdvancedComponentNavigator::set_nodes(std::vector<Blast::Project::Component> nodes)
{
   this->nodes = nodes;
}


void AdvancedComponentNavigator::set_mode(std::string mode)
{
   this->mode = mode;
}


void AdvancedComponentNavigator::set_search_text(std::string search_text)
{
   this->search_text = search_text;
}


std::string AdvancedComponentNavigator::get_project_root() const
{
   return project_root;
}


int AdvancedComponentNavigator::get_cursor_position() const
{
   return cursor_position;
}


bool AdvancedComponentNavigator::get_cursor_position_static() const
{
   return cursor_position_static;
}


std::vector<Blast::Project::Component> AdvancedComponentNavigator::get_nodes() const
{
   return nodes;
}


std::string AdvancedComponentNavigator::get_mode() const
{
   return mode;
}


std::string AdvancedComponentNavigator::get_search_text() const
{
   return search_text;
}


bool AdvancedComponentNavigator::is_mode_navigating_list()
{
   return this->mode == "navigating_list";
}

bool AdvancedComponentNavigator::is_mode_typing_in_search_bar()
{
   return this->mode == "typing_in_search_bar";
}

void AdvancedComponentNavigator::move_cursor_up()
{
   cursor_position -= 1;
}

void AdvancedComponentNavigator::move_cursor_down()
{
   cursor_position += 1;
}

void AdvancedComponentNavigator::move_cursor_to_top()
{
   cursor_position = 0;
}

bool AdvancedComponentNavigator::current_selection_is_valid()
{
   if (cursor_position < 0 || cursor_position >= nodes.size()) return false;
   return true;
}

void AdvancedComponentNavigator::set_mode_to_navigating_list()
{
   this->mode = "navigating_list";
}

void AdvancedComponentNavigator::set_mode_to_typing_in_search_bar()
{
   this->mode = "typing_in_search_bar";
}

std::string AdvancedComponentNavigator::get_current_selection_label_or_empty_string()
{
   if (!current_selection_is_valid()) return "";
   return nodes[get_cursor_position()].get_name();
}

void AdvancedComponentNavigator::refresh_list()
{
   Hexagon::AdvancedComponentNavigator::ComponentSearcher searcher(get_project_root(), search_text);
   nodes = searcher.components_sorted_by_most_recent();
}

void AdvancedComponentNavigator::yank_selected_text_label()
{
   if (!(current_selection_is_valid()))
   {
      std::stringstream error_message;
      error_message << "[AdvancedComponentNavigator::yank_selected_text_label]: error: guard \"current_selection_is_valid()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AdvancedComponentNavigator::yank_selected_text_label: error: guard \"current_selection_is_valid()\" not met");
   }
   std::string selected_text = get_current_selection_label_or_empty_string();
   ClipboardData::store(selected_text);
}

void AdvancedComponentNavigator::yank_selected_text_as_component_name()
{
   if (!(current_selection_is_valid()))
   {
      std::stringstream error_message;
      error_message << "[AdvancedComponentNavigator::yank_selected_text_as_component_name]: error: guard \"current_selection_is_valid()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AdvancedComponentNavigator::yank_selected_text_as_component_name: error: guard \"current_selection_is_valid()\" not met");
   }
   std::string selected_text = get_current_selection_label_or_empty_string();
   std::string filtered_text = php::str_replace("/", "::", selected_text);
   ClipboardData::store(filtered_text);
}

void AdvancedComponentNavigator::yank_selected_text_as_include_directive()
{
   if (!(current_selection_is_valid()))
   {
      std::stringstream error_message;
      error_message << "[AdvancedComponentNavigator::yank_selected_text_as_include_directive]: error: guard \"current_selection_is_valid()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AdvancedComponentNavigator::yank_selected_text_as_include_directive: error: guard \"current_selection_is_valid()\" not met");
   }
   std::string selected_text = get_current_selection_label_or_empty_string();
   std::string filtered_text = "#include <" + selected_text + ".hpp>";
   ClipboardData::store(filtered_text);
}

void AdvancedComponentNavigator::yank_selected_text_as_quintessence_dependency_lines()
{
   if (!(current_selection_is_valid()))
   {
      std::stringstream error_message;
      error_message << "[AdvancedComponentNavigator::yank_selected_text_as_quintessence_dependency_lines]: error: guard \"current_selection_is_valid()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AdvancedComponentNavigator::yank_selected_text_as_quintessence_dependency_lines: error: guard \"current_selection_is_valid()\" not met");
   }
   std::string selected_text = get_current_selection_label_or_empty_string();
   std::string symbol_text = selected_text;
   symbol_text = php::str_replace("/", "::", symbol_text);
   std::string headers_text = "    headers: [ " + selected_text + ".hpp ]";

   std::string text_for_clipboard = "  - symbol: " + symbol_text + "\n" + headers_text; // TODO clean this up

   ClipboardData::store(text_for_clipboard);
}

void AdvancedComponentNavigator::yank_selected_text_as_public_parent_class_lines()
{
   if (!(current_selection_is_valid()))
   {
      std::stringstream error_message;
      error_message << "[AdvancedComponentNavigator::yank_selected_text_as_public_parent_class_lines]: error: guard \"current_selection_is_valid()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AdvancedComponentNavigator::yank_selected_text_as_public_parent_class_lines: error: guard \"current_selection_is_valid()\" not met");
   }
   std::string selected_text = get_current_selection_label_or_empty_string();
   std::string symbol_text = selected_text;
   symbol_text = php::str_replace("/", "::", symbol_text);
   std::string text_for_clipboard = "  - class: " + symbol_text + "\n"
                                  + "    scope: public\n"
                                  + "    init_with: ''\n";

   ClipboardData::store(text_for_clipboard);
}

void AdvancedComponentNavigator::yank_selected_text_as_injected_dependency_property()
{
   if (!(current_selection_is_valid()))
   {
      std::stringstream error_message;
      error_message << "[AdvancedComponentNavigator::yank_selected_text_as_injected_dependency_property]: error: guard \"current_selection_is_valid()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AdvancedComponentNavigator::yank_selected_text_as_injected_dependency_property: error: guard \"current_selection_is_valid()\" not met");
   }
   std::string selected_text = get_current_selection_label_or_empty_string();

   // take the class symbol, store it
   std::string selected_text_as_class = selected_text;
   php::str_replace("/", "::", selected_text_as_class);

   // take the last component, snake_case it
   std::vector<std::string> split_tokens = Blast::StringSplitter(selected_text, '/').split();
   std::string snake_case_name = split_tokens.empty() ? "error_unextractable_component_base_name"
                                                      : convert_to_snake_case(split_tokens[split_tokens.size()-1]);

   // build up the string

   std::string name = snake_case_name;
   std::string type = selected_text_as_class + "*";

   std::stringstream result;
      result << "  - name: " << name << std::endl;
      result << "    type: " << type << std::endl;
      result << "    constructor_arg: true" << std::endl;
      result << "    init_with: nullptr" << std::endl;
      result << "    getter: true" << std::endl;
      result << "    setter: true" << std::endl;
      result << std::endl;
      result << std::endl;
   ClipboardData::store(result.str());
}

void AdvancedComponentNavigator::yank_selected_text_as_error_message_template()
{
   if (!(current_selection_is_valid()))
   {
      std::stringstream error_message;
      error_message << "[AdvancedComponentNavigator::yank_selected_text_as_error_message_template]: error: guard \"current_selection_is_valid()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AdvancedComponentNavigator::yank_selected_text_as_error_message_template: error: guard \"current_selection_is_valid()\" not met");
   }
   std::string selected_text = get_current_selection_label_or_empty_string();

   // take the class symbol, store it
   std::string selected_text_as_class = selected_text;
   php::str_replace("/", "::", selected_text_as_class);

   // take the last component, snake_case it
   std::vector<std::string> split_tokens = Blast::StringSplitter(selected_text, '/').split();
   std::string snake_case_name = split_tokens.empty() ? "error_unextractable_component_base_name"
                                                      : convert_to_snake_case(split_tokens[split_tokens.size()-1]);

   // build up the string

   std::string name = snake_case_name;
   std::string type = selected_text_as_class + "*";

   std::stringstream result;
      result << "         std::stringstream error_message;" << std::endl;
      result << "         error_message << \"" << selected_text_as_class << " error: \"" << std::endl;
      result << "                       << \"THING_THAT_HAPPENED\";" << std::endl;
      result << "         throw std::runtime_error(error_message.str());" << std::endl;
   ClipboardData::store(result.str());
}

void AdvancedComponentNavigator::yank_selected_text_as_static_casted_as()
{
   if (!(current_selection_is_valid()))
   {
      std::stringstream error_message;
      error_message << "[AdvancedComponentNavigator::yank_selected_text_as_static_casted_as]: error: guard \"current_selection_is_valid()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AdvancedComponentNavigator::yank_selected_text_as_static_casted_as: error: guard \"current_selection_is_valid()\" not met");
   }
   std::string selected_text = get_current_selection_label_or_empty_string();

   // take the class symbol, store it
   std::string selected_text_as_class = selected_text;
   php::str_replace("/", "::", selected_text_as_class);

   // take the last component, snake_case it
   //std::vector<std::string> split_tokens = Blast::StringSplitter(selected_text, '/').split();
   //std::string snake_case_name = split_tokens.empty() ? "error_unextractable_component_base_name"
                                                      //: convert_to_snake_case(split_tokens[split_tokens.size()-1]);

   // build up the string

   //std::string name = snake_case_name;
   //std::string type = selected_text_as_class + "*";

   std::stringstream result;
      result << "         if (base->is_type(" << selected_text_as_class << "::TYPE))" << std::endl;
      result << "         {" << std::endl;
      result << "            " << selected_text_as_class << " *as =" << std::endl;
      result << "               static_cast<" << selected_text_as_class << "*>(base);" << std::endl;
      result << "         }" << std::endl;

      //result << "
      //result << "         std::stringstream error_message;" << std::endl;
      //result << "         error_message << \"" << selected_text_as_class << " error: \"" << std::endl;
      //result << "                       << \"THING_THAT_HAPPENED\";" << std::endl;
      //result << "         throw std::runtime_error(error_message.str());" << std::endl;
   ClipboardData::store(result.str());
}

std::string AdvancedComponentNavigator::convert_to_snake_case(std::string source_str)
{
   std::string camelCase = source_str;
   // Convert lowerCamelCase and UpperCamelCase strings to lower_with_underscore.
   std::string str(1, tolower(camelCase[0]));

   // First place underscores between contiguous lower and upper case letters.
   // For example, `_LowerCamelCase` becomes `_Lower_Camel_Case`.
   for (auto it = camelCase.begin() + 1; it != camelCase.end(); ++it) {
     if (isupper(*it) && *(it-1) != '_' && islower(*(it-1))) {
       str += "_";
     }
     str += *it;
   }

   // Then convert it to lower case.
   std::transform(str.begin(), str.end(), str.begin(), ::tolower);

   return str;
}


} // namespace AdvancedComponentNavigator
} // namespace Hexagon


