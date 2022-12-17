#include "Demo.h"

Demo::Demo() {

}

Demo::~Demo() {

}

void Demo::Init() {
	// build and compile our shader program
	// ------------------------------------
	shaderProgram = BuildShader("vertexShader.vert", "fragmentShader.frag", nullptr);
	//skyboxShader = BuildShader("skybox.vert", "skybox.frag", nullptr);

	BuildColoredCubeSand();
	BuildColoredCubeWater();
	BuildColoredCubeTrunk();
	BuildColoredCubeLeaf();
	BuildColoredCubeCoconut();
	BuildColoredCubeBrick();
	BuildColoredCubeWodden();
	BuildColoredCubeFlag();
	BuildColoredCubeWhiteWall();
	BuildColoredCubeDoor();
	BuildColoredCubeTopTorch();

	BuildColoredCubeSun();
	BuildColoredCubeSkybox();

	//BuildColoredPlane();

	InitCamera();
}

void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
	glDeleteBuffers(1, &skyboxEBO);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO2);

	glDeleteVertexArrays(1, &VAO3);
	glDeleteBuffers(1, &VBO3);
	glDeleteBuffers(1, &EBO3);

	glDeleteVertexArrays(1, &VAO4);
	glDeleteBuffers(1, &VBO4);
	glDeleteBuffers(1, &EBO4);

	glDeleteVertexArrays(1, &VAO5);
	glDeleteBuffers(1, &VBO5);
	glDeleteBuffers(1, &EBO5);

	glDeleteVertexArrays(1, &VAO6);
	glDeleteBuffers(1, &VBO6);
	glDeleteBuffers(1, &EBO6);

	glDeleteVertexArrays(1, &VAO7);
	glDeleteBuffers(1, &VBO7);
	glDeleteBuffers(1, &EBO7);

	glDeleteVertexArrays(1, &VAO8);
	glDeleteBuffers(1, &VBO8);
	glDeleteBuffers(1, &EBO8);

	glDeleteVertexArrays(1, &VAO9);
	glDeleteBuffers(1, &VBO9);
	glDeleteBuffers(1, &EBO9);

	glDeleteVertexArrays(1, &VAO10);
	glDeleteBuffers(1, &VBO10);
	glDeleteBuffers(1, &EBO10);

	glDeleteVertexArrays(1, &VAO11);
	glDeleteBuffers(1, &VBO11);
	glDeleteBuffers(1, &EBO11);

	glDeleteVertexArrays(1, &VAO12);
	glDeleteBuffers(1, &VBO12);
	glDeleteBuffers(1, &EBO12);

	glDeleteVertexArrays(1, &VAO13);
	glDeleteBuffers(1, &VBO13);
	glDeleteBuffers(1, &EBO13);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	
	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0120f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.0120f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	//Camera Up
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		YCamera(-1 * 0.1);
	}

	//Camera Down
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		YCamera(0.1);
	}

	//4 * Move More Faster
	if (glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS) {
		MoveCamera(4 * abs(CAMERA_SPEED));
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth/2;
	double midY = screenHeight/2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);
}

void Demo::Update(double deltaTime) {
	
}

