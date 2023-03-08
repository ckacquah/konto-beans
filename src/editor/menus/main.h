#ifndef __KONTO_EDITOR_MENUS_MAIN_H__
#define __KONTO_EDITOR_MENUS_MAIN_H__

#include <functional>
#include <memory>

#include "editor/context.h"
#include "konto.h"

namespace Konto::Editor
{

struct MainMenuContext
{
    std::shared_ptr<EditorContext> editor{};
};

class MainMenu
{
  private:
    static MainMenuContext context_;

  public:
    static void render();
    static void init(std::shared_ptr<EditorContext> editor);
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_MENUS_MAIN_H__
