/* A Mandelbrot set visualizer.
** Copyright (C) 2024 Rivest Osz
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <https://www.gnu.org/licenses/>.
**/

#include "io/files.hpp"
#include "io/log.hpp"
#include "io/video.hpp"
#include "misc/config.hpp"
#include "misc/qoi.hpp"
#include <cmath>
#include <string>

namespace Raylib {
	#include <raylib.h>
};

const int screen_width = 1280;
const int screen_height = 960;

using namespace roBrot;

int main(int argc, const char **argv) {
	const char *err = nullptr;

	(void)read_config_from_args(argc, argv);

	if(init_window(screen_width, screen_height, "ro-brot", &err) < 0) {
		log_error("Couldn't initialize the window: %s\n", err);
		return 1;
	}

	Raylib::Shader shader = Raylib::LoadShader(nullptr, "./shader.fs");

	float off_x = 0.0, off_y = 0.0;
	float scale = 1.0;
	float max_iterations = 256;

	while(should_close_window() == false) {
		begin_frame();
		
		if(Raylib::IsKeyDown(Raylib::KEY_LEFT))
			off_x -= 0.1 * Raylib::GetFrameTime();
		if(Raylib::IsKeyDown(Raylib::KEY_RIGHT))
			off_x += 0.1 * Raylib::GetFrameTime();

		if(Raylib::IsKeyDown(Raylib::KEY_UP))
			off_y += 0.1 * Raylib::GetFrameTime();
		if(Raylib::IsKeyDown(Raylib::KEY_DOWN))
			off_y -= 0.1 * Raylib::GetFrameTime();

		if(Raylib::IsKeyDown(Raylib::KEY_KP_ADD))
			scale -= 0.1 * Raylib::GetFrameTime();
		if(Raylib::IsKeyDown(Raylib::KEY_KP_SUBTRACT))
			scale += 0.1 * Raylib::GetFrameTime();
		

		if(Raylib::IsKeyDown(Raylib::KEY_Q))
			max_iterations -= 4;
		if(Raylib::IsKeyDown(Raylib::KEY_W))
			max_iterations += 4;

		if(max_iterations < 4)
			max_iterations = 4;

		float mouse_x = Raylib::GetMouseX();
		float mouse_y = Raylib::GetMouseY();
		mouse_x /= screen_width;
		mouse_y /= screen_height;

		if(mouse_x < 0.0) mouse_x = 0.0;
		if(mouse_x > 1.0) mouse_x = 1.0;
		if(mouse_y < 0.0) mouse_y = 0.0;
		if(mouse_y > 1.0) mouse_y = 1.0;

		if(Raylib::IsMouseButtonPressed(Raylib::MOUSE_BUTTON_LEFT)) {
			off_x += mouse_x - 0.5;
			off_y += 1.0 - mouse_y - 0.5;
		}

		float wheel = Raylib::GetMouseWheelMove() * (-1.0);
		if(wheel < 0.0) wheel = -1.0;
		if(wheel > 0.0) wheel = +1.0;
		
		if(wheel != 0.0)
			scale += wheel * 0.05;

		Raylib::SetShaderValue(shader, Raylib::GetShaderLocation(shader, "off_x"), &off_x, Raylib::SHADER_UNIFORM_FLOAT);

		Raylib::SetShaderValue(shader, Raylib::GetShaderLocation(shader, "off_y"), &off_y, Raylib::SHADER_UNIFORM_FLOAT);

		Raylib::SetShaderValue(shader, Raylib::GetShaderLocation(shader, "scale"), &scale, Raylib::SHADER_UNIFORM_FLOAT);

		Raylib::SetShaderValue(shader, Raylib::GetShaderLocation(shader, "max_iterations"), &max_iterations, Raylib::SHADER_UNIFORM_FLOAT);

		Raylib::BeginShaderMode(shader);
			Raylib::DrawRectangle(0, 0, screen_width / 2, screen_height / 2, Raylib::BLACK);
			Raylib::DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height / 2, { 0xff, 0x00, 0xff, 0xff });
			Raylib::DrawRectangle(0, screen_height / 2, screen_width / 2, screen_height / 2, { 0xff, 0x00, 0xff, 0xff });
			Raylib::DrawRectangle(screen_width / 2, screen_height / 2, screen_width / 2, screen_height / 2, Raylib::BLACK);
		Raylib::EndShaderMode();

		std::string s = "ro-brot. Time: " + std::to_string(Raylib::GetFrameTime() * 1000) + " ms. FPS: " + std::to_string(1.0 / Raylib::GetFrameTime()) + " (" + std::to_string((int)max_iterations) + " iterations)";
		Raylib::SetWindowTitle(s.c_str());
		
		close_frame();
	};

	return 0;
}
