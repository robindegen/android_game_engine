#ifndef config_h__
#define config_h__

//Show console messages defined with the DEBUGPRINT macro.
#define SHOW_DEBUG_MESSAGES

#define COLOR_DEFAULT								1.0f, 1.0f, 1.0f, 1.0f
#define COLOR_BACKGROUND							0.046875f, 0.2109375f, 0.421875f, 1.0f

#define FULLSCREEN_VIRTUAL_RESOLUTION_WIDTH			1280.0f
#define FULLSCREEN_VIRTUAL_RESOLUTION_HEIGHT		720.0f

#define CONSOLE_LINE_BUFFSIZE						1024

#define SHADER_ATTRIB_VERTEX_ID						0
#define SHADER_ATTRIB_VERTEX_NAME					"age_position"

#define SHADER_ATTRIB_TEXCOORD_ID					1
#define SHADER_ATTRIB_TEXCOORD_NAME					"age_texcoord"

#define SHADER_PROJECTION_MATRIX_NAME				"age_projection_matrix"
#define SHADER_MODEL_MATRIX_NAME					"age_model_matrix"
#define SHADER_VIEW_MATRIX_NAME						"age_view_matrix"

#define SHADER_TEXTURE0_NAME						"age_texture"
#define SHADER_COLOR_NAME							"age_color"

#endif // config_h__
