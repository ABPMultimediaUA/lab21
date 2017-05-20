attribute vec4 a_VertexPosition;	// in: Posición de cada vértice

uniform mat4 u_MVP;                 // in: model*view*lightProyection

void main()
{
	// posición final del vértice
	gl_Position = u_MVP * a_VertexPosition;
}
