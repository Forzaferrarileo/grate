/*
 * Copyright (c) 2012, 2013 Erik Faye-Lund
 * Copyright (c) 2013 Avionic Design GmbH
 * Copyright (c) 2013 Thierry Reding
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef GRATE_LIBCGC_H
#define GRATE_LIBCGC_H 1

#include <stdint.h>
#include <stdlib.h>

enum cgc_shader_type {
	CGC_SHADER_VERTEX = 1,
	CGC_SHADER_FRAGMENT,
};

struct cgc_header_symbol {
	uint32_t unknown00;
	uint32_t unknown01;
	/*
	 * type? seen:
	 * - 0x1005 for attributes and output variables
	 * - 0x1006 for uniforms
	 * - 0x1007 for constants
	 */
	uint32_t unknown02;
	uint32_t unknown03;
	uint32_t name_offset;
	uint32_t values_offset;
	uint32_t unknown06;
	uint32_t alt_offset;
	uint32_t unknown08;
	uint32_t unknown09;
	uint32_t unknown10;
	uint32_t unknown11;
};

struct cgc_header {
	uint32_t type;
	uint32_t unknown00;
	uint32_t size;
	uint32_t num_symbols;
	uint32_t bar_size;
	uint32_t bar_offset;
	uint32_t binary_size;
	uint32_t binary_offset;
	uint32_t unknown01;
	uint32_t unknown02;
	uint32_t unknown03;
	uint32_t unknown04;

	struct cgc_header_symbol symbols[0];
};

struct cgc_vertex_shader {
	uint32_t unknown00;
	uint32_t unknown04;
	uint32_t unknown08;
	uint32_t unknown0c;
	uint32_t unknown10;
	uint32_t unknown14;
	uint32_t unknown18;
	uint32_t unknown1c;
	uint32_t unknown20;
	uint32_t unknown24;
	uint32_t unknown28;
	uint32_t unknown2c;
	uint32_t unknown30;
	uint32_t unknown34;
	uint32_t unknown38;
	uint32_t unknown3c;
	uint32_t unknown40;
	uint32_t unknown44;
	uint32_t unknown48;
	uint32_t unknown4c;
	uint32_t unknown50;
	uint32_t unknown54;
	uint32_t unknown58;
	uint32_t unknown5c;
	uint32_t unknown60;
	uint32_t unknown64;
	uint32_t unknown68;
	uint32_t unknown6c;
	uint32_t unknown70;
	uint32_t unknown74;
	uint32_t unknown78;
	uint32_t unknown7c;
	uint32_t unknown80;
	uint32_t unknown84;
	uint32_t unknown88;
	uint32_t unknown8c;
	uint32_t unknown90;
	uint32_t unknown94;
	uint32_t unknown98;
	uint32_t unknown9c;
	uint32_t unknowna0;
	uint32_t unknowna4;
	uint32_t unknowna8;
	uint32_t unknownac;
	uint32_t unknownb0;
	uint32_t unknownb4;
	uint32_t unknownb8;
	uint32_t unknownbc;
	uint32_t unknownc0;
	uint32_t unknownc4;
	uint32_t unknownc8;
	uint32_t unknowncc;
	uint32_t unknownd0;
	uint32_t unknownd4;
	uint32_t unknownd8;
	uint32_t unknowndc;
	uint32_t unknowne0;
	uint32_t unknowne4;
	uint32_t unknowne8;
	uint32_t unknownec;
	uint32_t unknownf0;
	uint32_t unknownf4;
	uint32_t unknownf8;
	uint32_t unknownfc;
};

struct cgc_fragment_shader {
	char signature[8];
	uint32_t unknown0;
	uint32_t unknown1;
	uint32_t words[0];
};

enum glsl_kind {
	GLSL_KIND_UNKNOWN,
	GLSL_KIND_ATTRIBUTE,
	GLSL_KIND_UNIFORM,
	GLSL_KIND_CONSTANT,
};