void Demo::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0 / 255.0f, 0 / 255.0f, 0 / 255.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(this->shaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	GLint viewLoc = glGetUniformLocation(this->shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	//======================================================================================================================================================

	glm::vec3 cameraPos = glm::vec3(0, 10, 0);
	glm::vec3 cameraFront = glm::vec3(0, 10, 0);

	// set lighting attributes
	GLint viewPosLoc = glGetUniformLocation(this->shaderProgram, "viewPos");
	glUniform3f(viewPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);

	glUniform3f(glGetUniformLocation(this->shaderProgram, "dirLight.direction"), 0.0f, -1.0f, -1.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "dirLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "dirLight.diffuse"), 1.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "dirLight.specular"), 0.1f, 0.1f, 0.1f);

	// point light 1   === Warna putih
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[0].position"), 0.0f, 1.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[0].ambient"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[0].diffuse"), 0.0f, 1.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[0].specular"), 0.0f, 1.0f, 0.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[0].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[0].linear"), 0.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[0].quadratic"), 0.00002f);

	// point light 2   === Lampu Kapal
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[1].position"), -12.5, 0.0, 17.5);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[1].ambient"), 245 / 255.0f, 212 / 255.0f, 105 / 255.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[1].diffuse"), 0.0f, 0.0f, 1.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[1].specular"), 0.0f, 0.0f, 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[1].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[1].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[1].quadratic"), 0.22f);

	//// Lampu Bridge
	// point light 3   === Kanan 1
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[2].position"), 24.0, 0.0, 4.5);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[2].ambient"), 245 / 255.0f, 212 / 255.0f, 105 / 255.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[2].diffuse"), 0.0f, 0.0f, 1.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[2].specular"), 0.0f, 0.0f, 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[2].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[2].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[2].quadratic"), 0.22f);

	// point light 4   === Kiri 1 
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[3].position"), 6.0, 0.0, 4.5);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[3].ambient"), 245 / 255.0f, 212 / 255.0f, 105 / 255.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[3].diffuse"), 0.0f, 0.0f, 1.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[3].specular"), 0.0f, 0.0f, 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[3].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[3].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[3].quadratic"), 0.22f);

	// point light 5   === Kanan 2
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[4].position"), 24.0, 0.0, -3.5);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[4].ambient"), 245 / 255.0f, 212 / 255.0f, 105 / 255.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[4].diffuse"), 0.0f, 0.0f, 1.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[4].specular"), 0.0f, 0.0f, 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[4].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[4].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[4].quadratic"), 0.22f);

	// point light 6   === Kiri 2
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[5].position"), 6.0, 0.0, -3.5);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[5].ambient"), 245 / 255.0f, 212 / 255.0f, 105 / 255.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[5].diffuse"), 0.0f, 0.0f, 1.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "pointLights[5].specular"), 0.0f, 0.0f, 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[5].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[5].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "pointLights[5].quadratic"), 0.22f);

	// spotLight
	glUniform3fv(glGetUniformLocation(this->shaderProgram, "spotLight.position"), 1, &cameraPos[0]);
	glUniform3fv(glGetUniformLocation(this->shaderProgram, "spotLight.direction"), 1, &cameraFront[0]);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "spotLight.ambient"), 1.0f, 0.0f, 1.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "spotLight.diffuse"), 1.0f, 0.0f, 1.0f);
	glUniform3f(glGetUniformLocation(this->shaderProgram, "spotLight.specular"), 1.0f, 0.0f, 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "spotLight.linear"), 0.09f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "spotLight.quadratic"), 0.032f);
	glUniform1f(glGetUniformLocation(this->shaderProgram, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
	glUniform1f(glGetUniformLocation(this->shaderProgram, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

	//======================================================================================================================================================

	DrawColoredCubeSkybox(-0.1, 14.8, 30.0,  60.5, 29.5, 0.0);

	DrawColoredCubeSkybox(-0.1, 14.8, -30.0, 60.5, 29.5, 0.0);

	DrawColoredCubeSkybox(-30.0, 14.8, -0.1, 0.0, 29.5, 60.5);

	DrawColoredCubeSkybox(30.0, 14.8, -0.1, 0.0, 29.5, 60.5);

	//Atas
	DrawColoredCubeSkybox(-0.1, 29.5, -0.1, 60.5, 1.0, 60.5);

	//======================================================================================================================================================

	//Panjang = 59 blok
	//Jari-jari = 29.5 blok
	//DrawColoredCubeSand(-29.5, 0.0, -29.5);	//Pucuk 1
	//DrawColoredCubeSand(-29.5, 0.0, 29.5);	//Pucuk 2
	//DrawColoredCubeSand(29.5, 0.0, -29.5);    //Pucuk 3
	//DrawColoredCubeSand(29.5, 0.0, 29.5);		//Pucuk 4

	//=========================================================================== Layer 1
	//Pasir biasa
	for (double i = -29.5; i <= -14.5; i++) {
		for (double j = -29.5; j <= 29.5; j++) {
			DrawColoredCubeSand(j, 0.0, i);
		}
	}

	//DrawColoredCubeWater(-29.5, 0.0, -3.5);
	//DrawColoredCubeWater(-29.5, 0.0, -13.5);

	//Pasir melengkung
	double temp = 0;
	for (double i = -29.5; i <= -3.5; i++) {
		for (double j = -3.5; j >= -13.5; j--) {
			DrawColoredCubeSand(i, 0.0, j - temp);
		}
		
		if (std::fmod(i, -3.5) == 0)
		{
			temp += 1.5;
		}
	}

	//Air
	for (double i = -13.5; i <= 29.5; i++) {
		for (double j = -29.5; j <= 29.5; j++) {
			DrawColoredCubeWater((j + 0.0001), -0.001, (i + 0.0001));
		}
	}

	//=========================================================================== Layer 2
	//Pasir biasa
	for (double i = -29.5; i <= -15.5; i++) {
		for (double j = -29.5; j <= 29.5; j++) {
			DrawColoredCubeSand(j, 1.0, i);
		}
	}

	//Pasir melengkung
	double temp1 = 0;
	for (double i = -29.5; i <= -4.5; i++) {
		for (double j = -4.5; j >= -17.5; j--) {
			DrawColoredCubeSand(i, (1.0 - 0.0001), j - temp1);
		}

		if (std::fmod(i, -3.5) == 0)
		{
			temp1 += 2.5;
		}
	}

	//======================================================================================================================================================

	DrawColoredCubeWater(0.0, 0.0, 0.0);

	////////Pohon
	////Batang
	DrawColoredCubeTrunk(-10.0, 2.0, -18.0, 1.0, 1.0, 1.0);
	DrawColoredCubeTrunk(-9.0, 2.0, -17.0, 1.0, 1.0, 1.0);
	DrawColoredCubeTrunk(-9.0, 2.0, -18.0, 1.0, 1.0, 1.0);
	DrawColoredCubeTrunk(-9.0, 3.0, -18.0, 1.0, 1.0, 1.0);
	DrawColoredCubeTrunk(-8.0, 4.0, -18.0, 1.0, 1.0, 1.0);
	DrawColoredCubeTrunk(-8.0, 5.0, -18.0, 1.0, 1.0, 1.0);
	DrawColoredCubeTrunk(-7.0, 6.0, -18.0, 1.0, 1.0, 1.0);
	DrawColoredCubeTrunk(-7.0, 7.0, -18.0, 1.0, 1.0, 1.0);

	//Tengah
	DrawColoredCubeLeaf(-7.0, 8.0, -18.0);
	DrawColoredCubeLeaf(-7.0, 9.0, -18.0);

	DrawColoredCubeLeaf(-7.0, 8.0, -17.0);
	DrawColoredCubeLeaf(-6.0, 8.0, -18.0);
	DrawColoredCubeLeaf(-6.0, 8.0, -19.0);
	DrawColoredCubeLeaf(-6.0, 8.0, -17.0);
	DrawColoredCubeLeaf(-7.0, 8.0, -19.0);
	DrawColoredCubeLeaf(-8.0, 8.0, -19.0);
	DrawColoredCubeLeaf(-8.0, 8.0, -18.0);
	DrawColoredCubeLeaf(-8.0, 8.0, -17.0);

	//Depan
	DrawColoredCubeLeaf(-7.0, 8.0, -16.0);
	DrawColoredCubeLeaf(-7.0, 8.0, -15.0);

	DrawColoredCubeLeaf(-7.0, 7.0, -14.0);

	//Kanan
	DrawColoredCubeLeaf(-5.0, 8.0, -18.0);
	DrawColoredCubeLeaf(-4.0, 8.0, -18.0);

	DrawColoredCubeLeaf(-3.0, 7.0, -18.0);

	//Belakang
	DrawColoredCubeLeaf(-7.0, 8.0, -20.0);
	DrawColoredCubeLeaf(-7.0, 8.0, -21.0);

	DrawColoredCubeLeaf(-7.0, 7.0, -22.0);

	//Kiri
	DrawColoredCubeLeaf(-9.0, 8.0, -18.0);
	DrawColoredCubeLeaf(-10.0, 8.0, -18.0);

	DrawColoredCubeLeaf(-11.0, 7.0, -18.0);

	//Diagonal
	DrawColoredCubeLeaf(-5.0, 8.0, -16.0);
	DrawColoredCubeLeaf(-4.0, 7.0, -15.0);

	DrawColoredCubeLeaf(-5.0, 8.0, -20.0);
	DrawColoredCubeLeaf(-4.0, 7.0, -21.0);

	DrawColoredCubeLeaf(-9.0, 8.0, -20.0);
	DrawColoredCubeLeaf(-10.0, 7.0, -21.0);

	DrawColoredCubeLeaf(-9.0, 8.0, -16.0);
	DrawColoredCubeLeaf(-10.0, 7.0, -15.0);

	////Coconut
	//Pohon
	DrawColoredCubeCoconut(-6.0, 7.0, -17.0, 0.5, 0.5, 0.5);
	DrawColoredCubeCoconut(-8.0, 7.0, -17.0, 0.5, 0.5, 0.5);
	DrawColoredCubeCoconut(-6.0, 7.0, -19.0, 0.5, 0.5, 0.5);
	DrawColoredCubeCoconut(-8.0, 7.0, -19.0, 0.5, 0.5, 0.5);

	//Jatuh
	DrawColoredCubeCoconut(-8.0, 1.75, -14.0, 0.5, 0.5, 0.5);
	DrawColoredCubeCoconut(-11.0, 1.75, -16.0, 0.5, 0.5, 0.5);
	DrawColoredCubeCoconut(-10.0, 1.85, -15.0, 0.7, 0.7, 0.7);

	//======================================================================================================================================================

	////Bridge
	//Kanan
	DrawColoredCubeBrick(18.0, 1.0, -12.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(18.0, 1.0, -7.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(18.0, 1.0, -2.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(18.0, 1.0, 3.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(23.0, 1.0, -2.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(23.0, 1.0, 3.5, 1.0, 1.0, 1.0);

	//Torch
	DrawColoredCubeTrunk(24.0, 3.5, 4.5,      0.12, 1.0, 0.12);
	DrawColoredCubeTopTorch(24.0, 4.05, 4.5,  0.12, 0.12, 0.12);

	//Torch
	DrawColoredCubeTrunk(24.0, 3.5, -3.5, 0.12, 1.0, 0.12);
	DrawColoredCubeTopTorch(24.0, 4.05, -3.5, 0.12, 0.12, 0.12);

	DrawColoredCubeBrick(24.0, 3.0, -3.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(19.0, 3.0, -17.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(19.0, 3.0, -10.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(19.0, 3.0, -3.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(19.0, 3.0, 4.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(24.0, 3.0, 4.5, 1.0, 1.0, 1.0);

	//Kiri
	DrawColoredCubeBrick(12.0, 1.0, -12.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(12.0, 1.0, -7.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(12.0, 1.0, -2.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(12.0, 1.0, 3.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(7.0, 1.0, -2.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(7.0, 1.0, 3.5, 1.0, 1.0, 1.0);

	DrawColoredCubeBrick(6.0, 3.0, -3.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(11.0, 3.0, -17.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(11.0, 3.0, -10.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(11.0, 3.0, -3.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(11.0, 3.0, 4.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(6.0, 3.0, 4.5, 1.0, 1.0, 1.0);

	//Torch
	DrawColoredCubeTrunk(6.0, 3.5, 4.5, 0.12, 1.0, 0.12);
	DrawColoredCubeTopTorch(6.0, 4.05, 4.5, 0.12, 0.12, 0.12);

	//Torch
	DrawColoredCubeTrunk(6.0, 3.5, -3.5, 0.12, 1.0, 0.12);
	DrawColoredCubeTopTorch(6.0, 4.05, -3.5, 0.12, 0.12, 0.12);

	//Pagar Kanan
	DrawColoredCubeWodden(19.0, 3.0, -16.5,  0.2, 0.5, 1.0);
	DrawColoredCubeWodden(19.0, 3.0, -15.5,  0.2, 0.5, 1.0);
	DrawColoredCubeWodden(19.0, 3.0, -14.5,  0.2, 0.5, 1.0);
	DrawColoredCubeWodden(19.0, 3.0, -13.5,  0.2, 0.5, 1.0);
	DrawColoredCubeWodden(19.0, 3.0, -12.5,  0.2, 0.5, 1.0);
	DrawColoredCubeWodden(19.0, 3.0, -11.5,  0.2, 0.5, 1.0);

	DrawColoredCubeWodden(19.0, 3.0, -10.5,  0.2, 0.5, 1.0);
	DrawColoredCubeWodden(19.0, 3.0, -9.5,   0.2, 0.5, 1.0);
	DrawColoredCubeWodden(19.0, 3.0, -8.5,   0.2, 0.5, 1.0);
	DrawColoredCubeWodden(19.0, 3.0, -7.5,   0.2, 0.5, 1.0);
	DrawColoredCubeWodden(19.0, 3.0, -6.5,   0.2, 0.5, 1.0);
	DrawColoredCubeWodden(19.0, 3.0, -5.5,   0.2, 0.5, 1.0);
	DrawColoredCubeWodden(19.0, 3.0, -4.5,   0.2, 0.5, 1.0);

	DrawColoredCubeWodden(24.0, 3.0, -2.5,   0.2, 0.5, 1.0);
	DrawColoredCubeWodden(24.0, 3.0, -1.5,   0.2, 0.5, 1.0);
	DrawColoredCubeWodden(24.0, 3.0, -0.5,   0.2, 0.5, 1.0);
	DrawColoredCubeWodden(24.0, 3.0, 0.5,    0.2, 0.5, 1.0);
	DrawColoredCubeWodden(24.0, 3.0, 1.5,    0.2, 0.5, 1.0);
	DrawColoredCubeWodden(24.0, 3.0, 2.5,    0.2, 0.5, 1.0);
	DrawColoredCubeWodden(24.0, 3.0, 3.5,    0.2, 0.5, 1.0);

	//Pagar Kiri
	DrawColoredCubeWodden(11.0, 3.0, -16.5,  0.2, 0.5, 1.0);
	DrawColoredCubeWodden(11.0, 3.0, -15.5,  0.2, 0.5, 1.0);
	DrawColoredCubeWodden(11.0, 3.0, -14.5,  0.2, 0.5, 1.0);
	DrawColoredCubeWodden(11.0, 3.0, -13.5,  0.2, 0.5, 1.0);
	DrawColoredCubeWodden(11.0, 3.0, -12.5,  0.2, 0.5, 1.0);
	DrawColoredCubeWodden(11.0, 3.0, -11.5,  0.2, 0.5, 1.0);

	DrawColoredCubeWodden(11.0, 3.0, -10.5,  0.2, 0.5, 1.0);
	DrawColoredCubeWodden(11.0, 3.0, -9.5,   0.2, 0.5, 1.0);
	DrawColoredCubeWodden(11.0, 3.0, -8.5,   0.2, 0.5, 1.0);
	DrawColoredCubeWodden(11.0, 3.0, -7.5,   0.2, 0.5, 1.0);
	DrawColoredCubeWodden(11.0, 3.0, -6.5,   0.2, 0.5, 1.0);
	DrawColoredCubeWodden(11.0, 3.0, -5.5,   0.2, 0.5, 1.0);
	DrawColoredCubeWodden(11.0, 3.0, -4.5,   0.2, 0.5, 1.0);

	DrawColoredCubeWodden(6.0, 3.0, -2.5,    0.2, 0.5, 1.0);
	DrawColoredCubeWodden(6.0, 3.0, -1.5,    0.2, 0.5, 1.0);
	DrawColoredCubeWodden(6.0, 3.0, -0.5,    0.2, 0.5, 1.0);
	DrawColoredCubeWodden(6.0, 3.0, 0.5,     0.2, 0.5, 1.0);
	DrawColoredCubeWodden(6.0, 3.0, 1.5,     0.2, 0.5, 1.0);
	DrawColoredCubeWodden(6.0, 3.0, 2.5,     0.2, 0.5, 1.0);
	DrawColoredCubeWodden(6.0, 3.0, 3.5,     0.2, 0.5, 1.0);

	//Pagar Tampak Depan 
	DrawColoredCubeWodden(7.0, 3.0, 4.5,     1.0, 0.5, 0.2);
	DrawColoredCubeWodden(8.0, 3.0, 4.5,     1.0, 0.5, 0.2);
	DrawColoredCubeWodden(9.0, 3.0, 4.5,     1.0, 0.5, 0.2);
	DrawColoredCubeWodden(10.0, 3.0, 4.5,    1.0, 0.5, 0.2);
	DrawColoredCubeWodden(12.0, 3.0, 4.5,    1.0, 0.5, 0.2);
	DrawColoredCubeWodden(13.0, 3.0, 4.5,	 1.0, 0.5, 0.2);
	DrawColoredCubeWodden(14.0, 3.0, 4.5,	 1.0, 0.5, 0.2);
	DrawColoredCubeWodden(15.0, 3.0, 4.5,	 1.0, 0.5, 0.2);
	DrawColoredCubeWodden(16.0, 3.0, 4.5,	 1.0, 0.5, 0.2);
	DrawColoredCubeWodden(17.0, 3.0, 4.5,	 1.0, 0.5, 0.2);
	DrawColoredCubeWodden(18.0, 3.0, 4.5,	 1.0, 0.5, 0.2);
	DrawColoredCubeWodden(20.0, 3.0, 4.5,	 1.0, 0.5, 0.2);
	DrawColoredCubeWodden(21.0, 3.0, 4.5,	 1.0, 0.5, 0.2);
	DrawColoredCubeWodden(22.0, 3.0, 4.5,	 1.0, 0.5, 0.2);
	DrawColoredCubeWodden(23.0, 3.0, 4.5,	 1.0, 0.5, 0.2);

	DrawColoredCubeWodden(7.0, 3.0, -3.5,	 1.0, 0.5, 0.2);
	DrawColoredCubeWodden(8.0, 3.0, -3.5,	 1.0, 0.5, 0.2);
	DrawColoredCubeWodden(9.0, 3.0, -3.5,	 1.0, 0.5, 0.2);
	DrawColoredCubeWodden(10.0, 3.0, -3.5,	 1.0, 0.5, 0.2);

	DrawColoredCubeWodden(20.0, 3.0, -3.5,   1.0, 0.5, 0.2);
	DrawColoredCubeWodden(21.0, 3.0, -3.5,   1.0, 0.5, 0.2);
	DrawColoredCubeWodden(22.0, 3.0, -3.5,   1.0, 0.5, 0.2);
	DrawColoredCubeWodden(23.0, 3.0, -3.5,   1.0, 0.5, 0.2);

	////Bridge - Alas
	//Tengah
	for (double i = -18.5; i <= 4.5; i++) {
		for (double j = 11.0; j <= 19; j++) {
			DrawColoredCubeWodden(j, 2.0, i,  1.0, 1.0, 1.0);
		}
	}

	//Pucuk Kanan
	for (double i = -3.5; i <= 4.5; i++) {
		for (double j = 20; j <= 24; j++) {
			DrawColoredCubeWodden(j, 2.0, i,  1.0, 1.0, 1.0);
		}
	}

	//Pucuk Kiri
	for (double i = -3.5; i <= 4.5; i++) {
		for (double j = 6; j <= 10; j++) {
			DrawColoredCubeWodden(j, 2.0, i,  1.0, 1.0, 1.0);
		}
	}

	//======================================================================================================================================================

	////Boat
	//Pucuk Kanan = x : -29.5, z : -29.5

	for (double i = 16.5; i <= 18.5; i++) {
		for (double j = -23.5; j <= -15.5; j++) {
			DrawColoredCubeWodden(j, 1.0, i, 1.0, 1.0, 1.0);
		}
	}

	//Kanan
	for (double i = -23.5; i <= -15.5; i++) {
		DrawColoredCubeWodden(i, 1.8, 19.5,   1.0, 0.8, 1.0);
	}

	//Kiri
	for (double i = -23.5; i <= -15.5; i++) {
		DrawColoredCubeWodden(i, 1.8, 15.5,  1.0, 0.8, 1.0);
	}

	//Belakang
	DrawColoredCubeWodden(-23.63, 1.72, 16.5,  0.75, 0.5, 1.0);
	DrawColoredCubeWodden(-23.63, 1.72, 17.5,  0.75, 0.5, 1.0);
	DrawColoredCubeWodden(-23.63, 1.72, 18.5,  0.75, 0.5, 1.0);

	//Depan
	DrawColoredCubeWodden(-14.63, 1.2, 17.5,   0.75, 0.7, 1.0);
	DrawColoredCubeWodden(-13.89, 1.3, 17.5,   0.75, 0.4, 1.0);
	DrawColoredCubeWodden(-13.16, 1.75, 17.5,  0.75, 0.4, 1.0);

	DrawColoredCubeWodden(-14.63, 1.72, 15.5,  0.75, 0.5, 1.0);
	DrawColoredCubeWodden(-14.63, 1.72, 16.5,  0.75, 0.5, 1.0);
	DrawColoredCubeWodden(-14.63, 1.72, 17.5,  0.75, 0.5, 1.0);
	DrawColoredCubeWodden(-14.63, 1.72, 18.5,  0.75, 0.5, 1.0);
	DrawColoredCubeWodden(-14.63, 1.72, 19.5,  0.75, 0.5, 1.0);

	DrawColoredCubeWodden(-13.87, 1.72, 16.5, 0.75, 0.5, 1.0);
	DrawColoredCubeWodden(-13.87, 1.72, 17.5, 0.75, 0.5, 1.0);
	DrawColoredCubeWodden(-13.87, 1.72, 18.5, 0.75, 0.5, 1.0);


	//Tiang
	DrawColoredCubeTrunk(-22.5, 2.0, 17.5,   0.12, 1.0, 0.12);
	DrawColoredCubeTrunk(-22.5, 3.0, 17.5,   0.12, 1.0, 0.12);
	DrawColoredCubeTrunk(-22.5, 4.0, 17.5,   0.12, 1.0, 0.12);
	DrawColoredCubeTrunk(-22.5, 5.0, 17.5,   0.12, 1.0, 0.12);

	//Bendera
	DrawColoredCubeFlag(-23.0, 5.0, 17.5,   1.0, 0.75, 0.0);

	//Torch
	DrawColoredCubeTrunk(-13.2, 2.2, 17.5,     0.12, 1.0, 0.12);
	DrawColoredCubeTopTorch(-13.2, 2.75, 17.5,  0.12, 0.12, 0.12);


	//======================================================================================================================================================

	////Rumah - Dinding
	for (double i = -29.5; i <= -17.5; i++) {
		DrawColoredCubeWhiteWall(i, 2.0, -29.5,   1.0, 1.0, 1.0);
		DrawColoredCubeWhiteWall(i, 3.0, -29.5,   1.0, 1.0, 1.0);
		DrawColoredCubeWhiteWall(i, 4.0, -29.5,   1.0, 1.0, 1.0);
		DrawColoredCubeWhiteWall(i, 5.0, -29.5,   1.0, 1.0, 1.0);
		DrawColoredCubeWhiteWall(i, 5.635, -29.5, 1.0, 0.25, 1.0);
	}

	for (double i = -29.5; i <= -17.5; i++) {
		DrawColoredCubeWhiteWall(i, 2.0, -15.5,   1.0, 1.0, 1.0);
		DrawColoredCubeWhiteWall(i, 3.0, -15.5,   1.0, 1.0, 1.0);
		DrawColoredCubeWhiteWall(i, 4.0, -15.5,   1.0, 1.0, 1.0);
		DrawColoredCubeWhiteWall(i, 5.0, -15.5,   1.0, 1.0, 1.0);
		DrawColoredCubeWhiteWall(i, 5.635, -15.5, 1.0, 0.25, 1.0);
	}

	for (double i = -29.5; i <= -15.5; i++) {
		DrawColoredCubeWhiteWall(-29.5, 2.0, i,   1.0, 1.0, 1.0);
		DrawColoredCubeWhiteWall(-29.5, 3.0, i,   1.0, 1.0, 1.0);
		DrawColoredCubeWhiteWall(-29.5, 4.0, i,   1.0, 1.0, 1.0);
		DrawColoredCubeWhiteWall(-29.5, 5.0, i,   1.0, 1.0, 1.0);
		DrawColoredCubeWhiteWall(-29.5, 5.635, i, 1.0, 0.25, 1.0);
	}

	for (double i = -29.5; i <= -15.5; i++) {
		DrawColoredCubeWhiteWall(-17.5, 2.0, i,   1.0, 1.0, 1.0);
		DrawColoredCubeWhiteWall(-17.5, 3.0, i,   1.0, 1.0, 1.0);
		DrawColoredCubeWhiteWall(-17.5, 4.0, i,   1.0, 1.0, 1.0);
		DrawColoredCubeWhiteWall(-17.5, 5.0, i,   1.0, 1.0, 1.0);
		DrawColoredCubeWhiteWall(-17.5, 5.635, i, 1.0, 0.25, 1.0);
	}

	////Rumah - Banner --> Gurung Nggawe
	//DrawColoredCubeFlag(-23.0, 5.0, -14.0, 1.0, 0.75, 0.0);

	////Rumah - Pintu
	DrawColoredCubeDoor(-16.9, 2.5, -24.5, 0.2, 2.0, 1.0);

	DrawColoredCubeBrick(-17.2, 2.0, -25.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(-17.2, 3.0, -25.5, 1.0, 1.0, 1.0);

	DrawColoredCubeBrick(-17.2, 2.0, -23.5, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(-17.2, 3.0, -23.5, 1.0, 1.0, 1.0);

	DrawColoredCubeBrick(-17.2, 3.735, -25.5, 1.0, 0.5, 1.0);
	DrawColoredCubeBrick(-17.2, 3.735, -24.5, 1.0, 0.5, 1.0);
	DrawColoredCubeBrick(-17.2, 3.735, -23.5, 1.0, 0.5, 1.0);


	////Rumah - Cagak [1]
	DrawColoredCubeBrick(-17.2, 2.0, -29.45, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(-17.2, 3.0, -29.45, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(-17.2, 4.0, -29.45, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(-17.2, 5.0, -29.45, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(-17.2, 5.635, -29.45, 1.0, 0.25, 1.0);

	////Rumah - Cagak [2]
	DrawColoredCubeBrick(-17.2, 2.0, -15.2,   1.0, 1.0, 1.0);
	DrawColoredCubeBrick(-17.2, 3.0, -15.2,   1.0, 1.0, 1.0);
	DrawColoredCubeBrick(-17.2, 4.0, -15.2,   1.0, 1.0, 1.0);
	DrawColoredCubeBrick(-17.2, 5.0, -15.2,   1.0, 1.0, 1.0);
	DrawColoredCubeBrick(-17.2, 5.635, -15.2, 1.0, 0.25, 1.0);

	////Rumah - Cagak [3]
	DrawColoredCubeBrick(-29.45, 2.0, -15.2, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(-29.45, 3.0, -15.2, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(-29.45, 4.0, -15.2, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(-29.45, 5.0, -15.2, 1.0, 1.0, 1.0);
	DrawColoredCubeBrick(-29.45, 5.635, -15.2, 1.0, 0.25, 1.0);

	////Rumah - Plavon
	//for (double i = -29.5; i <= -15.5; i++) {
	//	for (double j = -29.5; j <= -17.5; j++) {
	//		DrawColoredCubeWhiteWall(j, 5.0, i, 1.0, 1.0, 1.0);
	//	}
	//}

	////Rumah - Genteng [Tampak Lebar]
	//DrawColoredCubeWodden(-29.5, 6.0, -14.5, 1.0, 0.5, 1.0);
	for (double i = -29.5; i <= -17.5; i++) {
		DrawColoredCubeWodden(i, 6.0, -14.5, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(i, 6.0, -29.5, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -18.5; i++) {
		DrawColoredCubeWodden(i, 6.5, -15.5, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(i, 6.5, -29.5, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -19.5; i++) {
		DrawColoredCubeWodden(i, 7.0, -16.5, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(i, 7.0, -29.5, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -20.5; i++) {
		DrawColoredCubeWodden(i, 7.5, -17.5, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(i, 7.5, -29.5, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -21.5; i++) {
		DrawColoredCubeWodden(i, 8.0, -18.5, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(i, 8.0, -29.5, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -22.5; i++) {
		DrawColoredCubeWodden(i, 8.5, -19.5, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(i, 8.5, -29.5, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -23.5; i++) {
		DrawColoredCubeWodden(i, 9.0, -20.5, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(i, 9.0, -29.5, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -24.5; i++) {
		DrawColoredCubeWodden(i, 9.5, -21.5, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(i, 9.5, -29.5, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -25.5; i++) {
		DrawColoredCubeWodden(i, 10.0, -22.5, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(i, 10.0, -29.5, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -26.5; i++) {
		DrawColoredCubeWodden(i, 10.5, -23.5, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(i, 10.5, -29.5, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -27.5; i++) {
		DrawColoredCubeWodden(i, 11.0, -24.5, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(i, 11.0, -29.5, 1.0, 0.5, 1.0);
	}

	
	////Rumah - Genteng [Tampak Panjang]
	for (double i = -29.5; i <= -14.5; i++) {
		DrawColoredCubeWodden(-16.5, 6.0, i, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(-29.5, 6.0, i, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -15.5; i++) {
		DrawColoredCubeWodden(-17.5, 6.5, i, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(-29.5, 6.5, i, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -16.5; i++) {
		DrawColoredCubeWodden(-18.5, 7.0, i, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(-29.5, 7.0, i, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -17.5; i++) {
		DrawColoredCubeWodden(-19.5, 7.5, i, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(-29.5, 7.5, i, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -18.5; i++) {
		DrawColoredCubeWodden(-20.5, 8.0, i, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(-29.5, 8.0, i, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -19.5; i++) {
		DrawColoredCubeWodden(-29.5, 8.5, i, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(-21.5, 8.5, i, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -20.5; i++) {
		DrawColoredCubeWodden(-22.5, 9.0, i, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(-29.5, 9.0, i, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -21.5; i++) {
		DrawColoredCubeWodden(-23.5, 9.5, i, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(-29.5, 9.5, i, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -22.5; i++) {
		DrawColoredCubeWodden(-24.5, 10.0, i, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(-29.5, 10.0, i, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -23.5; i++) {
		DrawColoredCubeWodden(-25.5, 10.5, i, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(-29.5, 10.5, i, 1.0, 0.5, 1.0);
	}

	for (double i = -29.5; i <= -24.5; i++) {
		DrawColoredCubeWodden(-26.5, 11.0, i, 1.0, 0.5, 1.0);
		DrawColoredCubeWodden(-29.5, 11.0, i, 1.0, 0.5, 1.0);
	}

	////Rumah - Genteng [Tampak Atas]
	for (double i = -29.5; i <= -24.5; i++) {
		for (double j = -29.5; j <= -27.5; j++) {
			DrawColoredCubeWodden(j, 11.0, i, 1.0, 0.5, 1.0);
		}
	}

	//DrawColoredCubeWhiteWall(-29.5, 2.0, -29.5, 1.0, 1.0, 1.0);

	//======================================================================================================================================================

	//Kursi 1
	DrawColoredCubeWodden(-13.5, 1.7, -29.0, 0.5, 0.5, 1.0);
	DrawColoredCubeWodden(-9.5, 1.7, -29.0, 0.5, 0.5, 1.0);
	DrawColoredCubeWodden(-11.5, 1.9, -29.0, 6.0, 0.2, 1.0);

	//Kursi 2
	DrawColoredCubeWodden(-16.5, 1.7, -21.5, 1.0, 0.5, 0.5);
	DrawColoredCubeWodden(-16.5, 1.7, -17.5, 1.0, 0.5, 0.5);
	DrawColoredCubeWodden(-16.5, 1.9, -19.5, 1.0, 0.2, 5.0);

	//======================================================================================================================================================

	DrawColoredCubeSun(0, 20.0, 0, 0.0, 0.0, 0.0);

	//DrawTexturedCubeX();
	//DrawColoredPlane();

	glDisable(GL_DEPTH_TEST);
}

void Demo::BuildColoredCubeSand() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("sandTerrain.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredCubeSand(double xPos, double yPos, double zPos)
{
	glUseProgram(shaderProgram);

	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(xPos, yPos, zPos));

	//model = glm::rotate(model, angle, glm::vec3(0, 1, 0));

	//model = glm::scale(model, glm::vec3(3, 3, 3));				//ORI
	//model = glm::scale(model, glm::vec3(scale, scale, scale));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredCubeWater() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("water.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glGenBuffers(1, &EBO3);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredCubeWater(double xPos, double yPos, double zPos)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(xPos, yPos, zPos));

	//model = glm::rotate(model, angle, glm::vec3(0, 1, 0));

	//model = glm::scale(model, glm::vec3(3, 3, 3));				//ORI
	//model = glm::scale(model, glm::vec3(scale, scale, scale));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredCubeTrunk() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("coconutBark.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO4);
	glGenBuffers(1, &VBO4);
	glGenBuffers(1, &EBO4);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO4);

	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredCubeTrunk(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(xPos, yPos, zPos));

	//model = glm::rotate(model, angle, glm::vec3(0, 1, 0));

	//model = glm::scale(model, glm::vec3(3, 3, 3));				//ORI
	model = glm::scale(model, glm::vec3(xScale, yScale, zScale));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredCubeLeaf() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("coconutLeaf.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO5);
	glGenBuffers(1, &VBO5);
	glGenBuffers(1, &EBO5);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO5);

	glBindBuffer(GL_ARRAY_BUFFER, VBO5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredCubeLeaf(double xPos, double yPos, double zPos)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(xPos, yPos, zPos));

	//model = glm::rotate(model, angle, glm::vec3(0, 1, 0));

	//model = glm::scale(model, glm::vec3(3, 3, 3));				//ORI
	//model = glm::scale(model, glm::vec3(scale, scale, scale));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredCubeCoconut() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture6);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("coconut.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO6);
	glGenBuffers(1, &VBO6);
	glGenBuffers(1, &EBO6);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO6);

	glBindBuffer(GL_ARRAY_BUFFER, VBO6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO6);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredCubeCoconut(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(xPos, yPos, zPos));

	//model = glm::rotate(model, angle, glm::vec3(0, 1, 0));

	//model = glm::scale(model, glm::vec3(3, 3, 3));				//ORI
	model = glm::scale(model, glm::vec3(xScale, yScale, zScale));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredCubeBrick() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("brick.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO7);
	glGenBuffers(1, &VBO7);
	glGenBuffers(1, &EBO7);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO7);

	glBindBuffer(GL_ARRAY_BUFFER, VBO7);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO7);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredCubeBrick(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(xPos, yPos, zPos));

	//model = glm::rotate(model, angle, glm::vec3(0, 1, 0));

	//model = glm::scale(model, glm::vec3(3, 3, 3));				//ORI
	model = glm::scale(model, glm::vec3(xScale, yScale, zScale));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredCubeWodden() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("wodden.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO8);
	glGenBuffers(1, &VBO8);
	glGenBuffers(1, &EBO8);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO8);

	glBindBuffer(GL_ARRAY_BUFFER, VBO8);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO8);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredCubeWodden(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture8);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(xPos, yPos, zPos));

	//model = glm::rotate(model, angle, glm::vec3(0, 1, 0));

	//model = glm::scale(model, glm::vec3(3, 3, 3));				//ORI
	model = glm::scale(model, glm::vec3(xScale, yScale, zScale));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredCubeFlag() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("indonesiaFlag.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO9);
	glGenBuffers(1, &VBO9);
	glGenBuffers(1, &EBO9);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO9);

	glBindBuffer(GL_ARRAY_BUFFER, VBO9);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO9);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredCubeFlag(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture9);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO9); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(xPos, yPos, zPos));

	//model = glm::rotate(model, angle, glm::vec3(0, 1, 0));

	//model = glm::scale(model, glm::vec3(3, 3, 3));				//ORI
	model = glm::scale(model, glm::vec3(xScale, yScale, zScale));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredCubeWhiteWall() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture10);
	glBindTexture(GL_TEXTURE_2D, texture10);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("whiteWall.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO10);
	glGenBuffers(1, &VBO10);
	glGenBuffers(1, &EBO10);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO10);

	glBindBuffer(GL_ARRAY_BUFFER, VBO10);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO10);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredCubeWhiteWall(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture10);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO10); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(xPos, yPos, zPos));

	//model = glm::rotate(model, angle, glm::vec3(0, 1, 0));

	//model = glm::scale(model, glm::vec3(3, 3, 3));				//ORI
	model = glm::scale(model, glm::vec3(xScale, yScale, zScale));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredCubeDoor() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture11);
	glBindTexture(GL_TEXTURE_2D, texture11);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("door.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO11);
	glGenBuffers(1, &VBO11);
	glGenBuffers(1, &EBO11);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO11);

	glBindBuffer(GL_ARRAY_BUFFER, VBO11);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO11);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredCubeDoor(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture11);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO11); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(xPos, yPos, zPos));

	//model = glm::rotate(model, angle, glm::vec3(0, 1, 0));

	//model = glm::scale(model, glm::vec3(3, 3, 3));				//ORI
	model = glm::scale(model, glm::vec3(xScale, yScale, zScale));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredCubeTopTorch() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture13);
	glBindTexture(GL_TEXTURE_2D, texture13);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("top_torch.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO13);
	glGenBuffers(1, &VBO13);
	glGenBuffers(1, &EBO13);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO13);

	glBindBuffer(GL_ARRAY_BUFFER, VBO13);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO13);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredCubeTopTorch(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale)
{
	glUseProgram(shaderProgram);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture13);
	//glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture13);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stexture2);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 1.0f);

	glBindVertexArray(VAO13); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(xPos, yPos, zPos));

	//model = glm::rotate(model, angle, glm::vec3(0, 1, 0));

	//model = glm::scale(model, glm::vec3(3, 3, 3));				//ORI
	model = glm::scale(model, glm::vec3(xScale, yScale, zScale));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredCubeSun() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture12);
	glBindTexture(GL_TEXTURE_2D, texture12);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("crate.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO12);
	glGenBuffers(1, &VBO12);
	glGenBuffers(1, &EBO12);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO12);

	glBindBuffer(GL_ARRAY_BUFFER, VBO12);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO12);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredCubeSun(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale)
{
	glUseProgram(shaderProgram);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture12);
	//glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture12);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->shaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(VAO12); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(xPos, yPos, zPos));

	//model = glm::rotate(model, angle, glm::vec3(0, 1, 0));

	//model = glm::scale(model, glm::vec3(3, 3, 3));				//ORI
	model = glm::scale(model, glm::vec3(xScale, yScale, zScale));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredCubeSkybox() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &skyboxTexture);
	glBindTexture(GL_TEXTURE_2D, skyboxTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("skybox.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(skyboxVAO);

	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredCubeSkybox(double xPos, double yPos, double zPos, double xScale, double yScale, double zScale)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, skyboxTexture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(xPos, yPos, zPos));

	//model = glm::rotate(model, angle, glm::vec3(0, 1, 0));

	//model = glm::scale(model, glm::vec3(3, 3, 3));				//ORI
	model = glm::scale(model, glm::vec3(xScale, yScale, zScale));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredPlane()
{
	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("sandTerrain.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-30.0, -0.5, -30.0,  0,  0,
		 30.0, -0.5, -30.0, 50,  0,
		 30.0, -0.5,  30.0, 50, 50,
		-30.0, -0.5,  30.0,  0, 50,


	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}

void Demo::DrawColoredPlane()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 1);

	glBindVertexArray(VAO2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::InitCamera()
{
	//ORI
	//posCamX = 0.0f;
	//posCamY = 5.0f;
	//posCamZ = 8.0f;
	
	//MOD
	posCamX = 0.0f;
	posCamY = 15.0f;
	posCamZ = 8.0f;

	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	//CAMERA_SPEED = 0.001f;
	CAMERA_SPEED = 0.010f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Demo::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}

void Demo::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}

void Demo::YCamera(float speed)
{
	float y = viewCamY - posCamY;
	posCamY = posCamY + y * speed;
	viewCamY = viewCamY + y * speed;
}

void Demo::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}

int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	app.Start("Bjorky", 1920, 1080, false, true);
	//vsync, fullscreen
}