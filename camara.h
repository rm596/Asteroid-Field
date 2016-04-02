#include <math.h>

#include "Scenenode.h"

#include "GL/glew.h"
#include "vec3.h"
#include "mat4.h"

#define ORTHOGONAL 0
#define PERSPECTIVE 1

#define DEGREESTORADIANS 0.0174532925

class camara : public scenenode
{
public:
	camara();
};