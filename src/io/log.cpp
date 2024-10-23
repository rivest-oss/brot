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

#include "log.hpp"
#include <cstdarg>
#include <cstdio>

namespace roBrot {
	#define	RO_BROT_STR_DEBUG_LOG	"\x1b[96m[\x1b[95mDEBUG\x1b[96m]\x1b[0m "
	#define	RO_BROT_STR_INFO_LOG	"\x1b[93m[\x1b[33mINFO\x1b[93m]\x1b[0m "
	#define	RO_BROT_STR_ERROR_LOG	"\x1b[97m[\x1b[31mERROR\x1b[97m]\x1b[0m "
	
	int log_something(std::FILE *file, const char *pre, const char *format, std::va_list args) {
		(void)std::fprintf(file, "\x1b[93m[\x1b[43mroBrot\x1b[0m\x1b[93m]\x1b[0m%s", pre);
		int res = std::vfprintf(file, format, args);

		return res;
	};

	int log_debug(const char *format, ...) {
		va_list args;
		va_start(args, format);

		int res = log_something(stdout, RO_BROT_STR_DEBUG_LOG, format, args);

		va_end(args);

		return res;
	};

	int log_info(const char *format, ...) {
		va_list args;
		va_start(args, format);

		int res = log_something(stdout, RO_BROT_STR_INFO_LOG, format, args);

		va_end(args);

		return res;
	};

	int log_error(const char *format, ...) {
		va_list args;

		va_start(args, format);
		int res = log_something(stderr, RO_BROT_STR_ERROR_LOG, format, args);
		va_end(args);

		return res;
	};
};
