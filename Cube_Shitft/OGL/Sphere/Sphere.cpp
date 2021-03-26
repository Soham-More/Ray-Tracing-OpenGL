#include "Sphere.h"

OGL::Sphere::Sphere(glm::vec3 Pos, float radius)
{
    Generate_Fragments(1.0f, 100, 100);

    s_Model.SetPosition(Pos);

    s_Model.Scale(glm::vec3(radius, radius, radius));

    this->Pos = Pos;
    this->radius = radius;
}

OGL::Sphere::~Sphere()
{
    //dtor
}

void OGL::Sphere::Generate_Fragments(float radius, float sectorCount, float stackCount)
{
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<unsigned int> indices;

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex Normal

    float sectorStep = 2 * glm::pi<float>() / sectorCount;
    float stackStep = glm::pi<float>() / stackCount;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stackCount; ++i)
    {
        stackAngle = glm::pi<float>() / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cos(stackAngle);             // r * cos(u)
        z = radius * sin(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cos(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sin(sectorAngle);             // r * cos(u) * sin(v)
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);
        }
    }

    int k1, k2;
    for(int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != (stackCount-1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    std::vector<float> vn;

    for(int i = 0; i < vertices.size(); i += 3)
    {
        vn.push_back(vertices[i + 0]);
        vn.push_back(vertices[i + 1]);
        vn.push_back(vertices[i + 2]);

        vn.push_back(normals[i + 0]);
        vn.push_back(normals[i + 1]);
        vn.push_back(normals[i + 2]);
    }

    s_Model.GenerateModel(vertices, indices);
}

void OGL::Sphere::Draw()
{
    s_Model.Draw();
}

void OGL::Sphere::move(glm::vec3 m)
{
    this->Pos += m;
    s_Model.SetPosition(Pos);
}
