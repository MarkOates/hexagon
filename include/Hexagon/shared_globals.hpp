#pragma once



#include <string>



extern std::string REGEX_TEMP_FILENAME;
extern std::string CLIPBOARD_TEMP_FILENAME;
extern std::string FILE_NAVIGATOR_SELECTION_FILENAME;
extern std::string FILE_NAVIGATOR_SELECTION_last_content;
extern std::string MAKE_COMMAND_FILENAME;
extern std::string DEFAULT_CONTENT_FILENAME;


extern std::string NOTIFICATION_FILE_IS_UNSAVED;



#include <string>
#include <vector>


extern std::vector<std::string> notifications;

void clear_last_compiled_error_messages();
void set_last_compiled_error_messages(std::string);
std::string get_last_compiled_error_messages();
bool is_last_compiled_error_messages_empty();

void add_notification(std::string notification);
void remove_notification(std::string notification);
void clear_notifications();
