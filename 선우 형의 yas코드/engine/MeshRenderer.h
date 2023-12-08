#pragma once
#include "Component.h"

class Mesh;
class Shader;
class Material;

enum class MeshType : uint8
{
    Simple,
	Complex
};

class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer();
	virtual ~MeshRenderer();

	virtual void Update() override;

	void SetMeshType(MeshType type) { _meshType = type; }

	shared_ptr<Mesh> GetMesh() { return _mesh; }
	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetMaterial(shared_ptr<Material> material) { _material = material; }

	shared_ptr<SimpleMesh> GetSimpleMesh() { return _simpleMesh; }
	void SetSimpleMesh(shared_ptr<SimpleMesh> simpleMesh) { _simpleMesh = simpleMesh; }
	void SetShader(shared_ptr<Shader> shader) { _shader = shader; }

	// Legacy
	//void SetTexture(shared_ptr<Texture> texture) { }
	//void SetShader(shared_ptr<Shader> shader) { }

private:
	MeshType _meshType = MeshType::Simple;

	shared_ptr<Mesh> _mesh;
	shared_ptr<Material> _material;
	//shared_ptr<Texture> _texture;
	//shared_ptr<Shader> _shader;
	shared_ptr<SimpleMesh> _simpleMesh;
	shared_ptr<Shader> _shader;

};