enum glsl_type {
	GLSL_TYPE_UNKNOWN,
	GLSL_TYPE_FLOAT,
	GLSL_TYPE_VEC2,
	GLSL_TYPE_VEC3,
	GLSL_TYPE_VEC4,
	GLSL_TYPE_MAT2,
	GLSL_TYPE_MAT3,
	GLSL_TYPE_MAT4,
	GLSL_TYPE_SAMPLER2D,
	GLSL_TYPE_SAMPLER3D,
	GLSL_TYPE_INT,
	GLSL_TYPE_IVEC2,
	GLSL_TYPE_IVEC3,
	GLSL_TYPE_IVEC4,
	GLSL_TYPE_BOOL,
	GLSL_TYPE_BVEC2,
	GLSL_TYPE_BVEC3,
	GLSL_TYPE_BVEC4,
};

struct cgc_symbol {
	int location;
	enum glsl_kind kind;
	enum glsl_type type;
	const char *name;

	uint32_t vector[4];
};

struct cgc_shader {
	enum cgc_shader_type type;

	void *binary;
	size_t size;

	void *stream;
	size_t length;

	struct cgc_symbol *symbols;
	unsigned int num_symbols;
};

struct cgc_shader *cgc_compile(enum cgc_shader_type type, const char *code,
			       size_t size);
void cgc_shader_free(struct cgc_shader *shader);
void cgc_shader_dump(struct cgc_shader *shader, FILE *fp);

struct cgc_symbol *cgc_shader_get_symbol_by_kind(struct cgc_shader *shader,
						 enum glsl_kind kind,
						 unsigned int index);

static inline struct cgc_symbol *
cgc_shader_get_attribute(struct cgc_shader *shader, unsigned int index)
{
	return cgc_shader_get_symbol_by_kind(shader, GLSL_KIND_ATTRIBUTE,
					     index);
}

static inline struct cgc_symbol *
cgc_shader_get_uniform(struct cgc_shader *shader, unsigned int index)
{
	return cgc_shader_get_symbol_by_kind(shader, GLSL_KIND_UNIFORM,
					     index);
}

static inline struct cgc_symbol *
cgc_shader_get_constant(struct cgc_shader *shader, unsigned int index)
{
	return cgc_shader_get_symbol_by_kind(shader, GLSL_KIND_CONSTANT,
					     index);
}

struct cgc_symbol *
cgc_shader_find_symbol_by_kind(struct cgc_shader *shader,
			       enum glsl_kind kind, const char *name,
			       unsigned int *index);

static inline struct cgc_symbol *
cgc_shader_find_attribute(struct cgc_shader *shader, const char *name,
			  unsigned int *index)
{
	return cgc_shader_find_symbol_by_kind(shader, GLSL_KIND_ATTRIBUTE,
					      name, index);
}

static inline struct cgc_symbol *
cgc_shader_find_uniform(struct cgc_shader *shader, const char *name,
			unsigned int *index)
{
	return cgc_shader_find_symbol_by_kind(shader, GLSL_KIND_UNIFORM,
					      name, index);
}

static inline struct cgc_symbol *
cgc_shader_find_constant(struct cgc_shader *shader, const char *name,
			 unsigned int *index)
{
	return cgc_shader_find_symbol_by_kind(shader, GLSL_KIND_CONSTANT,
					      name, index);
}

enum vs_reg_type {
	VS_REG_TYPE_INVALID = 0,
	VS_REG_TYPE_TEMP = 1,
	VS_REG_TYPE_ATTR = 2,
	VS_REG_TYPE_CONST = 3,
	VS_REG_TYPE_VAR = 4
};

struct vs_dst {
	int reg;
	enum vs_reg_type type;
	unsigned int mask;
	int sat;
};

struct vs_src {
	int reg;
	enum vs_reg_type type;
	unsigned int swz;
	int neg, abs;
};

enum vs_op {
	VS_OP_MOV = 0x1,
	VS_OP_DP4 = 0x7
};
void vs_emit_alu(uint32_t stream[4], enum vs_op op, int cfetch, int afetch, const struct vs_dst *dst, const struct vs_src src[3], int last);

#endif
