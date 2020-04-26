

#include <Hexagon/SymlinkToucher.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/Project/SymlinkChecker.hpp>
#include <Blast/FileExistenceChecker.hpp>


namespace Hexagon
{


SymlinkToucher::SymlinkToucher(std::string filename)
   : filename(filename)
{
}


SymlinkToucher::~SymlinkToucher()
{
}


void SymlinkToucher::touch_if_symlink()
{
bool file_exists = Blast::FileExistenceChecker(filename).exists();
if (!file_exists) return;

bool is_symlink = Blast::Project::SymlinkChecker(filename).is_symlink();
if (!is_symlink) return;

std::string command = std::string("touch -h -c ") + filename;
Blast::ShellCommandExecutorWithCallback executor(command);
executor.execute();
return;

}
} // namespace Hexagon


