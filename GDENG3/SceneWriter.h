#pragma once
#include "Vector3D.h"

#include <string>
#include <fstream>

class SceneWriter
{
public:

	typedef std::fstream FileWriter;
	typedef std::string String;

	SceneWriter(String directory);

	void writeCoordinatesToFile(FileWriter file, Vector3D transform);
	void writeToFile();

	~SceneWriter();
private:
	String directory;
};