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

#include "stream.hpp"

namespace roBrot {
	u8 BaseStream::readU8(const char **err) {
		u8 buff[1];

		if(*err != nullptr)
			return (-1);

		if(read(buff, 1, err) < 0)
			return (-1);

		return buff[0];
	};
	
	u16 BaseStream::readU16BE(const char **err) {
		u8 buff[2];

		if(*err != nullptr)
			return (-1);

		if(read(buff, 2, err) < 0)
			return (-1);
		
		return (
			(((u16)buff[0]) << 8) |
			((u16)buff[1])
		);
	};
	
	u32 BaseStream::readU32BE(const char **err) {
		u8 buff[4];

		if(*err != nullptr)
			return (-1);

		if(read(buff, 4, err) < 0)
			return (-1);
		
		return (
			(((u32)buff[0]) << 24) |
			(((u32)buff[1]) << 16) |
			(((u32)buff[2]) << 8) |
			((u32)buff[3])
		);
	};
	
	u64 BaseStream::readU64BE(const char **err) {
		u8 buff[8];
		
		if(*err != nullptr)
			return (-1);

		if(read(buff, 8, err) < 0)
			return (-1);
		
		return (
			(((u64)buff[0]) << 56) |
			(((u64)buff[1]) << 48) |
			(((u64)buff[2]) << 40) |
			(((u64)buff[3]) << 32) |
			(((u64)buff[4]) << 24) |
			(((u64)buff[5]) << 16) |
			(((u64)buff[6]) << 8) |
			((u64)buff[7])
		);
	};
	
	u16 BaseStream::readU16LE(const char **err) {
		u8 buff[2];

		if(*err != nullptr)
			return (-1);

		if(read(buff, 2, err) < 0)
			return (-1);
		
		return (
			(((u16)buff[1]) << 8) |
			((u16)buff[0])
		);
	};
	
	u32 BaseStream::readU32LE(const char **err) {
		u8 buff[4];

		if(*err != nullptr)
			return (-1);

		if(read(buff, 4, err) < 0)
			return (-1);
		
		return (
			(((u32)buff[3]) << 24) |
			(((u32)buff[2]) << 16) |
			(((u32)buff[1]) << 8) |
			((u32)buff[0])
		);
	};
	
	u64 BaseStream::readU64LE(const char **err) {
		u8 buff[8];
		
		if(*err != nullptr)
			return (-1);

		if(read(buff, 8, err) < 0)
			return (-1);
		
		return (
			(((u64)buff[7]) << 56) |
			(((u64)buff[6]) << 48) |
			(((u64)buff[5]) << 40) |
			(((u64)buff[4]) << 32) |
			(((u64)buff[3]) << 24) |
			(((u64)buff[2]) << 16) |
			(((u64)buff[1]) << 8) |
			((u64)buff[0])
		);
	};
	
	i8 BaseStream::readI8(const char **err) {
		u8 buff[1];

		if(*err != nullptr)
			return (-1);

		if(read(buff, 1, err) < 0)
			return (-1);

		return buff[0];
	};
	
	i16 BaseStream::readI16BE(const char **err) {
		u8 buff[2];

		if(*err != nullptr)
			return (-1);

		if(read(buff, 2, err) < 0)
			return (-1);
		
		return (
			(((i16)buff[0]) << 8) |
			((i16)buff[1])
		);
	};

	i32 BaseStream::readI32BE(const char **err) {
		u8 buff[4];

		if(*err != nullptr)
			return (-1);

		if(read(buff, 4, err) < 0)
			return (-1);
		
		return (
			(((i32)buff[0]) << 24) |
			(((i32)buff[1]) << 16) |
			(((i32)buff[2]) << 8) |
			((i32)buff[3])
		);
	};

	i64 BaseStream::readI64BE(const char **err) {
		u8 buff[8];
		
		if(*err != nullptr)
			return (-1);

		if(read(buff, 8, err) < 0)
			return (-1);
		
		return (
			(((i64)buff[0]) << 56) |
			(((i64)buff[1]) << 48) |
			(((i64)buff[2]) << 40) |
			(((i64)buff[3]) << 32) |
			(((i64)buff[4]) << 24) |
			(((i64)buff[5]) << 16) |
			(((i64)buff[6]) << 8) |
			((i64)buff[7])
		);
	};

	i16 BaseStream::readI16LE(const char **err) {
		u8 buff[2];

		if(*err != nullptr)
			return (-1);

		if(read(buff, 2, err) < 0)
			return (-1);
		
		return (
			(((i16)buff[1]) << 8) |
			((i16)buff[0])
		);
	};

