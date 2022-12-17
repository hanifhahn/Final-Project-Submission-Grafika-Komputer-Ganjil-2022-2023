#pragma once
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>

class Demo :
	public RenderEngine
{
public:
	Demo();
	~Demo();
private:
	GLuint shaderProgram, VBO, VAO, EBO, texture, VBO2, VAO2, EBO2, texture2, VBO3, VAO3, EBO3, texture3, VBO4, VAO4, EBO4, texture4, VBO5, VAO5, EBO5, texture5, VBO6, VAO6, EBO6, texture6, VBO7, VAO7, EBO7, texture7, VBO8, VAO8, EBO8, texture8, VBO9, VAO9, EBO9, texture9, VBO10, VAO10, EBO10, texture10, VBO11, VAO11, EBO11, texture11, VBO12, VAO12, EBO12, texture12, VBO13, VAO13, EBO13, texture13;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	GLuint stexture, stexture2;
	GLuint skyboxShader;
	GLuint skyboxVAO, skyboxVBO, skyboxEBO, skyboxTexture;

	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);

	void BuildColoredCubeSand();
	void BuildColoredCubeWater();
	void BuildColoredCubeTrunk();
	void BuildColoredCubeLeaf();
	void BuildColoredCubeCoconut();
	void BuildColoredCubeBrick();
	void BuildColoredCubeWodden();
	void BuildColoredCubeFlag();
	void BuildColoredCubeWhiteWall();
	void BuildColoredCubeDoor();
	void BuildColoredCubeTopTorch();

	void BuildColoredCubeSun();
	void BuildColoredCubeSkybox();

	void DrawColoredCubeSand(double xPos, double yPos, double zPos);
	void DrawColoredCubeWater(double xPos, double yPos, double zPos);
	void DrawColoredCubeTrunk(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale);
	void DrawColoredCubeLeaf(double xPos, double yPos, double zPos);
	void DrawColoredCubeCoconut(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale);
	void DrawColoredCubeBrick(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale);
	void DrawColoredCubeWodden(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale);
	void DrawColoredCubeFlag(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale);
	void DrawColoredCubeWhiteWall(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale);
	void DrawColoredCubeDoor(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale);
	void DrawColoredCubeTopTorch(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale);

	void DrawColoredCubeSun(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale);
	void DrawColoredCubeSkybox(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale);

	void BuildColoredPlane();
	void DrawColoredPlane();

	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void YCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();
};

