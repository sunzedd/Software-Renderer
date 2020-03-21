#include "AssetLoader.h"

namespace Core {

std::shared_ptr<Mesh> AssetLoader::loadMesh(const std::string& filepath)
{
	int i = 0;

	std::vector<Vec3> positions;
	std::vector<Vec2> uvs;
	std::vector<Vec3> normals;
	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;

	auto mesh = std::make_shared<Mesh>();

	FILE* file;
	fopen_s(&file, filepath.c_str(), "r");
	if (!file)
		throw _Exception("Could not open file while reading: " + filepath);

	while (1)
	{
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		if (!strcmp(lineHeader, "v"))
		{
			Vec3 pos;
			fscanf_s(file, "%f %f %f\n", &pos.x, &pos.y, &pos.z);
			positions.push_back(pos);
		}
		else if (!strcmp(lineHeader, "vt"))
		{
			Vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			uvs.push_back(uv);
		}
		else if (!strcmp(lineHeader, "vn"))
		{
			Vec3 n;
			fscanf_s(file, "%f %f %f\n", &n.x, &n.y, &n.z);
			normals.push_back(n);
		}
		else if (!strcmp(lineHeader, "f"))
		{
			unsigned int posIndex[3], uvIndex[3], normalIndex[3];

			int cn = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&posIndex[0], &uvIndex[0], &normalIndex[0],
				&posIndex[1], &uvIndex[1], &normalIndex[1],
				&posIndex[2], &uvIndex[2], &normalIndex[2]);

			if (cn != 9)
			{
				fclose(file);
				throw _Exception("File could not been read: " + filepath);
			}

			for (int i = 0; i < 3; i++)
			{
				posIndex[i] -= 1;
				uvIndex[i] -= 1;
				normalIndex[i] -= 1;
			}

			Vertex v1, v2, v3;
			v1.pos = positions[posIndex[0]];
			v1.uv = uvs[uvIndex[0]];
			v1.n = normals[normalIndex[0]];

			v2.pos = positions[posIndex[1]];
			v2.uv = uvs[uvIndex[1]];
			v2.n = normals[normalIndex[1]];

			v3.pos = positions[posIndex[2]];
			v3.uv = uvs[uvIndex[2]];
			v3.n = normals[normalIndex[2]];

			v1.n.w = 0.0f;
			v2.n.w = 0.0f;
			v3.n.w = 0.0f;

			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + 2);

			i += 3;

			vertices.push_back(v1);
			vertices.push_back(v2);
			vertices.push_back(v3);
		}
	}

	mesh->setVertexBuffer(vertices);
	mesh->setIndexBuffer(indices);
	mesh->fillColor(Vec4(1.0f, 1.0f, 1.0f, 1.0f));

	return std::move(mesh);
}

std::shared_ptr<sf::Image> AssetLoader::loadImage(const std::string& filepath)
{
	auto img = std::make_shared<sf::Image>();
	img->loadFromFile(filepath);

	if (img->getSize().x == 0 || img->getSize().y == 0)
		throw _Exception("Could not load image");

	return std::move(img);
}

} // namespace Core