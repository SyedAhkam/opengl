#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <main.h>

#include <iostream>

// A callback function that executes on every window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); // set viewport size to new dimensions
}

int main() {
    // Init GLFW
    glfwInit();

    // Set window hints before creating a window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // major version of opengl should be 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // minor version should be 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // make sure to use the core profile

    // Create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Opengl", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create window" << std::endl;
        
        glfwTerminate();
        return -1;
    }

    // Make the window visible or make context of window 'current'
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress )) {
        std::cout << "Failed to Initialize GLAD" << std::endl;
        return -1;
    }

    // Set viewport size (yes, this is different than the window size)
    glViewport(0, 0, 800, 600);

    // Bind the window resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Main window/render loop
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window); // swaps the back buffer to the front (double buffering)
        glfwPollEvents(); // start polling events
    }

    // Clean resources and exit
    glfwTerminate();
    std::cout << "Bye" << std::endl;

    return 0;
}
