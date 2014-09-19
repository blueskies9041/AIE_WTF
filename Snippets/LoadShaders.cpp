

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <algorithm>

GLuint LoadShaders(const char * vertexPath, const char * fragmentPath)
{
	/* SHADER CREATION FROM FILE INPUT */
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//read in vertex shader code from file
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexPath, std::ios::in); // http://www.cplusplus.com/reference/fstream/ifstream/ -- Maybe read up on it later.
	if (vertexShaderStream.is_open)
	{
		std::string line = "";									//empty string to store the text from the stream into
		while (std::getline(vertexShaderStream, line))			//reads in text from the stream http://www.cplusplus.com/reference/string/string/getline/
		{
			vertexShaderCode += ("\n" + line);
		}
		vertexShaderStream.close();								//appropriately closes the stream after we're done reading in text
	}

	//read in fragment shader code from file
	//exact same process as vertex shader
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentPath, std::ios::in); // http://www.cplusplus.com/reference/fstream/ifstream/ -- Maybe read up on it later.
	if (fragmentShaderStream.is_open)
	{
		std::string line = "";										//empty string to store the text from the stream into
		while (std::getline(fragmentShaderStream, line))			//reads in text from the stream http://www.cplusplus.com/reference/string/string/getline/
		{
			fragmentShaderCode += ("\n" + line);
		}
		fragmentShaderStream.close();								//appropriately closes the stream after we're done reading in text
	}

	/* SHADER COMPILATION AND DEBUGGING */
	GLint result = GL_FALSE;
	int infoLogLength;

	//compile vertex shader
	printf("Compiling Shader: %s\n", vertexPath);
	char const * vertexSourcePtr = vertexShaderCode.c_str();
	glShaderSource(	vertexShaderID,		// param 1: shader - handle of the shader object whose source code is to be replaced
					1,					// param 2: count - numer of elements in the string and lengh arrays
					&vertexSourcePtr,	// param 3: string - specifies an array of pointers to strings containing the source code to be loaded into the shader
					NULL);				// param 4: length - specifies an array of string lengths (unecessary for this)
	glCompileShader(vertexShaderID);	// self expanetory, compiles the shader linked to the shader object provided
	
	//check vertex shader
	//couldn't find these on http://docs.gl/ found documentation for glGetShaderiv at http://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetShaderiv.xml

		//first call is going to ask our vertex shader about its compilation status, and return GL_TRUE or GL_FALSE to the result variable.
	glGetShaderiv(	vertexShaderID,		// param 1: shader - shader to be queried
					GL_COMPILE_STATUS,	// param 2: pname - object paramater, valid choice are: GL_SHADER_TYPE, GL_DELETE_STATUS, GL_COMPILE_STATUS, GL_INFO_LOG_LENGTH, GL_SHADER_SOURCE_LENGTH
					&result);			// param 3: params - returns the requested object paramater, far as I can tell will return GL_TRUE or GL_FALSE to "result" as I declared it above
		//second call is going to ask our vertex shader how long its info log is, and return it to the infoLogLength variable.
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> vertexShaderErrMsg(infoLogLength); //creates a vector of characters with size equal to the number we got from the second glGetShaderiv call.
	glGetShaderInfoLog(	vertexShaderID, // param 1: shader - ""
						infoLogLength,	// param 2: maxLength - size of the character buffer for storing the returned info log.
						NULL,			// param 3: length - returns the length of the string returned in infoLog (param 4), excluding the null terminator. Not needed. 
						&vertexShaderErrMsg[0]); // param 4: ingoLog - the array of characters that is used to reutrn the information log.
	std::fprintf(stdout, "%s\n", &vertexShaderErrMsg); //Outputs the info log to stdout

	//repeating EXACT SAME process for fragment shader
	//compile fragment shader
	printf("Compiling Shader: %s\n", fragmentPath);
	char const * fragmentSourcePtr = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePtr, NULL);				
	glCompileShader(fragmentShaderID);	

	//check fragment shader
	glGetShaderiv(fragmentShaderID,	GL_COMPILE_STATUS,	&result);			
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> fragmentShaderErrMsg(infoLogLength); 
	glGetShaderInfoLog(fragmentShaderID, infoLogLength,	NULL,&fragmentShaderErrMsg[0]); 
	std::fprintf(stdout, "%s\n", &fragmentShaderErrMsg); 

	/* SHADER PROGRAM LINKING, DEBUGGING, AND CLEANUP */

	//attaching the vertex and fragment shaders and then linking the program
	fprintf(stdout, "Linking Program\n");
	GLuint shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);
	glLinkProgram(shaderProgramID);

	//final checks, same theory and format as the glGetShaderiv thing from the vertex shader section
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &result);
	glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> programErrMsg(std::max(infoLogLength, int(1)));
	glGetProgramInfoLog(shaderProgramID, infoLogLength, NULL, &programErrMsg[0]);
	fprintf(stdout, "%s\n", &programErrMsg[0]);

	//delete the individual shaders as we no longer need them.
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	//finally return the combined and error checked programID to openGL for use in draw calls.
	return shaderProgramID;
}