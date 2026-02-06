
#include "helpers.h"
#include "stb/stb_image.h"

int loadTexture(GLuint tex, GLint repeat, const char* file)
{
	int res = -1;

	int width, height, nrChannels;
	unsigned char* data;
	data = stbi_load(file, &width, &height, &nrChannels, 0);
	
	if (data)
	{
		glBindTexture(GL_TEXTURE_2D, tex);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, (nrChannels == 4 ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		if (repeat == GL_CLAMP_TO_BORDER)
		{
			float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); //use this for GL_CLAMP_TO_BORDER
		}

		stbi_image_free(data);

		res = 0;
	}

	return res;
}

struct Camera {
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Euler Angles (for mouse rotation)
    float Yaw;
    float Pitch;

    // Camera options
    float MovementSpeed;
    float MouseSensitivity;

    // Constructor
    Camera(glm::vec3 position = glm::vec3(0.0f, 2.0f, 5.0f)) {
        Position = position;
        WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        Yaw = -90.0f; // pointing along negative Z
        Pitch = 0.0f;
        Front = glm::vec3(0.0f, 0.0f, -1.0f);
        MovementSpeed = 2.5f;
        MouseSensitivity = 0.1f;
        updateCameraVectors();
    }

    // Returns the View Matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // Process Keyboard (WASD)
    void ProcessKeyboard(int direction, float deltaTime) {
        float velocity = MovementSpeed * deltaTime;
        if (direction == 0) Position += Front * velocity; // W (Forward)
        if (direction == 1) Position -= Front * velocity; // S (Backward)
        if (direction == 2) Position -= Right * velocity; // A (Left)
        if (direction == 3) Position += Right * velocity; // D (Right)

        // Optional: Keep camera on a specific height if you want "Walking" instead of "Flying"
        // Position.y = 0.0f; 
    }

    // Process Mouse Movement
    void ProcessMouseMovement(float xoffset, float yoffset) {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // Constrain pitch so screen doesn't flip
        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;

        updateCameraVectors();
    }

private:
    // Recalculates the Front/Right/Up vectors from the updated Euler angles
    void updateCameraVectors() {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        // Re-calculate Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
} g_camera;

void processKeyboard(int direction, float deltaTime) {
    g_camera.ProcessKeyboard(direction, deltaTime);
}

// Process Mouse Movement
void processMouseMovement(float xoffset, float yoffset) {
    g_camera.ProcessMouseMovement(xoffset, yoffset);
}

const glm::mat4 getViewMatrix()
{
    return g_camera.GetViewMatrix();
}

const glm::vec3 getCameraPosition()
{
    return g_camera.Position;
}