#include "Components/Rendering/CameraComponent.hpp"
#include "Manager.hpp"
#include "SketchInclude.hpp"
#include "Transform.hpp"
#include "UtilsInclude.hpp"

namespace snack
{
CameraComponent::CameraComponent(Transform* transform)
    : BaseComponent(transform)
    , m_projection(Projection::PERSPECTIVE)
    , m_renderMode(RenderMode::FORWARD)
    , m_fieldOfView(45.0f)
    , m_farPlane(1000.0f)
    , m_nearPlane(0.1f)
    , m_size(20.0f)
{
    Manager::Render()->RegisterCameraComponent(this);
}

CameraComponent::~CameraComponent()
{
    Manager::Render()->DeregisterCameraComponent(this);
}

std::string CameraComponent::GetComponentID()
{
    return CLASS_NAME(CameraComponent);
}

f32 CameraComponent::GetFarPlane() const
{
    return m_farPlane;
}

f32 CameraComponent::GetFieldOfView() const
{
    return m_fieldOfView;
}

f32 CameraComponent::GetNearPlane() const
{
    return m_nearPlane;
}

CameraComponent::Projection CameraComponent::GetProjection() const
{
    return m_projection;
}

glm::mat4 CameraComponent::GetProjectionMatrix(f32 width, f32 height) const
{
    switch (m_projection)
    {
    case Projection::ORTHOGRAPHIC:
    {
        f32 aspect = width / height;
        return glm::ortho(m_size * aspect * -0.5f, m_size * aspect * 0.5f, m_size * -0.5f, m_size * 0.5f, m_nearPlane, m_farPlane);
    }
    case Projection::PERSPECTIVE:
    {
        return glm::perspective(m_fieldOfView, width / height, m_nearPlane, m_farPlane);
    }
    default:
        break;
    }

    return glm::mat4(1.0);
}

CameraComponent::RenderMode CameraComponent::GetRenderMode() const
{
    return m_renderMode;
}

glm::mat4 CameraComponent::GetViewMatrix() const
{
    glm::mat4 model = GetTransform()->GetWorldMatrix();
    return glm::lookAt(glm::vec3(model[3]), glm::vec3(model[0]) + glm::vec3(model[3]), glm::vec3(0.0f, 1.0f, 0.0f));
}

void CameraComponent::Load(cereal::JSONInputArchive& archive)
{
    BaseComponent::Load(archive);

    uint32 projection;
    uint32 renderMode;

    archive(
        cereal::make_nvp("projection", projection),
        cereal::make_nvp("renderMode", renderMode),
        cereal::make_nvp("fieldOfView", m_fieldOfView),
        cereal::make_nvp("nearPlane", m_nearPlane),
        cereal::make_nvp("farPlane", m_farPlane),
        cereal::make_nvp("size", m_size)
    );

    m_projection = static_cast<Projection>(projection);
    m_renderMode = static_cast<RenderMode>(renderMode);
}

#ifdef SPY_EDITOR
void CameraComponent::OnEditorGizmo()
{
    glm::mat4 model = GetTransform()->GetWorldMatrix();
    // @todo
}

void CameraComponent::OnEditorInspector()
{
    BaseComponent::OnEditorInspector();

    Sketch::FloatField("Near Plane", m_nearPlane);
    Sketch::FloatField("Far Plane", m_farPlane);

    std::string selectedRenderMode;
    if (m_renderMode == RenderMode::FORWARD)
    {
        selectedRenderMode = "Forward";
    }
    else
    {
        selectedRenderMode = "Deferred";
    }

    if (SketchCombo::Begin("Render Mode", selectedRenderMode))
    {
        if (SketchCombo::Selectable("Forward"))
        {
            m_renderMode = RenderMode::FORWARD;
        }

        if (SketchCombo::Selectable("Deferred"))
        {
            m_renderMode = RenderMode::DEFERRED;
        }

        SketchCombo::End();
    }

    
    std::string selectedProjection;
    if (m_projection == Projection::ORTHOGRAPHIC)
    {
        selectedProjection = "Orthographic";
    }
    else
    {
        selectedProjection = "Perspective";
    }

    if (SketchCombo::Begin("Projection", selectedProjection))
    {
        if (SketchCombo::Selectable("Orthographic"))
        {
            m_projection = Projection::ORTHOGRAPHIC;
        }
    
        if (SketchCombo::Selectable("Perspective"))
        {
            m_projection = Projection::PERSPECTIVE;
        }
    
        SketchCombo::End();
    }

    if (m_projection == Projection::ORTHOGRAPHIC)
    {
        Sketch::FloatField("Size", m_size);
    }
    else
    {
        Sketch::FloatField("Field of View", m_size);
    }
}
#endif

void CameraComponent::Save(cereal::JSONOutputArchive& archive)
{
    BaseComponent::Save(archive);

    archive(
        cereal::make_nvp("projection", static_cast<uint32>(m_projection)),
        cereal::make_nvp("renderMode", static_cast<uint32>(m_renderMode)),
        cereal::make_nvp("fieldOfView", m_fieldOfView),
        cereal::make_nvp("nearPlane", m_nearPlane),
        cereal::make_nvp("farPlane", m_farPlane),
        cereal::make_nvp("size", m_size)
    );
}

void CameraComponent::SetFarPlane(f32 farPlane)
{
    m_farPlane = farPlane;
}

void CameraComponent::SetFieldOfView(f32 fieldOfView)
{
    m_fieldOfView = fieldOfView;
}

void CameraComponent::SetNearPlane(f32 nearPlane)
{
    m_nearPlane = nearPlane;
}

void CameraComponent::SetProjection(Projection projection)
{
    m_projection = projection;
}

void CameraComponent::SetRenderMode(RenderMode renderMode)
{
    m_renderMode = renderMode;
}

void CameraComponent::SetSize(f32 size)
{
    m_size = size;
}
} // namespace snack
