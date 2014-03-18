#ifndef RASPBERRY_GLES_H_
#define RASPBERRY_GLES_H_

#include "config.h"

/************************************************************************/
/* Standard headers                                                     */
/************************************************************************/
#include <queue>
#include <string>
#include <memory>
#include <map>

/************************************************************************/
/* JNI                                                                  */
/************************************************************************/
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

/************************************************************************/
/* GLM                                                                  */
/************************************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

/************************************************************************/
/* GLES                                                                 */
/************************************************************************/
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

/************************************************************************/
/* Common headers                                                       */
/************************************************************************/
#include "singleton.h"
#include "console.h"
#include "buffer.h"

#endif /* RASPBERRY_GLES_H_ */
