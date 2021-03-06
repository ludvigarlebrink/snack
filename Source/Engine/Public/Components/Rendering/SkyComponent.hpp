#pragma once

#include "Components/BaseComponent.hpp"

namespace snack
{
class ENGINE_API SkyComponent final : public BaseComponent
{
public:

    SkyComponent(Transform* transform);

    ~SkyComponent();

    std::string GetComponentID() override;

    void Load(cereal::JSONInputArchive& archive) override;

    void Save(cereal::JSONOutputArchive& archive) override;
};
} // namespace snack
