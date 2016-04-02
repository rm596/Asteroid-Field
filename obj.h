#ifndef _OBJ
#define _OBJ

#include <GL/glew.h>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

/*
OBJ
*/
typedef struct {
	GLfloat x, y, z;
} Obj_vertex;

typedef struct {
	GLfloat u, v;
} Obj_texcoord;

typedef struct {
	GLfloat nx, ny, nz;
} Obj_normal;

/*
MTL
*/
typedef struct {
	std::string name;
	int index;
	GLfloat kar, kag, kab, kdr, kdg, kdb, ksr, ksg, ksb, d;
} Obj_material;

//MATERIAL
typedef struct
{
	GLfloat r, g, b;  
} Obj_color;

class obj
{
private:
	std::vector <Obj_vertex> Vertices, vertexData;
	std::vector <Obj_texcoord> Texcoords, texcoordData;
	std::vector <Obj_normal> Normals, normalData;
	
	//leitura do file mtl
	//std::vector <Obj_material> material;
	std::unordered_map<std::string, Obj_material> material;
	
	//materiais  
	std::vector <Obj_color> ambient, ambientData;
	std::vector <Obj_color> diffuse, diffuseData;
	std::vector <Obj_color> specular, specularData;
	std::vector <float> alfa, alfaData;

	//indices
	std::vector<unsigned int> vertexIdx, texcoordIdx, normalIdx; // , materialIdx;
	std::vector<std::string> materialIdx_name;

public:
	bool TexcoordsLoaded, NormalsLoaded, MaterialLoaded;

	//construtor
	obj();

	/*
	GETS
	*/
	const std::vector <Obj_vertex> getVertices();
	const std::vector <Obj_texcoord> getTextcoords();
	const std::vector <Obj_normal> getNormals();

	//MATERIAIS OBJ
	const std::vector <Obj_material> getMaterials();
	const void getMaterial(std::string & name);
	
	const std::vector <Obj_color> getAmbient();
	const std::vector <Obj_color> getDiffuse();
	const std::vector <Obj_color> getSpecular();
	const std::vector <float> getAlfa();

	//ler vertices
	void parseVertex(std::stringstream& sin);
	
	//ler uv
	void parseTexcoord(std::stringstream& sin);
	
	//ler normal
	void parseNormal(std::stringstream& sin);
	
	//construir face
	void parseFace(std::stringstream& sin);

	//ler linha em obj
	void parseLine(std::stringstream& sin);

	//ler linha mtl
	void parseLineMtl(std::stringstream& sin);
	
	//ler obj
	const void createMesh(std::string& obj, std::string& mtl);

	void loadMeshData(std::string& filename);

	void loadMtl(std::string& filename);
	
	void processMeshData();
	
	//clear memory
	void freeMeshData();
	
};

#endif
