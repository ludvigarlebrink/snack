#include "EditorManager.hpp"

namespace snack
{
IEditorSceneManager* EditorManager::m_editorSceneManager = nullptr;
IEditorWindowManager* EditorManager::m_editorWindowManager = nullptr;

IEditorSceneManager* EditorManager::Scene()
{
    return m_editorSceneManager;
}

IEditorWindowManager* EditorManager::Window()
{
    return m_editorWindowManager;
}
}
