#include "Model.h"

OGL::Model::Model()
{
    //ctor
}

OGL::Model::~Model()
{
    //dtor
}

void OGL::Model::GenerateModel(std::vector<float>& va, std::vector<unsigned int>& ia)
{
    Call(glGenVertexArrays(1, &Buffer.VertexArrayId));
    Call(glBindVertexArray(Buffer.VertexArrayId));

    Call(glGenBuffers(1, &Buffer.VertexBuffer));
    Call(glBindBuffer(GL_ARRAY_BUFFER, Buffer.VertexBuffer));
    Call(glBufferData(GL_ARRAY_BUFFER, va.size() * sizeof(float), &va[0], GL_STATIC_DRAW));

    Call(glGenBuffers(1, &Buffer.IndexBuffer));
    Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffer.IndexBuffer));
    Call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, ia.size() * sizeof(unsigned int), &ia[0], GL_STATIC_DRAW));

    Rotation = glm::mat4(1.0f);
    ScaleM = glm::mat4(1.0f);
    Transform = glm::mat4(1.0f);

    VertexArray = va;
    IndexArray = ia;

    UnBind();
}

void OGL::Model::Rotate(float Angle, glm::vec3 axis)
{
    Rotation = glm::rotate(glm::mat4(1.0f), Angle, axis);
}

void OGL::Model::Scale(glm::vec3 Scale)
{
    this->ScaleM = glm::scale(glm::mat4(1.0f), Scale);
}

void OGL::Model::SetPosition(glm::vec3 Pos)
{
    this->Transform = glm::translate(glm::mat4(1.0f), Pos);
    this->Pos = Pos;
}

void OGL::Model::Bind()
{
    Call(glBindVertexArray(Buffer.VertexArrayId));

    Call(glBindBuffer(GL_ARRAY_BUFFER, Buffer.VertexBuffer));

    Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffer.IndexBuffer));
}

void OGL::Model::UnBind()
{
    Call(glBindVertexArray(0));

    Call(glBindBuffer(GL_ARRAY_BUFFER, 0));

    Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void OGL::Model::Draw()
{
    Bind();

    Call(glEnableVertexAttribArray(0));
    Call(glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        6 * sizeof(float),  // stride
        (void*)0            // array buffer offset
        ));

    Call(glEnableVertexAttribArray(1));
    Call(glVertexAttribPointer(
        1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        6 * sizeof(float),  // stride
        (void*)(3 * sizeof(float))   // array buffer offset
        ));

    msh->Bind();

    msh->SetUniformMat4f("Model", Transform * ScaleM * Rotation);

    // Draw the triangles !
    Call(glDrawElements(
        GL_TRIANGLES,    // mode
        IndexArray.size(),  // count
        GL_UNSIGNED_INT, // type
        (void*)0         // element array buffer offset
    ));

    UnBind();
}
