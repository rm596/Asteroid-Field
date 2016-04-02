#include <iostream>
#include <fstream>
#include <sstream>

#include "Obj.h"
#include <vector>

Obj_material current_material;
int i = 0;

obj::obj()
{
}

const std::vector<Obj_vertex> obj::getVertices()
{
	return this->Vertices;
}

const std::vector<Obj_texcoord> obj::getTextcoords()
{
	return this->Texcoords;
}

const std::vector<Obj_normal> obj::getNormals()
{
	return this->Normals;
}

const std::vector<Obj_color> obj::getAmbient()
{
	return this->ambientData;
}

const std::vector<Obj_color> obj::getDiffuse()
{
	return this->diffuseData;
}

const std::vector<Obj_color> obj::getSpecular()
{
	return this->specularData;
}

const std::vector<float> obj::getAlfa()
{
	return this->alfaData;
}

const std::vector<Obj_material> obj::getMaterials()
{
	//return this->material;
}

const void obj::getMaterial(std::string & name_material)
{
	std::string temp;

	std::istringstream iss(name_material);
	iss >> temp >> temp;

	//std::cout << temp << std::endl;

	/*
	for (int i = 0; i < this->material.size(); i++)
	{
	if (this->material[i].name.compare(temp) == 0)
	{
	current_material = this->material[i];
	//std::cout << " encontrei " << this->material[i].name << std::endl;
	break;
	}
	}
	*/

	std::unordered_map<std::string, Obj_material>::const_iterator got = material.find(temp);
	current_material = got->second;
}

void obj::parseVertex(std::stringstream & sin)
{
	Obj_vertex v;
	sin >> v.x >> v.y >> v.z;
	vertexData.push_back(v);
}

void obj::parseTexcoord(std::stringstream& sin)
{
	Obj_texcoord t;
	sin >> t.u >> t.v;
	texcoordData.push_back(t);
}

void obj::parseNormal(std::stringstream & sin)
{
	Obj_normal n;
	sin >> n.nx >> n.ny >> n.nz;
	normalData.push_back(n);
}

void obj::parseFace(std::stringstream & sin)
{
	std::string token;
	for (int i = 0; i < 3; i++) {
		std::getline(sin, token, '/');
		if (token.size() > 0) vertexIdx.push_back(std::stoi(token));
		std::getline(sin, token, '/');
		if (token.size() > 0) texcoordIdx.push_back(std::stoi(token));
		std::getline(sin, token, ' ');
		if (token.size() > 0) {
			normalIdx.push_back(std::stoi(token));

			//AGR OS MATERIAIS
			//materialIdx.push_back(current_material.index);
			materialIdx_name.push_back(current_material.name);
		}
	}
}

//para ler obj
void obj::parseLine(std::stringstream & sin)
{
	std::string s;
	sin >> s;
	if (s.compare("v") == 0) parseVertex(sin);
	else if (s.compare("vt") == 0) parseTexcoord(sin);
	else if (s.compare("vn") == 0) parseNormal(sin);
	else if (s.compare("f") == 0) parseFace(sin);

	//faco set material actual
	else if (s.compare("usemtl") == 0) getMaterial(sin.str());

}

//ler file completo mtl
void obj::parseLineMtl(std::stringstream & sin)
{
	std::string s;
	sin >> s;

	if (s.compare("newmtl") == 0)
	{
		sin >> current_material.name;
		current_material.index = i;
		i++;
	}
	else if (s.compare("Ka") == 0)
	{
		sin >> current_material.kar >> current_material.kag >> current_material.kab;
	}
	else if (s.compare("Kd") == 0)
	{
		sin >> current_material.kdr >> current_material.kdg >> current_material.kdb;
	}
	else if (s.compare("Ks") == 0)
	{
		sin >> current_material.ksr >> current_material.ksg >> current_material.ksb;

		//inserir novo material
		//material.push_back(current_material);

		//std::pair<std::string, Obj_material> mymaterial(current_material.name, current_material);
		//material.insert(mymaterial);
	}
	else if (s.compare("d") == 0)
	{
		sin >> current_material.d;
		std::pair<std::string, Obj_material> mymaterial(current_material.name, current_material);
		material.insert(mymaterial);
	}
}

void obj::loadMeshData(std::string & filename)
{
	std::ifstream ifile(filename);
	while (ifile.good()) {
		std::string line;
		std::getline(ifile, line);
		parseLine(std::stringstream(line));
	}

	//se tenho coordenadas textura
	TexcoordsLoaded = (texcoordIdx.size() > 0);

	//se tenho normais
	NormalsLoaded = (normalIdx.size() > 0);
}

//para ler mtl
void obj::loadMtl(std::string & filename)
{
	std::ifstream ifile(filename);
	while (ifile.good()) {
		std::string line;
		std::getline(ifile, line);
		parseLineMtl(std::stringstream(line));
	}
}

//converter indiced em coordenadas
void obj::processMeshData()
{
	//temp color
	Obj_color color_mtl;
	float alfa;

	for (unsigned int i = 0; i < vertexIdx.size(); i++) {
		unsigned int vi = vertexIdx[i];
		Obj_vertex v = vertexData[vi - 1];
		Vertices.push_back(v);
		if (TexcoordsLoaded) {
			unsigned int ti = texcoordIdx[i];
			Obj_texcoord t = texcoordData[ti - 1];
			Texcoords.push_back(t);
		}
		if (NormalsLoaded) {
			unsigned int ni = normalIdx[i];
			Obj_normal n = normalData[ni - 1];
			Normals.push_back(n);
		}
		if (MaterialLoaded)
		{
			//procuramos hash table pelo nome
			std::unordered_map<std::string, Obj_material>::const_iterator got = material.find(materialIdx_name[i]);

			//obtemos material
			Obj_material temp; 
			temp = got->second; 

			//CRIAMOS MATERIAL PELO INDICE
			//ambiente

			color_mtl.r = temp.kar;
			color_mtl.g = temp.kag;
			color_mtl.b = temp.kab;

			ambientData.push_back(color_mtl);

			//difusa
			//Obj_color diffuse;

			color_mtl.r = temp.kdr;
			color_mtl.g = temp.kdg;
			color_mtl.b = temp.kdb;

			diffuseData.push_back(color_mtl);

			//especular
			//Obj_color specular;

			color_mtl.r = temp.ksr;
			color_mtl.g = temp.ksg;
			color_mtl.b = temp.ksb;

			specularData.push_back(color_mtl);

			//transparencia
			alfa = temp.d;

			alfaData.push_back(alfa);
		}
	}
}

//limpar memoria
void obj::freeMeshData()
{
	vertexData.clear();
	texcoordData.clear();
	normalData.clear();

	Vertices.clear();
	Texcoords.clear();
	Normals.clear();

	materialIdx_name.clear();
	material.clear();

	vertexIdx.clear();
	normalIdx.clear();
	texcoordIdx.clear();

	ambient.clear();
	ambientData.clear();

	diffuse.clear();
	diffuseData.clear();

	specular.clear();
	specularData.clear();

	alfa.clear();
	alfaData.clear();
}

const void obj::createMesh(std::string& obj, std::string& mtl)
{
	//ler mtl
	loadMtl(mtl);

	//faço set cor default
	//getMaterial(std::string("None"));
	MaterialLoaded = true;

	//ler obj
	loadMeshData(obj);

	processMeshData();
	//freeMeshData();
}
