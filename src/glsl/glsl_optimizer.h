#pragma once
#ifndef GLSL_OPTIMIZER_H
#define GLSL_OPTIMIZER_H

#if defined(GSO_BUILD_DLL)
#define GLOAPI	__declspec(dllexport)
#elif defined(GSO_LOAD_DLL)
#define GLOAPI	__declspec(dllimport)
#else
#define GLOAPI	
#endif

/*
 Main GLSL optimizer interface.
 See ../../README.md for more instructions.

 General usage:

 ctx = glslopt_initialize();
 for (lots of shaders) {
   shader = glslopt_optimize (ctx, shaderType, shaderSource, options);
   if (glslopt_get_status (shader)) {
     newSource = glslopt_get_output (shader);
   } else {
     errorLog = glslopt_get_log (shader);
   }
   glslopt_shader_delete (shader);
 }
 glslopt_cleanup (ctx);
*/

struct glslopt_shader;
struct glslopt_ctx;

enum glslopt_shader_type {
	kGlslOptShaderVertex = 0,
	kGlslOptShaderFragment,
};

// Options flags for glsl_optimize
enum glslopt_options {
	kGlslOptionNone = 0,
	kGlslOptionSkipPreprocessor = (1<<0), // Skip preprocessing shader source. Saves some time if you know you don't need it.
	kGlslOptionNotFullShader = (1<<1), // Passed shader is not the full shader source. This makes some optimizations weaker.
};

GLOAPI glslopt_ctx* glslopt_initialize (bool openglES);
GLOAPI void glslopt_cleanup (glslopt_ctx* ctx);

GLOAPI glslopt_shader* glslopt_optimize (glslopt_ctx* ctx, glslopt_shader_type type, const char* shaderSource, unsigned options);
GLOAPI bool glslopt_get_status (glslopt_shader* shader);
GLOAPI const char* glslopt_get_output (glslopt_shader* shader);
GLOAPI const char* glslopt_get_raw_output (glslopt_shader* shader);
GLOAPI const char* glslopt_get_log (glslopt_shader* shader);
GLOAPI void glslopt_shader_delete (glslopt_shader* shader);

#endif /* GLSL_OPTIMIZER_H */
