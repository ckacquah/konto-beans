#ifndef __KONTO_EDITOR_CONTEXT_H__
#define __KONTO_EDITOR_CONTEXT_H__

#include "konto.h"

namespace Konto::Editor
{

struct EditorContext
{
    uint32_t width{};
    uint32_t height{};
    std::string scene_path{};

    Entity selected_entity;
    InputContext input{};
    std::shared_ptr<Scene> scene{};

    EditorContext() = default;
    EditorContext(const EditorContext& other) = default;
    EditorContext(uint32_t _width, uint32_t _height) : width(_width), height(_height), scene(std::make_shared<Scene>())
    {
    }
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_CONTEXT_H__
