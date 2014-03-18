#ifndef vertex_h__
#define vertex_h__

//The standard vertex structure used to render everything.
struct Vertex
{
	float position[2];
	float uv[2];
} __attribute__((packed));

#endif // vertex_h__

