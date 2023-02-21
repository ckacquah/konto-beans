#ifndef __KONTO_EDITOR_MENUS_MAIN_H__
#define __KONTO_EDITOR_MENUS_MAIN_H__

namespace Konto::Editor
{

struct MainMenuData
{
};

class MainMenu
{
  private:
    static MainMenuData context_;

  public:
    static void render();
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_MENUS_MAIN_H__
