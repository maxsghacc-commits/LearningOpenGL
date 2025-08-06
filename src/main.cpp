#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include "shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"




void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

int main(int, char**) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return 1;
    }


    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Ishaans a retard", NULL, NULL);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

        
    glfwMakeContextCurrent(window);

    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  


    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "ERROR: Could not load OpenGL" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Model Matrix
    glm::mat4 Model = glm::mat4(1.0f);
    Model = glm::rotate(Model, glm::radians(-55.0f), glm::vec3(1.0f,0.0f,0.0f));

    // View Maxtrix
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // Projection Matrix
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(40.0f), 800.0f / 600.0f, 0.0f, 100.0f);



    glClearColor(0.1f, 0.3f, 0.7f, 1.0f); // Set clear color

    Shader ourShader("/home/max/Desktop/MAGE/src/vertexShader.vs", "/home/max/Desktop/MAGE/src/fragmentShader.fs");     

float vertices[] = {
    // First triangle
     0.5f,  0.5f, 0.0f,  // top right
    -0.5f,  0.5f, 0.0f,  // top left
    -0.5f, -0.5f, 0.0f,  // bottom left

    // Second triangle
     0.5f,  0.5f, 0.0f,  // top right
    -0.5f, -0.5f, 0.0f,  // bottom left
     0.5f, -0.5f, 0.0f   // bottom right
};



    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    

    while (!glfwWindowShouldClose(window)) {
        float time = glfwGetTime();
        glClear(GL_COLOR_BUFFER_BIT);
        

        ourShader.use();

        // Model Matrix Locations and Sending
        int modelLocation = glGetUniformLocation(ourShader.ID, "model");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Model));

        // View Matrix Location and sending
        int viewLocation = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

        // Porjection matirx location and sending
        int projLocation = glGetUniformLocation(ourShader.ID, "proj");
        glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));
        
        // Color Uniform
        float function = sin(time) / 1.0f + 0.7f;
        int uniform = glGetUniformLocation(ourShader.ID, "sineColor");
        glUniform4f(uniform, function, 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glfwPollEvents(); ; // Clear the screen

        glfwSwapBuffers(window); 
    }

    glfwTerminate(); 
    return 0;
}
