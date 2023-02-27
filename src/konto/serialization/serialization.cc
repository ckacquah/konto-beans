#include <flatbuffers/flatbuffers.h>

#include "konto/serialization/serialization.h"

namespace Konto
{

std::shared_ptr<Scene> SceneSerializer::deserialize(const uint8_t* buffer, size_t size)
{
    auto verifier = flatbuffers::Verifier(buffer, size);
    if (Serializable::VerifySceneBuffer(verifier))
    {
        auto scene = Serializable::GetScene(buffer);
        return std::make_shared<Scene>(convert(*scene));
    }
    throw std::runtime_error("Buffer is not serializable");
}

std::tuple<std::shared_ptr<uint8_t[]>, size_t> SceneSerializer::serialize(Scene& scene)
{
    flatbuffers::FlatBufferBuilder builder;
    auto _scene = convert(builder, scene);
    size_t size = builder.GetSize();
    std::shared_ptr<uint8_t[]> buffer{new uint8_t[size]};
    std::memcpy(buffer.get(), builder.GetBufferPointer(), size);
    return {buffer, size};
}

} // namespace Konto
