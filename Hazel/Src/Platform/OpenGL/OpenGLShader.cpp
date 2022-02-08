#include "hzpch.h"
#include "glad/glad.h"
#include "OpenGLShader.h"
#include "Hazel/Renderer/Renderer.h"

namespace Hazel
{
	OpenGLShader::OpenGLShader(const std::string& vertSource, const std::string& fragSource)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar *source = (const GLchar *)vertSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			CORE_LOG_ERROR("Compile Vertex Shader Failed!:{0}", &infoLog[0]);
			HAZEL_ASSERT(false, "Compile Vertex Shader Error Stopped Debugging!");

			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar *)fragSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			CORE_LOG_ERROR("Compile Fragment Shader Failed!:{0}", &infoLog[0]);
			HAZEL_ASSERT(false, "Compile Fragment Shader Error Stopped Debugging!");

			// In this simple program, we'll just leave
			return ;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		// Link our program
		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			CORE_LOG_ERROR("Link Shaders Failed!:{0}", infoLog[0]);// TODO这里应该是错的
			HAZEL_ASSERT(false, "Link  Shaders Error Stopped Debugging!");

			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	void Hazel::OpenGLShader::Bind()
	{
		glUseProgram(m_RendererID);
	}

	void Hazel::OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}

	void Hazel::OpenGLShader::UploadUniformMat4(const std::string & uniformName, glm::mat4 matrix)
	{
		// glm::value_ptr返回的类型是GLfloat*, 应该是个数组
		glUniformMatrix4fv(
			glGetUniformLocation(m_RendererID, uniformName.c_str()),
			1, GL_FALSE, glm::value_ptr(matrix));
	}
	void OpenGLShader::UploadUniformVec4(const std::string & uniformName, glm::vec4 vec4)
	{
		glUniform4fv(
			glGetUniformLocation(m_RendererID, uniformName.c_str()),
			1, glm::value_ptr(vec4)
		);
	}

	void OpenGLShader::UploadUniformI1(const std::string & uniformName, int id)
	{
		glUniform1i(glGetUniformLocation(m_RendererID, uniformName.c_str()), id); // set it manually
	}
}
