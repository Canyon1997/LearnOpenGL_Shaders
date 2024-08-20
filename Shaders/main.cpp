#include "OpenGLOperations.h"

int main()
{
	GLFWwindow* window = InitializeOpenGL();

	std::string VertexSource = GetVertexShaderSource("VertexShader1.glsl");
	std::string FragmentSource = GetFragmentShaderSource("FragmentShader1.glsl");

	unsigned int VertexShader = CreateVertexShader(VertexSource);
	unsigned int FragmentShader = CreateFragmentShader(FragmentSource);
	unsigned int ShaderProgram = CreateCompleteShader(VertexShader, FragmentShader);

	float Triangle1[] = {
		-1.0f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.0f, -0.5f, 0.0f
	};

	float Triangle2[] = {
		1.0f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.0f, -0.5f, 0.0f
	};

	unsigned int VAO[2];
	glGenVertexArrays(2, VAO);

	unsigned int VBO[2];
	glGenBuffers(2, VBO);

	// initialize VAO 1
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle1), Triangle1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// initialize VAO2
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle2), Triangle2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glViewport(0, 0, 800, 600);

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		//set background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//render
		glUseProgram(ShaderProgram);

		//set uniform value on fragement shader to change color over time each frame
		float timeValue = glfwGetTime();
		float pinkColor = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(ShaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, pinkColor, 0.4f, 0.7f, 1.0f);

		//Bind VAO 1
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Bind VAO2
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Swap color buffer and shows output to screen
		glfwSwapBuffers(window);

		//check if any events triggered
		glfwPollEvents();
	}


	// Clean-up
	glDeleteProgram(ShaderProgram);
	glfwTerminate();

	return 0;
}