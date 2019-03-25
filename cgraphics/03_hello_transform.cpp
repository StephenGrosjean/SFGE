#include <engine/engine.h>

#include "graphics/graphics3d.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SFML/Graphics/Texture.hpp"

#define ROTATE_OVER_TIME

class HelloTransformDrawingProgram : public sfge::DrawingProgram
{
public:
	using sfge::DrawingProgram::DrawingProgram;
    void OnEngineInit() override;
    void OnDraw() override;
    void Destroy() override;
private:

    float vertices[12] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };
    float texCoords[8] = {
            1.0f, 1.0f,	  // top right
            1.0f, 0.0f,   // bottom right
            0.0f, 0.0f,   // bottom left
            0.0f, 1.0f,   // top left
    };
    unsigned int indices[6] = {
            // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };

	sfge::Shader shaderProgram;
    unsigned VBO[2];
    unsigned EBO;
    unsigned VAO;
	sf::Texture sfTextureWall;
    unsigned textureWall;
};

void HelloTransformDrawingProgram::OnEngineInit()
{
    programName = "HelloTransform";

    shaders.push_back(&shaderProgram);

    glGenBuffers(2, &VBO[0]);
    glGenBuffers(1, &EBO);

    shaderProgram.Init(
            "data/shaders/03_hello_transform/transform.vert",
            "data/shaders/03_hello_transform/transform.frag"
    );
	sfTextureWall.loadFromFile("data/sprites/wall.dds");
	textureWall = sfTextureWall.getNativeHandle();
    glGenVertexArrays(1, &VAO); //like: new VAO()
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);//Now use our VAO
    //bind vertices data
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //bind texture coords data
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    //bind vertices index
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //unbind Vertex Array
    glBindVertexArray(0);
}

void HelloTransformDrawingProgram::OnDraw()
{
    glm::mat4 trans = glm::mat4(1.0f);
#ifndef ROTATE_OVER_TIME
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
#else
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    trans = glm::rotate(trans, m_Engine.GetTimeSinceInit(), glm::vec3(0.0f, 0.0f, 1.0f));
#endif

    shaderProgram.Bind();

    unsigned int transformLoc = glGetUniformLocation(shaderProgram.GetProgram(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    glBindTexture(GL_TEXTURE_2D, textureWall);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

void HelloTransformDrawingProgram::Destroy()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(2, &VBO[0]);
	glDeleteBuffers(2, &EBO);
}

int main(int argc, char** argv)
{
	sfge::Engine engine;

	HelloTransformDrawingProgram helloTransform(engine);

	auto* graphics3dManager = engine.GetGraphics3dManager();
	graphics3dManager->AddDrawingProgam(&helloTransform);
	{
		auto config = std::make_unique<sfge::Configuration>();
		config->screenResolution.x = 1024;
		config->screenResolution.y = 1024;
		//config.bgColor = sf::Color::Black;
		config->windowName = "Hello Transform";
		engine.Init(std::move(config));
	}

    engine.Start();

    return EXIT_SUCCESS;
}
