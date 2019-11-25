

#include <Hexagon/FileSystemNode.hpp>


FileSystemNode::FileSystemNode(ALLEGRO_FS_ENTRY *entry)
   : entry(entry)
   , children({})
{
}

FileSystemNode::FileSystemNode(std::string entry_filename)
   : entry(nullptr)
   , children({})
{
   entry = al_create_fs_entry(entry_filename.c_str());
   if (!entry) throw std::runtime_error("FileSystemNode::ctor: could not create fs_entry");
}

FileSystemNode::~FileSystemNode()
{
   al_destroy_fs_entry(entry);
   for (auto &child : children) delete child;
}

ALLEGRO_FS_ENTRY *FileSystemNode::get_entry() { return entry; }

void FileSystemNode::create_children()
{
   for (auto &child : children) delete child;
   children.clear();

   this->children = FileSystemNode::create_fs_entry_children(this);
}

std::vector<FileSystemNode *> &FileSystemNode::get_children_ref()
{
   return children;
}

int FileSystemNode::infer_num_children()
{
   return children.size();
}

bool FileSystemNode::infer_is_directory() const
{
   return (al_get_fs_entry_mode(entry) & ALLEGRO_FILEMODE_ISDIR) == ALLEGRO_FILEMODE_ISDIR;
}

std::string FileSystemNode::infer_full_name() const
{
   return al_get_fs_entry_name(entry);
}

std::string FileSystemNode::infer_folder_name()
{
   ALLEGRO_PATH *path = al_create_path(infer_full_name().c_str());
   if (!path) throw std::runtime_error("infer_folder_name(): cannot create path");
   std::string folder_name = al_get_path_tail(path);
   al_destroy_path(path);
   return folder_name;
}

std::string FileSystemNode::infer_basename()
{
   ALLEGRO_PATH *path = al_create_path(infer_full_name().c_str());
   if (!path) throw std::runtime_error("infer_basename(): cannot create path");
   std::string filename = al_get_path_filename(path);
   al_destroy_path(path);
   return filename;
}


std::string FileSystemNode::infer_parent()
{
   ALLEGRO_PATH *path = al_create_path(infer_full_name().c_str());
   if (!path) throw std::runtime_error("infer_parent(): cannot create path");
   if ((al_get_fs_entry_mode(entry) & ALLEGRO_FILEMODE_ISDIR) == ALLEGRO_FILEMODE_ISDIR)
   {
     al_destroy_path(path);
     path = al_create_path_for_directory(infer_full_name().c_str());
   }
   al_remove_path_component(path, -1);
   std::string parent_directory = al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP);
   al_destroy_path(path);
   return parent_directory;
}

//
//

std::vector<FileSystemNode *> FileSystemNode::create_fs_entry_children(FileSystemNode *node)
{
   std::vector<FileSystemNode *> results;

   if(al_open_directory(node->get_entry()))
   {
      ALLEGRO_FS_ENTRY* fs_entry;
      while((fs_entry = al_read_directory(node->get_entry())))
      {
         results.push_back(new FileSystemNode(fs_entry));
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


bool file_system_order_compare(FileSystemNode const *a, FileSystemNode const *b)
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


