varying vec3 v_Position;            // in: vertices en coordenadas de vista
varying vec3 v_Normal;              // in: normales en "
varying vec2 v_TextureCoords;       // in: coordenadas de textura

varying vec4 v_PositionLightSpace;

struct TLight {
    vec4 position;
    vec3 ambient;   // Intensidad
    vec3 diffuse;   // "
    vec3 specular;  // "
};

/*struct TMaterial {
    bool        hasTexture;
    sampler2D   diffuse;
    sampler2D   specular;
    float       shininess;  // Factor de brillo del material
};*/

//uniform TMaterial   u_Material;
uniform TLight      u_Light;
uniform bool        u_MaterialHasTexture;
uniform sampler2D   u_MaterialDiffuse;
uniform sampler2D   u_MaterialSpecular;
uniform float       u_MaterialShininess;
uniform bool        u_hasNormalTexture;
uniform sampler2D   u_normalTexture;
uniform sampler2D   u_shadowTexture;


float calculateShadow(vec4 positionLightSpace, vec3 normal, vec3 lightDir)
{
    vec3 projCoords = positionLightSpace.xyz / positionLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(u_shadowTexture, projCoords.xy).r;
    float currentDepth = projCoords.z;
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    /*float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(u_shadowTexture, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(u_shadowTexture, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;


    if(projCoords.z > 1.0)
        shadow = 0.0;*/

    return shadow;
}

vec3 phong()
{
    vec3 normal;
    if (u_hasNormalTexture)
        normal = vec3(normalize(texture2D(u_normalTexture, v_TextureCoords)));
    else
        normal = vec3(normalize(v_Normal));

    vec3 lightDir = normalize(vec3(u_Light.position) - v_Position);
    vec3 viewDir  = normalize(vec3(-v_Position));
    vec3 r        = reflect(-lightDir, normal);

    vec3 texSpec;
    vec3 texDiff;
    if (u_MaterialHasTexture)
    {
        texDiff = vec3(texture2D(u_MaterialDiffuse, v_TextureCoords));
        texSpec = vec3(texture2D(u_MaterialSpecular, v_TextureCoords));
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
        * max(dot(lightDir, normal), 0.0)     // max para que no sea negativo. Se multiplica por el angulo que forman s y n
        * texDiff;

    // Componente especular
    vec3 specular =
        u_Light.specular
        * pow(max(dot(r, viewDir), 0.0), u_MaterialShininess)
        * texSpec;

    float shadow = calculateShadow(v_PositionLightSpace, normal, lightDir);
    return (ambient + (1.0 - shadow) * (diffuse + specular));
    //return ambient + diffuse + specular;
}

void main()
{
    gl_FragColor = vec4(phong(), 1.0);
}
