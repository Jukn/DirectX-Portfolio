#pragma once

struct VertexTextureData
{
	Vector3 position = {0,0,0};
	Vector2 UV = {0,0};

	static std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
};

struct VertexColorData
{
	Vector3 position = {0,0,0};
	Color color = {0,0,0,0};

	static std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
};

