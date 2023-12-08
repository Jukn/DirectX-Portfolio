#pragma once
#include "IExecute.h"
#include "Geometry.h"
#include "Frustum.h"

class HeightMapDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	shared_ptr<Shader> _shader;
	shared_ptr<Shader> _gridShader;

	// land Object
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	vector<shared_ptr<IndexBuffer>> _subIndexBuffers;
	Matrix _world = Matrix::Identity;
	shared_ptr<Texture> _heightMap;
	shared_ptr<Texture> _texture;

	// collider objects
	array<shared_ptr<GameObject>, 16> _colliders;

	// Camera
	shared_ptr<GameObject> _camera;

	// Frustum
	shared_ptr<Frustum> _frustum;
};

