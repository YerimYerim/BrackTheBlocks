

#include "Renderer.h"
#define PI 3.14

Renderer::Renderer(GLfloat width, GLfloat height)
{ 
    GLuint VertexArrayID;
    screenRatio = width / height;
    shader = loadShader(objectVertexShader, objectfragmentShader);
    //particleShader = loadShader(objectVertexShader, objectfragmentShader);
    makeCirCle();

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glViewport(0, 0, width, height);
    glFrontFace(GL_CCW);
    
}
Renderer::~Renderer()
{
}
void Renderer::setupObjectRenderer( GameObject& gameObject, shape Shape )
{ 
    GLuint ColorSize;
    GLuint VertexSize;
    switch (Shape)
    {
    case CIRCLE:
        ColorSize = sizeof(circleColor);
        VertexSize = sizeof(circleVertexBuffer);
        gameObject = GameObject(circleVertexBuffer, circleColor, VertexSize, ColorSize);
        gameObject.drawCount = 36;
        break;
    case RECTANGLE:
       ColorSize = sizeof(rectangleVertexBuffer);
       VertexSize = sizeof(rectangleColorBuffer);
       gameObject = GameObject(rectangleVertexBuffer, rectangleColorBuffer, VertexSize, ColorSize);
       gameObject.drawCount = 6;
       break;
    default:
       break;
    }

    glGenBuffers(1, &gameObject.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, gameObject.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, gameObject.vertexPoseSize * sizeof(GLint), gameObject.vertexPosition, GL_STATIC_DRAW);

    glGenBuffers(1, &gameObject.colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, gameObject.colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, gameObject.colorPoseSize * sizeof(GLint), gameObject.colorPosition, GL_STATIC_DRAW);
}
void Renderer::updateRenderer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::makeCirCle()
{
    //circle 만들어주기
    GLfloat xPos[12];
    GLfloat yPos[12];

    for (int i = 0; i < 12; ++i)
    {
        xPos[i] = cos(PI / 180 * 30 * (i));
        yPos[i] = sin(PI / 180 * 30 * (i));
    }
    int posNum = 0;
    for (int i = 0; i < 12* 3 * 3; i += 9)
    {
        circleVertexBuffer[i] = xPos[posNum];
        circleVertexBuffer[i + 1] = yPos[posNum];
        circleVertexBuffer[i + 2] = 0;
     
        if (i == 11 * 3 * 3 )
        {
            circleVertexBuffer[i + 3] = xPos[0];
            circleVertexBuffer[i + 4] = yPos[0];
            circleVertexBuffer[i + 5] = 0;
        }
        else
        {
            circleVertexBuffer[i + 3] = xPos[posNum + 1];
            circleVertexBuffer[i + 4] = yPos[posNum + 1];
            circleVertexBuffer[i + 5] = 0;

        }

        circleVertexBuffer[i + 6] = 0;
        circleVertexBuffer[i + 7] = 0;
        circleVertexBuffer[i + 8] = 0;

        ++posNum;
    }

    for (int i = 0; i < 12 * 3 * 3; ++i)
    {
        circleColor[i] = 0.2f;
    }
   

}
unsigned int Renderer:: loadShader(const char* vertexShaderSource,const char* fragmentShaderSource)
{
    GLint Result = GL_FALSE;
    int InfoLogLength;

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(vertexShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

   
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(fragmentShader, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    return shaderProgram;
}
void Renderer::drawGameObject(GameObject& gameObject)
{ 
    glUseProgram(shader);
    GLuint attribPosLoc = glGetAttribLocation(shader, "aPos");
    glEnableVertexAttribArray(attribPosLoc);
    glBindBuffer(GL_ARRAY_BUFFER, gameObject.vertexBuffer);
    glVertexAttribPointer(attribPosLoc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)(0));

    GLuint attribColorLoc = glGetAttribLocation(shader, "aColor");
    glEnableVertexAttribArray(attribColorLoc);
    glBindBuffer(GL_ARRAY_BUFFER, gameObject.colorBuffer);
    glVertexAttribPointer(attribColorLoc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)(0));

    GLuint uniformRatio = glGetUniformLocation(shader, "aRatio");
    glUniform1f(uniformRatio, screenRatio);

    if (gameObject.colorPosition != NULL)
    {
        GLuint uniformTransform = glGetUniformLocation(shader, "aTransX");
        glUniform1f(uniformTransform, gameObject.Position.x);

        GLuint uniformTransformY = glGetUniformLocation(shader, "aTransY");
        glUniform1f(uniformTransformY, gameObject.Position.y);

        GLuint uniformSizeX = glGetUniformLocation(shader, "aSizeX");
        glUniform1f(uniformSizeX, gameObject.getScale().x);
        
        GLuint uniformSizeY = glGetUniformLocation(shader, "aSizeY");
        glUniform1f(uniformSizeY, gameObject.getScale().y);
    }
    glDrawArrays(GL_TRIANGLES, 0, gameObject.drawCount);
    glDisableVertexAttribArray(0);
}
void Renderer::drawParticle(GameObject& gameObject)
{
    glUseProgram(particleShader);
    glGenBuffers(1, &gameObject.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, gameObject.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, gameObject.vertexPoseSize * sizeof(GLint), gameObject.vertexPosition, GL_STATIC_DRAW);

    glGenBuffers(1, &gameObject.colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, gameObject.colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, gameObject.colorPoseSize * sizeof(GLint), gameObject.colorPosition, GL_STATIC_DRAW);

    GLuint attribPosLoc = glGetAttribLocation(particleShader, "aPos");
    glEnableVertexAttribArray(attribPosLoc);
    glBindBuffer(GL_ARRAY_BUFFER, gameObject.vertexBuffer);
    glVertexAttribPointer(attribPosLoc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)(0));

    GLuint attribColorLoc = glGetAttribLocation(particleShader, "aColor");
    glEnableVertexAttribArray(attribColorLoc);
    glBindBuffer(GL_ARRAY_BUFFER, gameObject.colorBuffer);
    glVertexAttribPointer(attribColorLoc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)(0));

    GLuint uniformRatio = glGetUniformLocation(shader, "aRatio");
    glUniform1f(uniformRatio, screenRatio);

    if (gameObject.colorPosition != NULL)
    {
        GLuint uniformTransform = glGetUniformLocation(particleShader, "aTransX");
        glUniform1f(uniformTransform, gameObject.Position.x);

        GLuint uniformTransformY = glGetUniformLocation(particleShader, "aTransY");
        glUniform1f(uniformTransformY, gameObject.Position.y);

        GLuint uniformSizeX = glGetUniformLocation(particleShader, "aSizeX");
        glUniform1f(uniformSizeX, gameObject.getScale().x);

        GLuint uniformSizeY = glGetUniformLocation(particleShader, "aSizeY");
        glUniform1f(uniformSizeY, gameObject.getScale().y);
    }
    glDrawArrays(GL_TRIANGLES, 0, gameObject.drawCount);
    glDisableVertexAttribArray(0);
}
