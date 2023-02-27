#ifndef __KONTO_EDITOR_MENUS_DIALOGS_H__
#define __KONTO_EDITOR_MENUS_DIALOGS_H__

#include <string>
#include <tuple>
#include <vector>

namespace Konto::Editor
{

class FileDialog
{
  public:
    static std::string open(const std::string& folderpath,
                            const std::vector<std::tuple<std::string, std::string>>& filters);
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_MENUS_DIALOGS_H__
