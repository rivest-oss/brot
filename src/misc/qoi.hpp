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

#pragma once
#include "../nuclei.hpp"
#include "../io/stream.hpp"
#include "../io/log.hpp"

namespace roBrot {
	struct image_t {
		u32	width = 0;
		u32	height = 0;
		u8	*rgb = nullptr;
	};

	class QOI {
		private:
			struct rgb_t {
				u8 r = 0x00;
				u8 g = 0x00;
				u8 b = 0x00;
			};

		public:
			static int encode(image_t image, BaseStream *ws, const char **err) {
				if(*err != nullptr)
					return -1;
				if(ws == nullptr) {
					*err = "Write stream pointer is NULL";
					return -1;
				}

				if(image.width > 32768) {
					*err = "Image width is too large (> 32768)";
					return -1;
				}
				if(image.height > 32768) {
					*err = "Image height is too large (> 32768)";
					return -1;
				}

				ws->writeU32BE(0x716f6966, err); // "qoif".
				ws->writeU32BE(image.width, err);
				ws->writeU32BE(image.height, err);
				ws->writeU8(3, err); // 3 = RGB,4 = RGBA.
				ws->writeU8(1, err); // colorspace (all channels linear).

				if(*err != nullptr)
					return -1;

				rgb_t px, prev_px;
				rgb_t index[64];

				u32 len = image.width * image.height * 3;
				int run = 0;

				for(u32 i = 0; i < len; i += 3, prev_px = px) {
					px.r = image.rgb[i + 0],
					px.g = image.rgb[i + 1],
					px.b = image.rgb[i + 2];

					if(
						(px.r == prev_px.r) &&
						(px.g == prev_px.g) &&
						(px.b == prev_px.b)
					) {
						run++;

						if((run == 62) || (i >= len)) {
							ws->writeU8(0xc0 | (run - 1), err);
							run = 0;

							if(*err != nullptr)
								return -1;
						}

						continue;
					}

					if(run > 0) {
						ws->writeU8(0xc0 | (run - 1), err);
						run = 0;

						if(*err != nullptr)
							return -1;
					}

					u8 px_index = (px.r * 3 + px.g * 5 + px.b * 7 + 2805) % 64;

					if(
						(px.r == index[px_index].r) &&
						(px.g == index[px_index].g) &&
						(px.b == index[px_index].b)
					) {
						ws->writeU8(px_index, err);
						if(*err != nullptr)
							return -1;

						continue;
					}

					index[px_index] = px;

					i8 vr = px.r - prev_px.r;
					i8 vg = px.g - prev_px.g;
					i8 vb = px.b - prev_px.b;

					i8 vg_r = vr - vg;
					i8 vg_b = vb - vg;

					if(
						((vr > -3) && (vr < 2)) &&
						((vg > -3) && (vg < 2)) &&
						((vb > -3) && (vb < 2))
					) {
						ws->writeU8(0x40 | ((2 + vr) << 4) | ((2 + vg) << 2) | (2 + vb), err);
						if(*err != nullptr)
							return -1;

						continue;
					}

					if(
						(vg_r > -9) && (vg_r < 8) &&
						(vg > -33) && (vg < 32) &&
						(vg_b > -9) && (vg_b < 8)
					) {
						ws->writeU8(0x80 | (32 + vg), err);
						ws->writeU8(((8 + vg_r) << 4) | (8 + vg_b), err);

						if(*err != nullptr)
							return -1;

						continue;
					}

					ws->writeU8(0xfe, err);
					ws->writeU8(px.r, err);
					ws->writeU8(px.g, err);
					ws->writeU8(px.b, err);
					if(*err != nullptr)
						return -1;

					continue;
				};

				ws->writeU32BE(0x00000000, err);
				ws->writeU32BE(0x00000001, err);
				if(*err != nullptr)
					return -1;
				
				return 0;
			};
	};
};
