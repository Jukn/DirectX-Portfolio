#include "pch.h"
#include "07. HeightMapDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "MeshRenderer.h"

void HeightMapDemo::Init()
{
    _shader = make_shared<Shader>(L"06. Terrain.fx");

    //_heightMap = RESOURCES->Load<Texture>(L"Height", L"..\\Resources\\Textures\\Terrain\\height.png");
    //const DirectX::ScratchImage& info = _heightMap->GetInfo();
    //uint8* pixelBuffer = info.GetPixels();
    _texture = RESOURCES->Load<Texture>(L"Grass", L"..\\Resources\\Textures\\Wood.jpg");

    //const int32 width = _heightMap->GetSize().x;
    //const int32 height = _heightMap->GetSize().y;
    const uint32 width = 16;
    const uint32 height = 16;
    const uint32 divideBy = 4;

    // land geometry
    _geometry = make_shared<Geometry<VertexTextureData>>();
    GeometryHelper::CreateGrid(_geometry, width, height, divideBy);
    _vertexBuffer = make_shared<VertexBuffer>();
    _vertexBuffer->Create(_geometry->GetVertices());
    _subIndexBuffers.resize(divideBy);
    for (uint32 i = 0; i < divideBy; i++)
    {
        _subIndexBuffers[i] = make_shared<IndexBuffer>();
        _subIndexBuffers[i]->Create(_geometry->GetSubIndices()[i]);
    }

    // CPU로 vertex y 처리
    /*
    {
        const float weight = 10.f; // 높이 가중치

        vector<VertexTextureData>& v = const_cast<vector<VertexTextureData>&>(_geometry->GetVertices());

        for (int32 z = 0; z < height; z++)
        {
            for (int32 x = 0; x < width; x++)
            {
                int32 idx = width * z + x;
                uint8 height = pixelBuffer[idx] / 255.f * weight;
                v[idx].position.y = height; // 높이 보정
            }
        }
    }
    */

    // export height map
    /*
    {
        DirectX::ScratchImage image;
        image.Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, width, height, 1, 1);

        uint8* pixels = image.GetPixels();
        for (int32 z = 0; z < height; z++)
        {
            for (int32 x = 0; x < width; x++)
            {
                int32 idx = width * z + x;
                pixels[idx * 4 + 0] = pixelBuffer[idx];
                pixels[idx * 4 + 1] = pixelBuffer[idx];
                pixels[idx * 4 + 2] = pixelBuffer[idx];
                pixels[idx * 4 + 3] = 255;
            }
        }

        DirectX::SaveToWICFile(image.GetImages(), image.GetImageCount(),
            DirectX::WIC_FLAGS_NONE, DirectX::GetWICCodec(DirectX::WIC_CODEC_PNG),
            L"..\\Resources\\Textures\\Terrain\\heightExported.png");
    }
    */

    // Camera
    _camera = make_shared<GameObject>();
    _camera->GetOrAddTransform();
    _camera->AddComponent(make_shared<Camera>());
    _camera->AddComponent(make_shared<CameraScript>());
    _camera->GetTransform()->SetPosition(Vec3(0, 5, 0.f));
    _camera->GetTransform()->SetRotation(Vec3(25.f, 0.f, 0.f));

    // colliders

    for (uint32 i = 0; i < _colliders.size(); i++)
    {
        _colliders[i] = make_shared<GameObject>();
        _colliders[i]->GetOrAddTransform();
        _colliders[i]->AddComponent(make_shared<MeshRenderer>());
        _colliders[i]->GetMeshRenderer()->SetMeshType(MeshType::Simple);
        _colliders[i]->GetMeshRenderer()->GetSimpleMesh()->CreateCube();
        _colliders[i]->GetMeshRenderer()->SetShader(make_shared<Shader>(L"02. Quad.fx"));
        _colliders[i]->GetTransform()->SetPosition(Vec3(i, 0.f, 0.f));
    }
}

void HeightMapDemo::Update()
{
    _camera->Update();
    _frustum->FinalUpdate();
}

void HeightMapDemo::Render()
{
    // land 
    {
        _shader->GetMatrix("World")->SetMatrix((float*)&_world);
        _shader->GetMatrix("View")->SetMatrix((float*)&Camera::S_MatView);
        _shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::S_MatProjection);
        _shader->GetSRV("Texture0")->SetResource(_texture->GetComPtr().Get());

        uint32 stride = _vertexBuffer->GetStride();
        uint32 offset = _vertexBuffer->GetOffset();

        DC->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
        DC->IASetIndexBuffer(_subIndexBuffers[1]->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
        DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        _shader->DrawIndexed(0, 0, _subIndexBuffers[1]->GetCount(), 0, 0);
    }
}
