


#include <Hexagon/shared_globals.hpp>



std::string REGEX_TEMP_FILENAME = "regex.txt";
std::string CLIPBOARD_TEMP_FILENAME = "clipboard.txt";
std::string FILE_NAVIGATOR_SELECTION_FILENAME = "file_navigator_selection.txt";
std::string FILE_NAVIGATOR_SELECTION_last_content = "";
std::string MAKE_COMMAND_FILENAME = "make_command.txt";
std::string DEFAULT_CONTENT_FILENAME = "default.txt";


std::string NOTIFICATION_FILE_IS_UNSAVED = "file is unsaved";



std::vector<std::string> notifications = {};

void add_notification(std::string notification)
{
   notifications.push_back(notification);
}

void remove_notification(std::string notification)
{
   notifications.push_back(notification);
}

void clear_notifications()
{
   notifications.clear();
}


