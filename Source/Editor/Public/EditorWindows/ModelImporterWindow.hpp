#pragma once

#include "EditorWindow.hpp"

#include <glm/glm.hpp>
#include <vector>

namespace snack
{
class EDITOR_API ModelImporterWindow final : public EditorWindow
{
public:

    ModelImporterWindow();

    ~ModelImporterWindow();

    std::string GetTitle() override;

    void SetFile(const std::string& filepath);

protected:

    void OnDraw(f32 deltaTime) override;

private:

    bool Import();

private:

    bool m_flipTextureCoordiantes;
    bool m_generateNormals;
    bool m_generateTangents;

    std::string m_source;
} // namespace snack
