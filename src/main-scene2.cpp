// Bryn Mawr College, alinen, 2020
//

#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include "mesh.h"
#include "osutils.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "myparticlesystem.h"
#include "renderer.h"

using namespace std;
using namespace glm;
using namespace agl;

// globals
Mesh theModel;
int theCurrentModel = 0;
vector<string> theModelNames;

//these will be used for clamping
vec3 minDimentions;
vec3 maxDimentions;

mat4 projectionMatrix;
mat4 modelMatrix;
glm::mat4 mv;
mat4 viewMatrix;

float heightGlobal;
float widthGlobal;

float clickPosX = 0;
float clickPosY = 0;
float changeX = 0;
float changeY = 0;
double scrollPosX = 0;
double scrollPosY = 0;
float dist = 1.0f;
float Azimuth = 0.0f;
float Elevation = 0.0f;

// OpenGL IDs
GLuint theVboPosId;
GLuint theVboNormalId;
GLuint theElementbuffer;

MyParticleSystem theSystem;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   if (action != GLFW_PRESS) return;

   if (key == GLFW_KEY_ESCAPE)
   {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
   }
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   // Prevent a divide by zero
   if (height == 0) height = 1;

   // Set Viewport to window dimensions
   glViewport(0, 0, width, height);
   ParticleSystem::GetRenderer().perspective(radians(60.0f), 1.0f, 0.1f, 100.0f);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // TODO: Camera controls
    clickPosX = xpos;
    clickPosY = ypos;

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS)
    {
        int keyPress = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
        if (keyPress == GLFW_PRESS)
        {
        }
    }
    else if (state == GLFW_RELEASE)
    {
    }
}

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    double xFpos, yFpos;
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state != GLFW_PRESS)
    {
    }
    else
    {
        int keyPress = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
        if (keyPress == GLFW_PRESS)
        {

            glfwGetCursorPos(window, &xFpos, &yFpos);
            scrollPosX = xFpos;
            scrollPosY = yFpos;

            dist = dist + .01 * (scrollPosY - clickPosY);

            clickPosX = scrollPosX;
            clickPosY = scrollPosY;
        }
        {

            glfwGetCursorPos(window, &xFpos, &yFpos);
            scrollPosX = xFpos;
            scrollPosY = yFpos;

            float changeX = scrollPosX - clickPosX;
            float changeY = scrollPosY - clickPosY;

            clickPosX = scrollPosX;
            clickPosY = scrollPosY;

            Azimuth = Azimuth + .01 * changeX;
            Elevation = Elevation + changeY * .01;

            // cout << Azimuth << endl;
            // cout << Elevation << endl;
        }
    }
}

static void LoadModel(const std::string &dir)
{
    std::vector<std::string> filenames = GetFilenamesInDir(dir, "ply");
    std::string filename = filenames[0];
    theModelNames.push_back(dir + filename);
    cout << dir + filename << endl;

    theModel.loadPLY(theModelNames[0]);

    minDimentions = theModel.getMinBounds();
    maxDimentions = theModel.getMaxBounds();

    // modelMatrix = theModel.positions();

    // //translation and scaling the model matrix
    float scaleX = fabs((maxDimentions.x - minDimentions.x));
    float scaleY = fabs((maxDimentions.y - minDimentions.y));
    float scaleZ = fabs((maxDimentions.z - minDimentions.z));

    float maxValueXY = std::max(scaleX, scaleY);
    float maxValueXZ = std::max(scaleX, scaleZ);
    float finalMax = std::max(maxValueXY, maxValueXZ);

    float centerX = (maxDimentions.x + minDimentions.x) / 2;
    float centerY = (maxDimentions.y + minDimentions.y) / 2;
    float centerZ = (maxDimentions.z + minDimentions.z) / 2;

    // vec3 lookAt =
    glm::mat4 scaled = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / finalMax, 1.0f / finalMax, 1.0f / finalMax));
    glm::mat4 translated = glm::translate(glm::mat4(1.0f), glm::vec3(-centerX, -centerY, -centerZ));
    modelMatrix = scaled * translated;

    glBindBuffer(GL_ARRAY_BUFFER, theVboPosId);
    glBufferData(GL_ARRAY_BUFFER, theModel.numVertices() * 3 * sizeof(float), theModel.positions(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, theVboNormalId);
    glBufferData(GL_ARRAY_BUFFER, theModel.numVertices() * 3 * sizeof(float), theModel.normals(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theElementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, theModel.numTriangles() * 3 * sizeof(unsigned int), theModel.indices(), GL_DYNAMIC_DRAW);
}

static std::string LoadShaderFromFile(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cout << "Cannot load file: " << fileName << std::endl;
        return "";
    }

    std::stringstream code;
    code << file.rdbuf();
    file.close();

    return code.str();
}

