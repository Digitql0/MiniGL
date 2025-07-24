#include "MiniGL.hpp"

#include <iostream>

// Mathematics
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/ext/matrix_transform.hpp"

// MY OWN LIBRARIES
#include "shader.hpp"

int mousex = 0.0f;
int mousey = 0.0f;
unsigned int rectangleVAO;
unsigned int rectangleVBO;
GLFWwindow* frame;
int screenHeight;
int screenWidth;
char* screenTitle;
float rectangleVertices[] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.5f,  0.5f,
    -0.5f, -0.5f,
     0.5f,  0.5f,
    -0.5f,  0.5f,
};

Shader myShader;

bool WindowShouldClose() {
	return glfwWindowShouldClose(frame);
}

void CloseWindow() {
	glfwTerminate();
}

void drawRectangle(float posx, float posy, float width, float height, int r, int g, int b) {
	glm::vec3 rgb = glm::vec3(r/255.0f, g/255.0f, b/255.0f);
	myShader.setVec3("color", rgb);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(posx, posy, 0.0f));
	model = glm::scale(model, glm::vec3(width, height, 1.0f));
	myShader.setMat4("model", model);
	
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(0.0f, float(screenWidth), float(screenHeight), 0.0f);
	myShader.setMat4("projection", projection);	

	glBindVertexArray(rectangleVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void BeginDrawing() {
	processInput(frame);
	myShader.use();
}

void ClearBackground(int r, int g, int b) {
	glClearColor(r/255, g/255, b/255, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void EndDrawing() {
	glfwSwapBuffers(frame);
    glfwPollEvents();
}

void glfwSetup() {
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void GLADSetup() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void MakeWindow(int width, int height, const char* title) {
	std::cout << "1" << std::endl;
	glfwSetup();
	
	std::cout << "1" << std::endl;
	GLFWwindow* win = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	
	std::cout << "1" << std::endl;
	if (win == NULL) {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    std::cout << "1" << std::endl;
    glfwMakeContextCurrent(win);

    std::cout << "1" << std::endl;
	GLADSetup();

    std::cout << "1" << std::endl;
    glViewport(0, 0, width, height);

    std::cout << "1" << std::endl;
    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
    glfwSetCursorPosCallback(win, mouse_callback);
    glfwSetScrollCallback(win, scroll_callback);

    std::cout << "1" << std::endl;
    glEnable(GL_DEPTH_TEST);

	std::cout << "1" << std::endl;
	screenHeight = height;
	screenWidth = width;

	std::cout << "1" << std::endl;
	screenTitle = (char*)malloc(strlen(title) + 1);
	if (screenTitle != NULL) {
	    strcpy(screenTitle, title);
	}

	std::cout << "1" << std::endl;
	frame = win;

	myShader.MakeShader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");

    std::cout << "1" << std::endl;
    initializeRectangleVAO();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){

}

void initializeRectangleVAO() {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

	rectangleVAO = VAO;
	rectangleVBO = VBO;
}