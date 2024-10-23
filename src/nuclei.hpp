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
#include <cstdint>
#include <cstdlib>

namespace roBrot {
	typedef uint8_t u8;
	typedef uint16_t u16;
	typedef uint32_t u32;
	typedef uint64_t u64;
	
	typedef int8_t i8;
	typedef int16_t i16;
	typedef int32_t i32;
	typedef int64_t i64;
	
	typedef float f32;
	typedef double f64;

	static_assert((sizeof(u8) == 1) && (sizeof(i8) == 1), "I8 isn't an 8-bit integer.");
	static_assert((sizeof(u16) == 2) && (sizeof(i16) == 2), "I16 isn't a 16-bit integer.");
	static_assert((sizeof(u32) == 4) && (sizeof(i32) == 4), "I32 isn't a 32-bit integer.");
	static_assert((sizeof(u64) == 8) && (sizeof(i64) == 8), "I64 isn't a 64-bit integer.");

	static_assert(sizeof(f32) == 4, "F32 isn't a 32-bit FP.");
	static_assert(sizeof(f64) == 8, "F64 isn't a 64-bit FP.");

	void __assert_me__(const char *file, int line, const char *comment);

	#ifdef RO_BROT_DEBUG
		#define assert_me(x,y) if((x) == false) __assert_me__(__FILE__, __LINE__, y);
	#else
		#define assert_me(x,y) (void)0;
	#endif

	typedef struct { const char **error; } Error;
	
	template<typename Type>
	class ErrorOr {
		private:
			Type val;
		
		public:
			const char **error = nullptr;
			
			ErrorOr(void) {
				error = nullptr;
			};
			
			ErrorOr(Error error_struct) {
				error = error_struct.error;
			};
			
			ErrorOr(Type value_pointer) {
				error = nullptr;
				val = value_pointer;
			};
			
			Type value(void) { return val; };
	};
	
	template<typename Type>
	class ErrorOr<Type*> {
		private:
			Type *val = nullptr;
		
		public:
			const char **error = nullptr;
			
			ErrorOr(void) {
				error = nullptr;
			};
			
			ErrorOr(Error error_struct) {
				error = error_struct.error;
			};
			
			ErrorOr(Type *value_pointer) {
				error = nullptr;
				val = value_pointer;
			};
			
			Type *value(void) { return val; };
	};
	
	template<typename Type>
	class ErrorOr<Type&> {
		public:
			const char **error = nullptr;
			Type* value_pointer = nullptr;
			
			ErrorOr(void) {
				error = nullptr;
			};
			
			ErrorOr(Error error_struct) {
				error = error_struct.error;
			};
			
			ErrorOr(Type *val_ptr) {
				error = nullptr;
				value_pointer = val_ptr;
			};
			
			Type& value(void) { return (*value_pointer); };
	};
	
	template<>
	class ErrorOr<void> {
		public:
			const char **error = nullptr;
			
			ErrorOr(Error error_struct) { error = error_struct.error; };
	};

	template<typename T>
	T *valloc(u64 count, const char **err) {
		if(*err != nullptr)
			return nullptr;

		void *p = std::calloc(count, sizeof(T));
		if(p == nullptr) {
			*err = "Couldn't allocate enough memory";
			return nullptr;
		}

		return (T *)p;
	};
	
	template<typename T>
	T *valloc(const char **err) {
		return valloc<T>(1, err);
	};

	void vfree(void *p);
};
