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

    Entity active_entity;
    std::shared_ptr<Scene> scene{};

    EditorContext() = default;
    EditorContext(const EditorContext& other) = default;
};

} // namespace Konto::Editor

#endif // __KONTO_EDITOR_CONTEXT_H__
