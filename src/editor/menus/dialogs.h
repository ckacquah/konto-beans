#ifndef __KONTO_EDITOR_MENUS_DIALOGS_H__
#define __KONTO_EDITOR_MENUS_DIALOGS_H__

#include <string>
#include <tuple>
#include <vector>

namespace Konto::Editor
{

struct FileDialog
{
    static std::string open(const std::string& folderpath,
                            const std::vector<std::tuple<std::string, std::string>>& filters);
    static std::string save(const std::string& folderpath, const std::string& filename,
                            const std::vector<std::tuple<std::string, std::string>>& filters);
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_MENUS_DIALOGS_H__