static void PrintShaderErrors(GLuint id, const std::string label)
{
    std::cerr << label << " failed\n";
    GLint logLen;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLen);
    if (logLen > 0)
    {
        char *log = (char *)malloc(logLen);
        GLsizei written;
        glGetShaderInfoLog(id, logLen, &written, log);
        std::cerr << "Shader log: " << log << std::endl;
        free(log);
    }
}

static GLuint LoadShader(const std::string &vertex, const std::string &fragment)
{
    GLint result;
    std::string vertexShader = LoadShaderFromFile(vertex);
    const char *vertexShaderRaw = vertexShader.c_str();
    GLuint vshaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshaderId, 1, &vertexShaderRaw, NULL);
    glCompileShader(vshaderId);
    glGetShaderiv(vshaderId, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        PrintShaderErrors(vshaderId, "Vertex shader");
        return -1;
    }

    std::string fragmentShader = LoadShaderFromFile(fragment);
    const char *fragmentShaderRaw = fragmentShader.c_str();
    GLuint fshaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshaderId, 1, &fragmentShaderRaw, NULL);
    glCompileShader(fshaderId);
    glGetShaderiv(fshaderId, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        PrintShaderErrors(fshaderId, "Fragment shader");
        return -1;
    }

    GLuint shaderId = glCreateProgram();
    glAttachShader(shaderId, vshaderId);
    glAttachShader(shaderId, fshaderId);
    glLinkProgram(shaderId);
    glGetShaderiv(shaderId, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        PrintShaderErrors(shaderId, "Shader link");
        return -1;
    }
    return shaderId;
}

int main(int argc, char** argv)
{
   GLFWwindow* window;

   if (!glfwInit())
   {
      return -1;
   }

   // Explicitly ask for a 4.0 context 
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   /* Create a windowed mode window and its OpenGL context */
   float width = 500;
   float height = 500;
   window = glfwCreateWindow(width, height, "Particle Viewer", NULL, NULL);
   if (!window)
   {
      glfwTerminate();
      return -1;
   }

   glfwMakeContextCurrent(window);
   glfwSetKeyCallback(window, key_callback);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   glfwSetMouseButtonCallback(window, mouse_button_callback);
   glfwSetScrollCallback(window, scroll_callback);
   glfwSetCursorPosCallback(window, cursor_position_callback);

#ifndef APPLE
   if (glewInit() != GLEW_OK)
   {
      cout << "Cannot initialize GLEW\n";
      return -1;
   }
#endif

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   glClearColor(0, 0, 0, 1);

   LoadModel("../model/");
   theModel.initBuffer();

   theSystem.init(500); // TODO: Set number of particles here
   float fov = radians(30.0f);
   ParticleSystem::GetRenderer().perspective(fov, 1.0f, 0.1f, 10.0f);
   ParticleSystem::GetRenderer().lookAt(vec3(0, 0, 4), vec3(0, 0, 0));

   float lastTime = glfwGetTime();
   while (!glfwWindowShouldClose(window))
   {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers

      float dt = glfwGetTime() - lastTime;
      lastTime = glfwGetTime();

    //   theModel.renderer();

      theSystem.update(dt);
      theSystem.draw();

      // Swap front and back buffers
      glfwSwapBuffers(window);

      // Poll for and process events
      glfwPollEvents();
   }

   glfwTerminate();
   return 0;
}

