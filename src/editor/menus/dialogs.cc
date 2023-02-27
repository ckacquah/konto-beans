#include <stdexcept>

#include <nfd.h>

#include "dialogs.h"

namespace Konto::Editor
{

std::string FileDialog::open(const std::string& folderpath,
                             const std::vector<std::tuple<std::string, std::string>>& filters)
{
    NFD_Init();

    nfdchar_t* outPath;
    nfdfilteritem_t* filters_ = new nfdfilteritem_t[filters.size()];
    for (int i = 0; i < filters.size(); i++)
    {
        nfdfilteritem_t filter_item;
        filter_item.name = std::get<0>(filters[i]).c_str();
        filter_item.spec = std::get<1>(filters[i]).c_str();
        filters_[i] = filter_item;
    }

    nfdresult_t result = NFD_OpenDialog(&outPath, filters_, filters.size(), NULL);

    if (result == NFD_OKAY)
    {
        auto result = std::string(outPath);
        delete[] filters_;
        NFD_Quit();
        NFD_FreePath(outPath);
        return result;
    }
    else if (result == NFD_ERROR)
    {
        printf("Error: %s\n", NFD_GetError());
    }

    throw std::runtime_error("Failed to open file");
}

} // namespace Konto::Editor