	i32 BaseStream::readI32LE(const char **err) {
		u8 buff[4];

		if(*err != nullptr)
			return (-1);

		if(read(buff, 4, err) < 0)
			return (-1);
		
		return (
			(((i32)buff[3]) << 24) |
			(((i32)buff[2]) << 16) |
			(((i32)buff[1]) << 8) |
			((i32)buff[0])
		);
	};

	i64 BaseStream::readI64LE(const char **err) {
		u8 buff[8];
		
		if(*err != nullptr)
			return (-1);

		if(read(buff, 8, err) < 0)
			return (-1);
		
		return (
			(((i64)buff[7]) << 56) |
			(((i64)buff[6]) << 48) |
			(((i64)buff[5]) << 40) |
			(((i64)buff[4]) << 32) |
			(((i64)buff[3]) << 24) |
			(((i64)buff[2]) << 16) |
			(((i64)buff[1]) << 8) |
			((i64)buff[0])
		);
	};

	f32 BaseStream::readF32(const char **err) {
		if(*err != nullptr)
			return (-1);

		u32 v = readU32BE(err);
		f32 *p = (f32 *)(&v);
		f32 f = (*p);
		
		return f;
	};
	
	f64 BaseStream::readF64(const char **err) {
		if(*err != nullptr)
			return (-1);

		u64 v = readU64BE(err);
		f64 *p = (f64 *)(&v);
		f64 f = (*p);
		
		return f;
	};

	i8 BaseStream::writeU8(u8 value, const char **err) {
		u8 buff[1] = {
			(u8)value
		};

		return write(buff, 1, err);
	};
	
	i8 BaseStream::writeU16BE(u16 value, const char **err) {
		u8 buff[2] = {
			(u8)((value >> 8) & 0xff),
			(u8)(value & 0xff)
		};
		
		return write(buff, 2, err);
	};
	
	i8 BaseStream::writeU32BE(u32 value, const char **err) {
		u8 buff[4] = {
			(u8)((value >> 24) & 0xff),
			(u8)((value >> 16) & 0xff),
			(u8)((value >> 8) & 0xff),
			(u8)(value & 0xff)
		};
		
		return write(buff, 4, err);
	};
	
	i8 BaseStream::writeU64BE(u64 value, const char **err) {
		u8 buff[8] = {
			(u8)((value >> 56) & 0xff),
			(u8)((value >> 48) & 0xff),
			(u8)((value >> 40) & 0xff),
			(u8)((value >> 32) & 0xff),
			(u8)((value >> 24) & 0xff),
			(u8)((value >> 16) & 0xff),
			(u8)((value >> 8) & 0xff),
			(u8)(value & 0xff)
		};
		
		return write(buff, 8, err);
	};
	
	i8 BaseStream::writeU16LE(u16 value, const char **err) {
		u8 buff[2] = {
			(u8)(value & 0xff),
			(u8)((value >> 8) & 0xff)
		};
		
		return write(buff, 2, err);
	};
	
	i8 BaseStream::writeU32LE(u32 value, const char **err) {
		u8 buff[4] = {
			(u8)(value & 0xff),
			(u8)((value >> 8) & 0xff),
			(u8)((value >> 16) & 0xff),
			(u8)((value >> 24) & 0xff)
		};
		
		return write(buff, 4, err);
	};
	
	i8 BaseStream::writeU64LE(u64 value, const char **err) {
		u8 buff[8] = {
			(u8)(value & 0xff),
			(u8)((value >> 8) & 0xff),
			(u8)((value >> 16) & 0xff),
			(u8)((value >> 24) & 0xff),
			(u8)((value >> 32) & 0xff),
			(u8)((value >> 40) & 0xff),
			(u8)((value >> 48) & 0xff),
			(u8)((value >> 56) & 0xff)
		};
		
		return write(buff, 8, err);
	};
	
	// [TODO] Loss-less I8->U8.
	i8 BaseStream::writeI8(i8 value, const char **err) {
		return writeU8(value, err);
	};

	i8 BaseStream::writeI16LE(i16 value, const char **err) {
		return writeU16LE(value, err);
	};

	i8 BaseStream::writeI32LE(i32 value, const char **err) {
		return writeU32LE(value, err);
	};

	i8 BaseStream::writeI64LE(i64 value, const char **err) {
		return writeU64LE(value, err);
	};
	
	i8 BaseStream::writeF32(float value, const char **err) {
		u32 *raw_value = (u32 *)(&value);
		return writeU32BE(*raw_value, err);
	};
	
	i8 BaseStream::writeF64(double value, const char **err) {
		u64 *raw_value = (u64 *)(&value);
		return writeU64BE(*raw_value, err);
	};
};
