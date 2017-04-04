varying vec3 v_Position;            // in: vertices en coordenadas de vista
varying vec3 v_Normal;              // in: normales en "
varying vec2 v_TextureCoords;       // in: coordenadas de textura

struct TLight {
    vec4 position;
    vec3 ambient;   // Intensidad
    vec3 diffuse;   // "
    vec3 specular;  // "
};

struct TMaterial {
    bool        hasTexture;
    sampler2D   diffuse;
    sampler2D   specular;
    float       shininess;  // Factor de brillo del material
};

uniform TLight      u_Light;
uniform TMaterial   u_Material;

vec3 phong()
{
    vec3 n = normalize(v_Normal);
    vec3 s = normalize(vec3(u_Light.position) - v_Position);
    vec3 v = normalize(vec3(-v_Position));
    vec3 r = reflect(-s, n);

    vec3 texSpec;
    vec3 texDiff;
    if (u_Material.hasTexture)
    {
        texDiff = vec3(texture2D(u_Material.diffuse, v_TextureCoords));
        texSpec = vec3(texture2D(u_Material.specular, v_TextureCoords));
    }
    else
    {
        texDiff = texSpec = vec3(0.5,0.5,0.5);  // Color gris si no tiene textura
    }

    // Componente ambiental
    vec3 ambient =
        u_Light.ambient
        * texDiff;

    // Componente difusa
    vec3 diffuse =
        u_Light.diffuse
        * max(dot(s,n), 0.0)     // max para que no sea negativo. Se multiplica por el angulo que forman s y n
        * texDiff;

    // Componente especular
    vec3 specular =
        u_Light.specular
        * pow(max(dot(r,v), 0.0), u_Material.shininess)
        * texSpec;


    return ambient + diffuse + specular;
}

void main()
{
    gl_FragColor = vec4(phong(), 1.0);
}
