attribute vec4 a_VertexPosition;	// in: Posici�n de cada v�rtice

uniform mat4 u_MVP;                 // in: model*view*lightProyection

void main()
{
	// posici�n final del v�rtice
	gl_Position = u_MVP * a_VertexPosition;
}
