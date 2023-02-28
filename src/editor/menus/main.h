#ifndef __KONTO_EDITOR_MENUS_MAIN_H__
#define __KONTO_EDITOR_MENUS_MAIN_H__

#include <functional>
#include <memory>

#include "editor/context.h"
#include "konto.h"

namespace Konto::Editor
{

struct MainMenuData
{
    std::shared_ptr<EditorContext> editor{};
};

class MainMenu
{
  private:
    static MainMenuData context_;

  public:
    static void render();
    static void init(const std::shared_ptr<EditorContext>& editor);
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_MENUS_MAIN_H__
