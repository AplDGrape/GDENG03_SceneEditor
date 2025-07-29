#pragma once
#include <string>
#include <sstream>
#include <vector>
#include "Vector3D.h"
#include "pugixml-1.13/src/pugixml.hpp"
#include "pugixml-1.13/src/pugiconfig.hpp"

class SceneReader
{
public:
	typedef std::string String;

	SceneReader(String directory);

	void readFromFile();
	Vector3D GetTransformFromXML(pugi::xml_node transform);

	std::vector<std::string> split(const std::string& s, char delim);

	~SceneReader();
private:
	String directory;
};