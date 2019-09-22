#include <allegro5/allegro.h>
#include <vector>
#include <string>


class OldFileSystemNode
{
private:
   ALLEGRO_FS_ENTRY *entry;
   std::vector<OldFileSystemNode *> children;

public:
   OldFileSystemNode(ALLEGRO_FS_ENTRY *entry);
   ~OldFileSystemNode();

   ALLEGRO_FS_ENTRY *get_entry();

   void create_children();

   std::vector<OldFileSystemNode *> &get_children_ref();
   int infer_num_children();
   bool infer_is_directory() const;
   std::string infer_full_name() const;
   std::string infer_folder_name();
   std::string infer_basename();
   std::string infer_parent();

   static std::vector<OldFileSystemNode *> create_fs_entry_children(OldFileSystemNode *node);
};

bool file_system_order_compare(OldFileSystemNode const *a, OldFileSystemNode const *b);
