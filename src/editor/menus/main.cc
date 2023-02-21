#include <imgui/imgui.h>

#include "main.h"

namespace Konto::Editor
{

MainMenuData MainMenu::context_{};

void MainMenu::render()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Scene"))
            {
            }
            if (ImGui::MenuItem("Open Scene"))
            {
            }
            if (ImGui::MenuItem("Save"))
            {
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Settings"))
        {
            if (ImGui::MenuItem("Runtime"))
            {
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

} // namespace Konto::Editor
