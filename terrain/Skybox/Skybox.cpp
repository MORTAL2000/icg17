#include "Skybox.h"

Skybox::Skybox()
{

}

GLuint Skybox::init() {
    mMaterial.init("Skybox_vshader.glsl", "Skybox_fshader.glsl");
    vector<const GLchar*> faces;
    faces.push_back("right_moon.png");
    faces.push_back("left_moon.png");
    faces.push_back("bottom_moon.png");
    faces.push_back("top_moon.png");
    faces.push_back("back_moon.png");
    faces.push_back("front_moon.png");
    GLuint texId = mMaterial.addCubeTexture(GL_TEXTURE_CUBE_MAP,GL_TEXTURE0,faces,"skybox");
    mMaterial.addTexture(GL_TEXTURE10,"sky.png","sky",GL_LINEAR_MIPMAP_LINEAR,GL_REPEAT,GL_CLAMP_TO_EDGE, true);

    GLfloat skyboxVertices[] = {
        // Positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(mMaterial.attrLocation("position"), 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);

    return texId;
}

void Skybox::draw(const glm::mat4 &view, const glm::mat4 &projection) {
    glm::mat4 newView = view;
    newView[3] = glm::vec4(0,0,0,1);
    glDepthMask(GL_FALSE);
    glBindVertexArray(skyboxVAO);
    mMaterial.bind();
    glUniformMatrix4fv(mMaterial.uniformLocation("VP"), ONE, DONT_TRANSPOSE,glm::value_ptr(projection * newView));
    glUniformMatrix4fv(mMaterial.uniformLocation("V"), ONE, DONT_TRANSPOSE,glm::value_ptr(view));
    glUniformMatrix4fv(mMaterial.uniformLocation("iV"), ONE, DONT_TRANSPOSE,glm::value_ptr(inverse(view)));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    mMaterial.unbind();
    glBindVertexArray(0);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthMask(GL_TRUE);
}

