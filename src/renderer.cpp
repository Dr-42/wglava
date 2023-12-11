#include "renderer.h"

#include <GLFW/glfw3.h>
#include <cstdio>
#include <string>

std::string vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;

out vec4 color;
void main(){
	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
	color = aColor;
}
)";

std::string fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

in vec4 color;
void main(){
	FragColor = color;
}
)";

Renderer::Renderer(){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(800, 600, "Audio Visualizer", NULL, NULL);
	glfwMakeContextCurrent(window);	

	// Initialize GLEW	
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK){
		printf("GLEW initialization failed!\n");
	}

	// Create vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderSourcePtr = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSourcePtr, NULL);
	glCompileShader(vertexShader);

	// Check for errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("Vertex shader compilation failed: %s\n", infoLog);
	}

	// Create fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentShaderSourcePtr = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSourcePtr, NULL);
	glCompileShader(fragmentShader);

	// Check for errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("Fragment shader compilation failed: %s\n", infoLog);
	}

	// Create shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check for errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("Shader program linking failed: %s\n", infoLog);
	}

	// Delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Create vertex array object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create vertex buffer object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Create element buffer object
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Set vertex attributes
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Renderer::~Renderer(){
	// Delete buffers
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// Delete vertex array object
	glDeleteVertexArrays(1, &VAO);

	// Delete shader program
	glDeleteProgram(shaderProgram);
}

void Renderer::Begin(){
	// Use shader program
	glUseProgram(shaderProgram);
	glfwSwapBuffers(window);
	glfwPollEvents();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::End(){
	// Clear buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::DrawRect(Rect rect, Color color){
	// Create vertices
	glBindVertexArray(VAO);
	float vertices[] = {
		rect.x, rect.y, color.r, color.g, color.b, color.a,
		rect.x + rect.w, rect.y, color.r, color.g, color.b, color.a,
		rect.x + rect.w, rect.y + rect.h, color.r, color.g, color.b, color.a,
		rect.x, rect.y + rect.h, color.r, color.g, color.b, color.a
	};

	// Create indices
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	// Bind buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Set buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
