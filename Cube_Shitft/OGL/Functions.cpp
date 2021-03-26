#include "Functions.h"

Vertex_Iterator OGL::Find(Vertex_Iterator Begin, Vertex_Iterator End, OGL::Vertex& Key)
{
	for (; Begin < End; Begin++)
	{
		if ((Begin->Position == Key.Position) && (Begin->Normal == Key.Normal)) break;
	}

	return Begin;
}

std::vector<float> OGL::ToArray(std::vector<OGL::Vertex> Array)
{
	std::vector<float> Temp;

	for (int i = 0; i < Array.size(); i++)
	{
		Temp.push_back(Array[i].Position.x);
		Temp.push_back(Array[i].Position.y);
		Temp.push_back(Array[i].Position.z);

		Temp.push_back(Array[i].Normal.x);
		Temp.push_back(Array[i].Normal.y);
		Temp.push_back(Array[i].Normal.z);
	}

	return Temp;
}

std::vector<OGL::Vertex> OGL::ToVector(std::vector<float> Array)
{
	std::vector<OGL::Vertex> Temp;

	for (int i = 0; i < Array.size(); i += 6)
	{
		Temp.push_back({ glm::vec3(Array[i + 0], Array[i + 1], Array[i + 2]), glm::vec3(Array[i + 3], Array[i + 4], Array[i + 5]) });
	}

	return Temp;
}

OGL::Vertex_Index_Array OGL::GetIndexedArray(std::vector<OGL::Vertex>& Array)
{
	std::vector<OGL::Vertex> Short_List;
	std::vector<unsigned int> Index_Array;

	for (int i = 0; i < Array.size(); i++)
	{
		auto Iterator = OGL::Find(Short_List.begin(), Short_List.end(), Array[i]);

		if (Iterator == Short_List.end())
		{
			Short_List.push_back(Array[i]);

			Index_Array.push_back(Short_List.size() - 1);
		}
		else
		{
			int Index = int(Iterator - Short_List.begin());

			Index_Array.push_back(Index);
		}
	}

	std::vector<float> Final_Short_List = ToArray(Short_List);

	return { Final_Short_List, Index_Array };
}