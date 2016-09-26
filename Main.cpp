#define _SCL_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#include <cmath>
const int width = 640;
const int height = 480;

float* pixels = new float[width*height * 3];

struct Coord2d {
	Coord2d() {}
	Coord2d(double x, double y) {
		this->x = x;
		this->y = y;
	}
	double x = 0;
	double y = 0;
};
bool isCursorinsideCircle(Coord2d &cursor_coord, Coord2d &center_coord, double radius) {
	double x_displacement = cursor_coord.x - center_coord.x;
	double y_displacement = cursor_coord.y - center_coord.y;
	return  x_displacement* x_displacement + y_displacement*y_displacement < radius*radius;
}
void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& x0, const int& y0, const int& x1, const int& y1, const float& red, const float& green, const float& blue)
{
	const int i0 = (int)fmin(x0, x1);
	const int i1 = (int)fmax(x0, x1);
	int j0 = y0;
	int j1 = y1;

	if (i0 != x0)
	{
		j0 = y1;
		j1 = y0;
	}
	if (i0 != i1)
		for (int i = i0; i <= i1; i++)
		{
			const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

			drawPixel(i, j, red, green, blue);
		}
	else
		for (int i = j0; i <= j1; i++)
		{
			drawPixel(i0, i, red, green, blue);
		}
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	/*const int i0 = 100, i1 = 200;
	const int j0 = 50, j1 = 80;
	drawLine(i0, j0, i1, j1, 1.0f, 0.0f, 0.0f);*/

	//TODO: try moving object
}

int main(void)
{
	GLFWwindow* window;

	// 각 아이콘 동그라미들의 중심좌표
	Coord2d IconCenters[6];

	for (int i = 0; i < 6; i++) {
		IconCenters[i].x = 150 + 200 * (i / 2);
		IconCenters[i].y = 150 + 200 * (i % 2);
	}
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);
		double mouse_xpos, mouse_ypos;
		glfwGetCursorPos(window, &mouse_xpos, &mouse_ypos);
		//printf("Cursor loc : %lf, %lf \n", mouse_xpos, mouse_ypos);

		drawOnPixelBuffer();
		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		// 1. Thick Line
		for (int i = 0; i < 20; i++)
			drawLine(100, 150 + i, 200, 150 + i, 0, 0, 0);
		// 2. square
		drawLine(100, 300, 200, 300, 0, 0, 0);
		drawLine(100, 400, 200, 400, 0, 0, 0);
		drawLine(100, 300, 100, 400, 0, 0, 0);
		drawLine(200, 300, 200, 400, 0, 0, 0);
		// 3. filled square
		for (int i = 0; i <= 50; i++) {
			// 밑변
			drawLine(300, 300 + i, 400, 300 + i, 0, 0, 0);
			// 윗변
			drawLine(300, 400 - i, 400, 400 - i, 0, 0, 0);
			// 왼쪽 수직변
			drawLine(300 + i, 300, 300 + i, 400, 0, 0, 0);
			// 오른쪽 수직변
			drawLine(400 - i, 300, 400 - i, 400, 0, 0, 0);
		}
		// 4. triangle
		drawLine(300, 100, 400, 100, 0, 0, 0);
		drawLine(300, 100, 350, 200, 0, 0, 0);
		drawLine(350, 200, 400, 100, 0, 0, 0);
		// 5. pentagon center : 550,350
		for (int i = 0; i < 5; i++)
			drawLine(550 + 50 * cos((i * 72.0) *M_PI / 180.0), 350 + 50 * sin((i * 72.0) *M_PI / 180.0), 550 + 50 * cos(((i + 1) * 72.0) *M_PI / 180.0), 350 + 50 * sin(((i + 1) * 72.0) *M_PI / 180.0), 0, 0, 0);
		drawLine(550 + 50 * cos((3 * 72.0) *M_PI / 180.0), 350 + 50 * sin((3 * 72.0) *M_PI / 180.0), 550 + 50 * cos(((2) * 72.0) *M_PI / 180.0), 350 + 50 * sin(((2) * 72.0) *M_PI / 180.0), 0, 0, 0);
		// 6. circle 550,150
		for (int i = 0; i <= 360; i++) {
			drawPixel(550 + 50 * cos(i), 150 + 50 * sin(i), 0, 0, 0);
		}
		// Extended 1. Icon Circles
		for (int i = 0; i <= 360; i++) {
			for (Coord2d each : IconCenters) {
				if (isCursorinsideCircle(Coord2d(mouse_xpos, height - mouse_ypos), each, 80.0))
					drawPixel(each.x + 80 * cos(i), each.y + 80 * sin(i), 1.0, 0, 0);
				else
					drawPixel(each.x + 80 * cos(i), each.y + 80 * sin(i), 0, 1.0, 0);
			}
		}


		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}

