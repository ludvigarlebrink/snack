#include "FolderNode.hpp"

#include <algorithm>
#include <filesystem>
#include <iostream>

namespace snack
{
FolderNode::FolderNode(const std::string& folderpath)
{
    SetUp(folderpath, folderpath.size(), nullptr);
}

FolderNode::FolderNode(const std::string& folderpath, int32 offset, FolderNode* parent)
{
    SetUp(folderpath, offset, parent);
}

FolderNode::~FolderNode()
{
    for (auto c : m_children)
    {
        delete c;
    }
}

FolderNode* FolderNode::GetChild(int32 index) const
{
    return m_children[index];
}

int32 FolderNode::GetChildCount() const
{
    return m_children.size();
}

FolderNode::FileInfo FolderNode::GetFileInfo(int32 index) const
{
    return m_fileInfos[index];
}
int32 FolderNode::GetFileInfoCount() const
{
    return m_fileInfos.size();
}

std::string FolderNode::GetFullRelativePath() const
{
    return m_fullRelativePath;
}

std::string FolderNode::GetName() const
{
    return m_name;
}

std::string FolderNode::GetRelativePath() const
{
    return m_relativePath;
}

bool FolderNode::IsLeaf() const
{
    return m_children.empty();
}

void FolderNode::SetUp(const std::string& folderpath, int32 offset, FolderNode* parent)
{
    int32 count = std::count(folderpath.begin(), folderpath.end(), '/');

    if (count == 0)
    {
        m_name = folderpath;
        m_fullRelativePath = folderpath;
        m_fullRelativePath.append("/");
    }
    else if (count == 1)
    {
        m_name = folderpath.substr(0, folderpath.find_last_of('/'));
        m_fullRelativePath = folderpath;
    }
    else
    {
        m_name = folderpath.substr(0, folderpath.find_last_of('/'));
        m_name = m_name.substr(m_name.find_last_of('/') + 1);
        m_fullRelativePath = folderpath;
    }

    m_relativePath = m_fullRelativePath.substr(offset);

    for (const auto& entry : std::filesystem::directory_iterator(m_fullRelativePath))
    {
        if (entry.is_regular_file())
        {
            FileInfo fileInfo;
            std::string relativePath = entry.path().generic_u8string();
            std::string name = relativePath.substr(relativePath.find_last_of("/") + 1);
            fileInfo.name = name.substr(0, name.find_first_of('.'));
            fileInfo.extension = name.substr(name.find_first_of('.'));
            fileInfo.fullRelativePath = relativePath;
            fileInfo.relativePath = relativePath.substr(offset);
            m_fileInfos.push_back(fileInfo);
        }
        else if (entry.is_directory())
        {
            FolderNode* child = new FolderNode(entry.path().generic_u8string() + "/", offset, this);
            m_children.push_back(child);
        }
    }
}
} // namespace snack
