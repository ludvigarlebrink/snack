#pragma once

#include "EditorWindow.hpp"

#include <assimp/scene.h>
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

    void ProcessMesh(aiMesh* mesh);

    void ProcessNode(aiNode* node, const aiScene* scene);

private:

    bool m_flipTextureCoordiantes;
    bool m_generateNormals;
    bool m_generateTangents;

    std::string m_source;
} // namespace snack
