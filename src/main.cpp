#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std; 

// Callback function that gets called whenever the window is resized.
// It updates the OpenGL viewport to match the new window dimensions.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{

    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const char *vertexShaderSource2 = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);\n"
    "}\0";



    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n\0";

    const char *fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 1.0f, 0.5f, 1.0f);\n"
    "}\n\0";



    // Initialize GLFW (the library that handles windows & input)
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    // Configure GLFW: enable 4x multisampling (anti-aliasing)
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Request OpenGL version 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window (800x600). If creation fails, exit.
    GLFWwindow* window = glfwCreateWindow(800, 600, "Opengl Engine", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to open GLFW window" << endl;
        return -1;
    }

    // Make the OpenGL context of the window current in this thread
    glfwMakeContextCurrent(window);

    // Initialize GLAD (loads all OpenGL function pointers)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // Set the initial viewport size
    glViewport(0, 0, 800, 600);

    // Register the callback so that the viewport updates when the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //Vertex shader compilation
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int vertexShader2;
    vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader2, 1, &vertexShaderSource2, NULL);
    glCompileShader(vertexShader2);

    //Fragment shader compilation
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int fragmentShader2;
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    //creating shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    //attaching shaders to program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //second shader program
    unsigned int shaderProgram2;
    shaderProgram2 = glCreateProgram();

    glAttachShader(shaderProgram2, vertexShader2);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    //delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(vertexShader2);
    glDeleteShader(fragmentShader); 
    glDeleteShader(fragmentShader2);

    // A simple triangle defined by three vertices
    float vertices1[] = {
        -0.9f, -0.5f, 0.0f,  // left
        0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top
    };

    float vertices2[] = {
        0.0f,-0.5f,0.0f, //left
        0.9f,-0.5f,0.0f, //right
        0.45f,0.5f,0.0f //bottom
    };

    // float vertices[] = {
    //      0.5f,  0.5f, 0.0f,  // top right
    //      0.5f, -0.5f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f,  // bottom left
    //     -0.5f,  0.5f, 0.0f   // top left 
    // };

    //indices for rectangle
    // unsigned int indices[] = {
    //     0,1,3,
    //     1,2,3
    // };


    unsigned int VAO[2], VBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2,VBO);

    //Bind first VAO and VBO
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);

    //Bind second VAO and VBO
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);

    // Main render loop: runs until the user closes the window
    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.42f, 0.55f, 0.63f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //create first triangle with first shader program
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //create second triangle with second shader program
        glUseProgram(shaderProgram2);

        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0 ,3);

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, 0);
        //glBindVertexArray(0);

        // Swap the front and back buffers 
        // (This displays whatever was drawn in the previous frame)
        glfwSwapBuffers(window);
        // Process pending events (keyboard, mouse, etc.)
        glfwPollEvents();    
    }

    // Clean up and close the program
    glfwTerminate();
    return 0;
}