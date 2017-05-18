attribute vec4 a_VertexPosition;	// in: Posición de cada vértice
attribute vec3 a_VertexNormal;	    // in: Normal de cada vértice
attribute vec2 a_TextureCoords;     // in: coordenadas uv de las texturas

varying vec3 v_Position;            // out: vertices en coordenadas de vista
varying vec3 v_Normal;              // out: normales en "
varying vec2 v_TextureCoords;       // out: coordenadas de textura

varying vec4 v_PositionLightSpace;  // out: vertices en coordenadas de la luz


uniform mat4 u_MVMatrix;	        // in: Matriz ModelView
uniform mat3 u_NormalMatrix;        // in: Matriz de normales transformadas
uniform mat4 u_MVP;                 // in: model*view*proyection

uniform mat4 u_lightSpaceMatrix;

void main()
{
	// Pasamos al fragment
	v_Position = vec3(u_MVMatrix * a_VertexPosition);
	v_Normal = normalize(u_NormalMatrix * a_VertexNormal);
	v_TextureCoords = a_TextureCoords;

	v_PositionLightSpace = u_lightSpaceMatrix * vec4(v_Position, 1.0);

	// posición final del vértice
	gl_Position = u_MVP * a_VertexPosition;
}
