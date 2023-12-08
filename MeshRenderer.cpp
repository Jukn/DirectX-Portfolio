#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Game.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"

MeshRenderer::MeshRenderer() : Super(ComponentType::MeshRenderer)
{

}

MeshRenderer::~MeshRenderer()
{

}

//void MeshRenderer::Update()
//{
//	if (_mesh == nullptr || _texture == nullptr || _shader == nullptr)
//		return;
//
//	_shader->GetSRV("Texture0")->SetResource(_texture->GetComPtr().Get());
//
//	auto world = GetTransform()->GetWorldMatrix();
//	RENDER->PushTransformData(TransformDesc{world});
//
//	uint32 stride = _mesh->GetVertexBuffer()->GetStride();
//	uint32 offset = _mesh->GetVertexBuffer()->GetOffset();
//
//	DC->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetComPtr().GetAddressOf(), &stride, &offset);
//	DC->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
//
//	_shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
//}

//void MeshRenderer::Update()
//{
//	if (_mesh == nullptr || _texture == nullptr || _shader == nullptr)
//		return;
//
//	_shader->GetSRV("DiffuseMap")->SetResource(_texture->GetComPtr().Get());
//
//	auto world = GetTransform()->GetWorldMatrix();
//	RENDER->PushTransformData(TransformDesc{ world });
//
//	uint32 stride = _mesh->GetVertexBuffer()->GetStride();
//	uint32 offset = _mesh->GetVertexBuffer()->GetOffset();
//
//	DC->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetComPtr().GetAddressOf(), &stride, &offset);
//	DC->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
//
//	_shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
//}

void MeshRenderer::Update()
{
    auto world = GetTransform()->GetWorldMatrix();
    uint32 stride = 0;
    uint32 offset = 0;

    switch (_meshType)
    {
    case MeshType::Simple:
        if(_simpleMesh == nullptr || _shader == nullptr)
            return;

        RENDER->PushTransformData(TransformDesc{ world });

        stride = _simpleMesh->GetVertexBuffer()->GetStride();
        offset = _simpleMesh->GetVertexBuffer()->GetOffset();

        DC->IASetVertexBuffers(0, 1, _simpleMesh->GetVertexBuffer()->GetComPtr().GetAddressOf(), &stride, &offset);
        DC->IASetIndexBuffer(_simpleMesh->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

        _shader->DrawIndexed(0, 0, _simpleMesh->GetIndexBuffer()->GetCount(), 0, 0);
        break;

    case MeshType::Complex:
        if (_mesh == nullptr || _material == nullptr || _material->GetShader() == nullptr)
            return;

        _material->Update();

        RENDER->PushTransformData(TransformDesc{ world });

        stride = _mesh->GetVertexBuffer()->GetStride();
        offset = _mesh->GetVertexBuffer()->GetOffset();

        DC->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetComPtr().GetAddressOf(), &stride, &offset);
        DC->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

        _material->GetShader()->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
        break;

    default:
        assert(false);
        break;
    }
}
