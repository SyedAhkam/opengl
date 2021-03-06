#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <main.h>

// Constants
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float triangle_vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

// A callback function that executes on every window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); // set viewport size to new dimensions
}

// Process inputs
void processInput(GLFWwindow* window) {
    // Check if escape key is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1); // if yes, set 'windowShouldClose' value to 1 ie. true
    }
}

void loadShaders() {
    // Create and compile the vertex shader
    unsigned int vertexShader;
    
    vertexShader = glCreateShader(GL_VERTEX_SHADER); // creates a vertex shader object

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // binds the vertex shader source to the shader object
    glCompileShader(vertexShader);

    // Store logs and success indicator here
    int success;
    char infoLog[512];

    // Check if vertex shader compilation was successful
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // query the shader compile status
    
    // If unsuccessful,
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); // fetches the shader compile logs

        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Create and compile the fragment shader
    unsigned int fragmentShader;

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // creates a fragment shader object

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // binds the fragment shader source to the shader object
    glCompileShader(fragmentShader);

    // Check if fragment shader compilation was successful
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    // If unsuccessful,
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog); // fetches the shader compile logs

        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Create a shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    
    // Attach shaders to program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Link shader program
    glLinkProgram(shaderProgram);

    // Check if linking the program was successful
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    // If unsuccessful,
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

        std::cout << "ERROR:SHADER_PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }
    
    // Use/Activate the shader program
    glUseProgram(shaderProgram);

    // Shader objects are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void loadVertices() {
    // NOTE: Always generate VAO before any VBO's

    // Create a vertex array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    
    // Generate a vertex buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
 
    // Bind the vertex array object for use
    glBindVertexArray(VAO);

    // Bind the vertex buffer object with target as an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Set 'BufferData' as our triangle_vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

    // Hint/point opengl how to interpret our vertices array
    glVertexAttribPointer(
        0,                  // Index of the vertex attribute
        3,                  // Size of the vertex attribute
        GL_FLOAT,           // Type of the data
        GL_FALSE,           // Should the data be normalized?
        3 * sizeof(float),  // This is the stride ie. the byte offset between vertex attributes
        (void*)0            // Offset of the first vertex attribute  
    );

    // Enable VertexAttribArray
    glEnableVertexAttribArray(0);
   }

// Perform all the rendering here
void doRendering(GLFWwindow* window) {
    // Clear the screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // sets the ClearColor state
    glClear(GL_COLOR_BUFFER_BIT); // clears the entire buffer

    // Draw the triangle !!
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main() {
    // Init GLFW
    glfwInit();

    // Set window hints before creating a window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // major version of opengl should be 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // minor version should be 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // make sure to use the core profile

    // Create a window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello Opengl", NULL, NULL);
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
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // Bind the window resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load our shaders
    loadShaders();

    // Load vertices
    loadVertices();

    // Main window/render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window); // process inputs if any

        // Do all the rendering in this function
        doRendering(window);

        glfwSwapBuffers(window); // swaps the back buffer to the front (double buffering)
        glfwPollEvents(); // start polling events
    }

    // Clean resources and exit
    glfwTerminate();
    std::cout << "Bye" << std::endl;

    return 0;
}
