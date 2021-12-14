#include "GameUtility.h"

vec3 Normalize(vec3& Direction)
{
	
	GLfloat Norm = sqrtf(powf(Direction.x, 2) + powf(Direction.y, 2) + powf(Direction.z, 2));
	vec3 normalized = { Direction.x / Norm, Direction.y / Norm, Direction.z / Norm };

	return normalized;
}

void transScreenToGL(GLfloat screenWidth, GLfloat screenHeight,
	GLfloat inputX, GLfloat inputY, GLfloat* convertedX, GLfloat* convertedY)
{
	*convertedX = (GLfloat)((inputX - (GLfloat)screenWidth * 0.5f) * (GLfloat)(1.0f / (GLfloat)(screenWidth * 0.5f)));
	*convertedY = -(GLfloat)((inputY - (GLfloat)screenHeight * 0.5f) * (GLfloat)(1.0f / (GLfloat)(screenHeight * 0.5f)));
}
void transGameWorldToGL(GLfloat WorldWidth, GLfloat WorldHeight,GLfloat ScreenRatio,
	GLfloat gameWorldX, GLfloat gameWorldY, GLfloat* GLposX, GLfloat* GLposY)
{
		*GLposX = (GLfloat)(gameWorldX) / ((GLfloat)WorldWidth * 0.5f);
		*GLposY = (GLfloat)(gameWorldY) / ((GLfloat)WorldHeight * 0.5f) * (GLfloat)ScreenRatio;
}

void updateDeltaTime(float& deltatime, std::chrono::system_clock::time_point& lastTime)
{
	std::chrono::system_clock::time_point curTime = std::chrono::system_clock::now();
    deltatime = (curTime - lastTime).count()* 0.00001f;
	lastTime = curTime;
}
unsigned int loadShader(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    GLint Result = GL_FALSE;
    int InfoLogLength;

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(vertexShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(fragmentShader, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    GLint linkSuccess;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(shaderProgram, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
        exit(1);
    }
    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShader);


    return shaderProgram;
}
