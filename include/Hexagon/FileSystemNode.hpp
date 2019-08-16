#include <allegro5/allegro.h>
#include <vector>
#include <string>


class FileSystemNode
{
private:
   ALLEGRO_FS_ENTRY *entry;
   std::vector<FileSystemNode *> children;

public:
   FileSystemNode(ALLEGRO_FS_ENTRY *entry);
   ~FileSystemNode();

   ALLEGRO_FS_ENTRY *get_entry();

   void create_children();

   std::vector<FileSystemNode *> &get_children_ref();
   int infer_num_children();
   bool infer_is_directory() const;
   std::string infer_full_name() const;
   std::string infer_folder_name();
   std::string infer_basename();

   static std::vector<FileSystemNode *> create_fs_entry_children(FileSystemNode *node);
};

bool file_system_order_compare(FileSystemNode const *a, FileSystemNode const *b);
