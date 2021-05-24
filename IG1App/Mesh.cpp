#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

//-------------------------------------------------------------------------

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const
{
    if (mShader == nullptr) {
        if (vVertices.size() > 0) {  // transfer data
            // transfer the coordinates of the vertices
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 

            if (vColors.size() > 0) { // transfer colors
                glEnableClientState(GL_COLOR_ARRAY);
                glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
            }

            if (vTexCoords.size() > 0) {
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
            }

            draw();

            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);
        }
    }
    else {
        mShader->bind();
        glBindVertexArray(VAO);
        draw();
        glBindVertexArray(0);
        mShader->unbind();
    }
}
void Mesh::setShader(Shader* shader)
{
    mShader = shader;


    std::vector<double> vertices;
    for (int i = 0; i < mNumVertices; i++) {
        for (int j = 0; j < 3; j++)
            vertices.push_back(vVertices[i][j]);

        for (int j = 0; j < 4; j++)
            vertices.push_back(vColors[i][j]);
    }
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(double), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 7 * sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 4, GL_DOUBLE, GL_FALSE, 7 * sizeof(double), (void*)(3 * sizeof(double)));
    glEnableVertexAttribArray(1);

}
void Mesh::setColor(glm::dvec4 aColor)
{
    for (int i = 0; i < mNumVertices; i++) {
        vColors[i] = aColor;
    }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaPoligono(GLuint numL, GLdouble rd)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINE_LOOP;

  mesh->mNumVertices = numL;
  mesh->vVertices.reserve(mesh->mNumVertices);
  mesh->vColors.reserve(mesh->mNumVertices);
  
  float Cx = 0;
  float Cy = 0;
  float x, y;
  float grd = 90;
  x = Cx + rd * cos(radians(grd));
  y = Cy + rd * sin(radians(grd));

  for (int i = 0; i < numL; i++) {
      mesh->vVertices.emplace_back(x, y, 0.0);
      grd = grd + (360 / numL);
      x = Cx + rd * cos(radians(grd));
      y = Cy + rd * sin(radians(grd));
  }

  for (int i = 0; i < numL; i++) {
      mesh->vColors.emplace_back(1.0, 1.0, 1.0, 1.0);
  }

  return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaSierpinski(GLdouble rd, GLuint numP)
{
    Mesh* triangulo = generaPoligono(3, rd);
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_POINTS;

    mesh->mNumVertices = numP;
    mesh->vVertices.reserve(mesh->mNumVertices);
    mesh->vColors.reserve(mesh->mNumVertices);

    
    mesh->vVertices.emplace_back(triangulo->vertices()[rand() % 3]);
    glm::dvec3 auxVertA, auxVertB;
    for (int k = 1; k < numP; k++) {
        auxVertA = mesh->vertices()[k - 1];
        auxVertB = triangulo->vertices()[rand() % 3] + auxVertA;
        mesh->vVertices.emplace_back(auxVertB.x/2, auxVertB.y / 2, auxVertB.z / 2);
    }

    
    delete triangulo; 
    triangulo = nullptr;
    return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaTrianguloRGB(GLdouble rd)
{
    Mesh* mesh = generaPoligono(3, rd);
    
    mesh->mPrimitive = GL_TRIANGLES;

    mesh->vColors[0] = glm::dvec4(1.0, 0.0, 0.0, 1.0);
    mesh->vColors[1] = glm::dvec4(0.0, 1.0, 0.0, 1.0);
    mesh->vColors[2] = glm::dvec4(0.0, 0.0, 1.0, 1.0);

    return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);
    mesh->vColors.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(0, h, 0.0);
    mesh->vVertices.emplace_back(0, 0, 0.0);
    mesh->vVertices.emplace_back(w, h, 0.0);
    mesh->vVertices.emplace_back(w, 0, 0.0);


    return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h)
{
    Mesh* mesh = generaRectangulo(w, h);

    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

    return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaEstrella3D(GLdouble re, GLuint np, GLdouble h)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_FAN;

    mesh->mNumVertices = 2*np+2;
    mesh->vVertices.reserve(mesh->mNumVertices);
    mesh->vColors.reserve(mesh->mNumVertices);

    float Cx = 0;
    float Cy = 0;
    float outx, outy;
    float inx, iny;
    GLfloat grd = 0.0;

    outx = Cx + re * cos(radians(grd));
    outy = Cy + re * sin(radians(grd));

    grd = grd + (360.0 / (np * 2));
    inx = Cx + (re/2) * cos(radians(grd));
    iny = Cy + (re/2) * sin(radians(grd));

    mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
    for (int i = 0; i < np; i++) {
        mesh->vVertices.emplace_back(outx, outy, h);
        mesh->vVertices.emplace_back(inx, iny, h);

        grd = grd + (360.0 / (np*2));
        outx = Cx + re * cos(radians(grd));
        outy = Cy + re * sin(radians(grd));


        grd = grd + (360.0 / (np * 2));
        inx = Cx + (re / 2) * cos(radians(grd));
        iny = Cy + (re / 2) * sin(radians(grd));
    }
    mesh->vVertices.emplace_back(outx, outy, h);


    return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaContCubo(GLdouble ld)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 10;
    mesh->vVertices.reserve(mesh->mNumVertices);
    mesh->vColors.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(ld / 2, ld / 2, ld / 2);
    mesh->vVertices.emplace_back(ld / 2, -ld / 2, ld / 2);

    mesh->vVertices.emplace_back(-ld / 2, ld / 2, ld / 2);
    mesh->vVertices.emplace_back(-ld / 2, -ld / 2, ld / 2);

    mesh->vVertices.emplace_back(-ld / 2, ld / 2, -ld / 2);
    mesh->vVertices.emplace_back(-ld / 2, -ld / 2, -ld / 2);

    mesh->vVertices.emplace_back(ld / 2, ld / 2, -ld / 2);
    mesh->vVertices.emplace_back(ld / 2, -ld / 2, -ld / 2);

    mesh->vVertices.emplace_back(ld / 2, ld / 2, ld / 2);
    mesh->vVertices.emplace_back(ld / 2, -ld / 2, ld / 2);


    return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
    Mesh* mesh = generaRectangulo(w, h);
    mesh->vTexCoords.reserve(mesh->mNumVertices);

    mesh->vTexCoords.emplace_back(0, rw);
    mesh->vTexCoords.emplace_back(0, 0);
    mesh->vTexCoords.emplace_back(rh, rw);
    mesh->vTexCoords.emplace_back(rh, 0);
    return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h)
{
    Mesh* mesh = generaEstrella3D(re, np, h);
    mesh->vTexCoords.reserve(mesh->mNumVertices);

    mesh->vTexCoords.emplace_back(0.5, 0.5);

    for (int i = 1; i < mesh->mNumVertices; i++) {
        switch (i % 8) {
        case 0:
            mesh->vTexCoords.emplace_back(0, 0);
            break;
        case 1:
            mesh->vTexCoords.emplace_back(0, 0.5);
            break;
        case 2:
            mesh->vTexCoords.emplace_back(0, 1);
            break;
        case 3:
            mesh->vTexCoords.emplace_back(0.5, 1);
            break;
        case 4:
            mesh->vTexCoords.emplace_back(1, 1);
            break;
        case 5:
            mesh->vTexCoords.emplace_back(1, 0.5);
            break;
        case 6:
            mesh->vTexCoords.emplace_back(1, 0);
            break;
        case 7:
            mesh->vTexCoords.emplace_back(0.5, 0);
            break;
        }
    }
    return mesh;
}

Mesh* Mesh::generaContCuboTexCor(GLdouble nl)
{
    Mesh* mesh = generaContCubo(nl);
    mesh->vTexCoords.reserve(mesh->mNumVertices);

    mesh->vTexCoords.emplace_back(0, 1);
    mesh->vTexCoords.emplace_back(0, 0);

    mesh->vTexCoords.emplace_back(1, 1);
    mesh->vTexCoords.emplace_back(1, 0);

    mesh->vTexCoords.emplace_back(2, 1);
    mesh->vTexCoords.emplace_back(2, 0);

    mesh->vTexCoords.emplace_back(3, 1);
    mesh->vTexCoords.emplace_back(3, 0);

    mesh->vTexCoords.emplace_back(4, 1);
    mesh->vTexCoords.emplace_back(4, 0);

    return mesh;
}

//-------------------------------------------------------------------------
