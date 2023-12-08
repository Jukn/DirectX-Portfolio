#pragma once

template<typename T>
class Geometry
{
public:
	Geometry() {} 
	~Geometry() {}

	uint32 GetVertexCount() { return static_cast<uint32>(_vertices.size()); }
	void* GetVertexData() { return _vertices.data(); }
	const vector<T>& GetVertices() { return _vertices; }

	uint32 GetIndexCount() { return static_cast<uint32>(_indices.size());  }
	void* GetIndexData() { return _indices.data(); }
	const vector<uint32>& GetIndices() { return _indices; }

	void AddVertex(const T& vertex) { _vertices.push_back(vertex); }
	void AddVertices(const vector<T>& vertices) { _vertices.insert(_vertices.end(), vertices.begin(), vertices.end()); }
	void SetVertices(const vector<T>& vertices) { _vertices = vertices; }

	void AddIndex(uint32 index) { _indices.push_back(index); }
	void AddIndices(const vector<uint32>& indices) { _indices.insert(_indices.end(), indices.begin(), indices.end()); }
	void SetIndices(const vector<uint32>& indices) { _indices = indices; }

    void AddSubIndex(const vector<uint32>& indices) { _subIndices.push_back(indices); }
	void SetSubIndices(const vector<vector<uint32>>& indices) { _subIndices = indices; }
	const vector<vector<uint32>>& GetSubIndices() { return _subIndices; }

private:
	vector<T> _vertices;
	//vector<vector<T>> _subVertices;
	vector<uint32> _indices;
	vector<vector<uint32>> _subIndices;
};
