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

#include "video.hpp"

namespace Raylib {
	#include <raylib.h>
};

namespace roBrot {
	int init_window(int width, int height, const char *title, const char **err) {
		(void)err;

		Raylib::SetTargetFPS(60);
		Raylib::SetExitKey(0);

		Raylib::InitWindow(width, height, title);
		while(Raylib::IsWindowReady() == false);

		return 0;
	};

	void deinit_window(void) {
		Raylib::CloseWindow();
	};

	bool should_close_window(void) {
		return Raylib::WindowShouldClose();
	};

	void begin_frame(void) {
		Raylib::BeginDrawing();
		Raylib::ClearBackground(Raylib::BLACK);
	};

	void close_frame(void) {
		Raylib::EndDrawing();
		Raylib::SwapScreenBuffer();
	};
};
