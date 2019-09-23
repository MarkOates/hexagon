

#include <Hexagon/OldFileSystemNode.hpp>


OldFileSystemNode::OldFileSystemNode(ALLEGRO_FS_ENTRY *entry)
   : entry(entry)
   , children({})
{
}

OldFileSystemNode::OldFileSystemNode(std::string entry_filename)
   : entry(nullptr)
   , children({})
{
   entry = al_create_fs_entry(entry_filename.c_str());
   if (!entry) throw std::runtime_error("OldFileSystemNode::ctor: could not create fs_entry");
}

OldFileSystemNode::~OldFileSystemNode()
{
   al_destroy_fs_entry(entry);
   for (auto &child : children) delete child;
}

ALLEGRO_FS_ENTRY *OldFileSystemNode::get_entry() { return entry; }

void OldFileSystemNode::create_children()
{
   for (auto &child : children) delete child;
   children.clear();

   this->children = OldFileSystemNode::create_fs_entry_children(this);
}

std::vector<OldFileSystemNode *> &OldFileSystemNode::get_children_ref()
{
   return children;
}

int OldFileSystemNode::infer_num_children()
{
   return children.size();
}

bool OldFileSystemNode::infer_is_directory() const
{
   return (al_get_fs_entry_mode(entry) & ALLEGRO_FILEMODE_ISDIR) == ALLEGRO_FILEMODE_ISDIR;
}

std::string OldFileSystemNode::infer_full_name() const
{
   return al_get_fs_entry_name(entry);
}

std::string OldFileSystemNode::infer_folder_name()
{
   ALLEGRO_PATH *path = al_create_path(infer_full_name().c_str());
   if (!path) throw std::runtime_error("infer_folder_name(): cannot create path");
   std::string folder_name = al_get_path_tail(path);
   al_destroy_path(path);
   return folder_name;
}

std::string OldFileSystemNode::infer_basename()
{
   ALLEGRO_PATH *path = al_create_path(infer_full_name().c_str());
   if (!path) throw std::runtime_error("infer_basename(): cannot create path");
   std::string filename = al_get_path_filename(path);
   al_destroy_path(path);
   return filename;
}

std::string OldFileSystemNode::infer_parent()
{
   ALLEGRO_PATH *path = al_create_path(infer_full_name().c_str());
   if (!path) throw std::runtime_error("infer_parent(): cannot create path");
   al_drop_path_tail(path);
   std::string parent_directory = al_get_path_filename(path);
   al_destroy_path(path);
   return parent_directory;
}

//
//

std::vector<OldFileSystemNode *> OldFileSystemNode::create_fs_entry_children(OldFileSystemNode *node)
{
   std::vector<OldFileSystemNode *> results;

   if(al_open_directory(node->get_entry()))
   {
      ALLEGRO_FS_ENTRY* fs_entry;
      while((fs_entry = al_read_directory(node->get_entry())))
      {
         results.push_back(new OldFileSystemNode(fs_entry));
         std::sort(results.begin(), results.end(), file_system_order_compare);
      }
   }
   else
   {
   }

   //std::sort(results.begin(), results.end());

   return results;
}


///


bool file_system_order_compare(OldFileSystemNode const *a, OldFileSystemNode const *b)
{
   if (a->infer_is_directory() != b->infer_is_directory())
   {
      if (a->infer_is_directory()) return true;
      return false;
   }
   else
   {
     return strcmp(a->infer_full_name().c_str(), b->infer_full_name().c_str()) < 0;
   }
}


