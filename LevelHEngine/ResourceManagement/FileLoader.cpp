#include "FileLoader.h"

#include <fstream>
#include "../Core/Logging.h"

/**
@brief A namespace that contains functions to load in files.
*/
namespace FileLoader
{

	std::string loadShaderFile(std::string fileName)
	{
		//file loading message
		Logging::logI("Loading " + fileName);

		//The loaded file as a string
		std::string loadedFile;

		//Open the file using a ifstream
		std::ifstream file(shaderFolder + fileName + shaderExtension);

		//If the file successfully opens
		if (file.is_open())
		{
			//File loading variables
			std::string currentLine;

			//While there are still lines to be read in from the file
			while (getline(file, currentLine))
			{
				//Add the current line to the loaded file
				loadedFile.append(currentLine);

				//Add a new line symbol to the end of the line
				loadedFile.append("\n");
			}
			//Close the file
			file.close();

			//file loaded message
			Logging::logI(fileName + " loaded");
		}
		//If the file could not be opened then output error message
		else
		{
			Logging::logI("Unable to open file");
		}

		//Return the loaded file as a std::string
		return loadedFile;
	}

	void loadOBJFile(std::string objFileName, std::vector<float> &vertices,
		std::vector<float> &vertexNormals, std::vector<float> &vertexTextures)
	{
		//file loading message
		Logging::logI("Loading " + objFileName);

		//Open the file using a ifstream
		std::ifstream file(meshFolder + objFileName + meshExtension);

		//local versions of the unsorted vertices and vertex normals
		std::vector<float> loadedVertices;
		std::vector<float> loadedVertexNormals;
		std::vector<float> loadedVertexTextures;

		//If the file successfully opens
		if (file.is_open())
		{
			//File loading variables
			std::string currentLine;

			//While there are still lines to be read in from the file
			while (getline(file, currentLine))
			{
				//load the current line in to a stringstream
				std::stringstream streamLine;
				streamLine.str(currentLine);

				//Create a string for the file type
				std::string lineType;
				//load in the first part of the line into the line type
				streamLine >> lineType;
			
				//if the data in the data in the current line is a vertex
				if (lineType == "v")
				{
					//load in the X Y Z coordinates for the vertex
					loadXYZFloats(streamLine, loadedVertices);
				}

				//if the data in the data in the current line is a vertex normal
				if (lineType == "vn")
				{			
					//load in the XYZ coordinates for the vertex normal
					loadXYZFloats(streamLine, loadedVertexNormals);
				}

				//if the data in the data in the current line is a vertex texture
				if (lineType == "vt")
				{
					//load in the UV coordinates for the vertex texture
					loadUVFloats(streamLine, loadedVertexTextures);
				}

				//if the data in the data in the current line is a face
				if (lineType == "f")
				{
					//sort the loaded data using the faces (indices)
					sortWithIndices(streamLine, loadedVertices, loadedVertexNormals, loadedVertexTextures, vertices, vertexNormals,vertexTextures);
				}
			}
			//Close the file
			file.close();

			//file loaded message
			Logging::logI(objFileName + " loaded");
		}
		//If the file could not be opened then output error message
		else
		{
			Logging::logI("Unable to open file");
		}
	}

	void loadXYZFloats(std::stringstream &streamLine, std::vector<float> &vectorArray)
	{
		//loop for the 3 parts of the coordinate
		for (int i = 0; i < 3; i++)
		{
			//load the next part of the stringstream into a float
			float coordinate;
			streamLine >> coordinate;

			//push the float to the array
			vectorArray.push_back(coordinate);
		}
	}

	void loadUVFloats(std::stringstream &streamLine, std::vector<float> &vectorArray)
	{
		//loop for the 2 parts of the coordinate
		for (int i = 0; i < 2; i++)
		{
			//load the next part of the stringstream into a float
			float coordinate;
			streamLine >> coordinate;

			//push the float to the array
			vectorArray.push_back(coordinate);
		}
	}

	void sortWithIndices(std::stringstream &streamLine, 
			std::vector<float> &loadedVertices,	std::vector<float> &loadedVertexNormals, 
			std::vector<float> &loadedVertexTextures, std::vector<float> &vertices, 
			std::vector<float> &vertexNormals, std::vector<float> &vertexTextures)
	{
		/*
		possible types of face data:
		v1 v2 v3 ...
		v1/vt1 v2/vt2 v3/vt3 ...
		v1/vt1/vn1 v2/vt2/vn2 v2/vt2/vn2 ...
		v1//vn1 v2//vn2 v2//vn2 ...	
		*/

		//loop through each indices of the face
		while (!streamLine.eof())
		{
			//load the next part of the stringstream into a float for the indices of the face
			float indices;
			streamLine >> indices;

			//push back the XYZ coordinates for the vertex at the indices position
			vertices.push_back(loadedVertices[(unsigned int)(indices - 1) * 3]);
			vertices.push_back(loadedVertices[(unsigned int)((indices - 1) * 3) + 1]);
			vertices.push_back(loadedVertices[(unsigned int)((indices - 1) * 3) + 2]);

			//check if the next char in the string stream is not a slash
			if (streamLine.peek() != '/')
			{
				//push back the UV coordinates (0,0) for the vertex texture
				vertexTextures.push_back(0.0f);
				vertexTextures.push_back(0.0f);

				//push back the XYZ coordinates (0,0,0) for the vertex normal
				vertexNormals.push_back(0.0f);
				vertexNormals.push_back(0.0f);
				vertexNormals.push_back(0.0f);

				//escape the loop
				break;
			}
			
			//remove the slash from the stream
			streamLine.get();

			//check if the next char in the string stream is a slash
			if (streamLine.peek() == '/')
			{
				//push back the UV coordinates (0,0) for the vertex texture
				vertexTextures.push_back(0.0f);
				vertexTextures.push_back(0.0f);
			}
			else
			{
				//load the next part of the stringstream into a float for the indices of the face
				streamLine >> indices;

				//push back the UV coordinates for the vertex texture at the indices position
				vertexTextures.push_back(loadedVertexTextures[(unsigned int)(indices - 1) * 2]);
				vertexTextures.push_back(loadedVertexTextures[(unsigned int)((indices - 1) * 2) + 1]);
			}

			//check if the next char in the string stream is not a slash
			if (streamLine.peek() != '/')
			{
				//push back the XYZ coordinates (0,0,0) for the vertex normal
				vertexNormals.push_back(0.0f);
				vertexNormals.push_back(0.0f);
				vertexNormals.push_back(0.0f);

				//escape the loop
				break;
			}

			//remove the slash from the stream
			streamLine.get();

			//load the next part of the stringstream into a float for the indices of the face
			streamLine >> indices;

			//push back the XYZ coordinates for the vertex normal at the indices position
			vertexNormals.push_back(loadedVertexNormals[(unsigned int)(indices - 1) * 3]);
			vertexNormals.push_back(loadedVertexNormals[(unsigned int)((indices - 1) * 3) + 1]);
			vertexNormals.push_back(loadedVertexNormals[(unsigned int)((indices - 1) * 3) + 2]);
		}
	}

} // End of file loader namespace