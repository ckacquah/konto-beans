#include <fstream>
#include <string>

#include <imgui/imgui.h>

#include "dialogs.h"
#include "editor/context.h"
#include "main.h"

namespace Konto::Editor
{

MainMenuData MainMenu::context_{};

void MainMenu::init(const std::shared_ptr<EditorContext>& editor)
{
    context_.editor = editor;
}

void MainMenu::render()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Scene"))
            {
                context_.editor->scene_path = "";
                context_.editor->scene = nullptr;
                context_.editor->scene = std::make_shared<Scene>();
                context_.editor->active_entity = Entity();
            }
            if (ImGui::MenuItem("Open Scene"))
            {
                context_.editor->scene_path = FileDialog::open("", {{"Konto Scene File", "konto"}});

                if (!context_.editor->scene_path.empty())
                {
                    std::ifstream project_file;
                    project_file.open(context_.editor->scene_path, std::ios::binary | std::ios::in);
                    project_file.seekg(0, std::ios::end);
                    size_t length = project_file.tellg();
                    project_file.seekg(0, std::ios::beg);
                    char* data = new char[length];

                    project_file.read(data, length);
                    project_file.close();

                    context_.editor->scene = nullptr;
                    context_.editor->scene = SceneSerializer::deserialize((uint8_t*)data, length);
                    context_.editor->active_entity = Entity();
                }
            }
            if (ImGui::MenuItem("Save Scene"))
            {
                if (!context_.editor->scene_path.empty())
                {
                    context_.editor->scene_path = FileDialog::save("", "scene.konto", {{"Konto Scene File", "konto"}});
                }
                if (context_.editor->scene != nullptr)
                {
                    std::ofstream project_file;
                    project_file.open(context_.editor->scene_path, std::ios::binary | std::ios::out);

                    auto [data, length] = SceneSerializer::serialize(*context_.editor->scene);

                    project_file.write((char*)data.get(), length);
                    project_file.close();
                }
            }
            if (ImGui::MenuItem("Save Scene As"))
            {
                context_.editor->scene_path = FileDialog::save("", "scene.konto", {{"Konto Scene File", "konto"}});

                if (!context_.editor->scene_path.empty() && context_.editor->scene != nullptr)
                {
                    std::ofstream project_file;
                    project_file.open(context_.editor->scene_path, std::ios::binary | std::ios::out);

                    auto [data, length] = SceneSerializer::serialize(*context_.editor->scene);

                    project_file.write((char*)data.get(), length);
                    project_file.close();
                }
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
