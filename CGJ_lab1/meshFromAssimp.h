#pragma once
bool Import3DFromFile(const std::string& pFile);
std::vector<struct MyMesh> createMeshFromAssimp(const aiScene* sc, const char* model_dir);