/*# version 330
in vec4 lightPosition;
in vec3 lightIntensity;
in vec4 lightAmbient;
in vec4 lightDiffuse;
in vec4 vPosition;
in vec3 vNormal;

/*struct LightInfo {
    vec4 position;
    vec3 intensity;
};
uniform LightInfo Light;
Light.position = lightPosition;
Light.intensity = intensity;
//uniform vec3 Kd;
//uniform vec3 Ka;*/
// Diffuse reflectivity
// Ambient reflectivity
/*const int levels = 3;
const float scaleFactor = 1.0 / levels;
layout( location = 0 ) out vec4 FragColor;
vec3 toonShade( )
{
    //float Kd = max ( NdotL , 0.0) ;
    vec3 s = normalize( lightPosition.xyz - vPosition.xyz );
    float cosine = max( 0.0, dot( s, vNormal ) );
    vec3 diffuse = lightDiffuse * floor( cosine * levels ) * scaleFactor;
    return lightIntensity * (lightAmbient + diffuse);
}
void main() {
    FragColor = vec4(toonShade(), 1.0);
}*/
# version 330
in vec3 fN ;
in vec3 fE ;
in vec3 fL ;
uniform vec4 ambientProduct ;
uniform vec4 diffuseProduct ;
uniform vec4 specularProduct ;
uniform float shininess ;
const int levels = 5;
const float scaleFactor = 1.0 / levels;
out vec4 frag_color ;
void main ()
{
    vec3 N = normalize ( fN );
    vec3 E = normalize ( fE );
    vec3 L = normalize ( fL );
    vec3 R = normalize (2.0 * dot (L , N) * N - L);
    float NdotL = dot (N , L);
    float Kd = max ( NdotL , 0.0) ;
    float Ks = ( NdotL < 0.0) ? 0.0 : pow ( max ( dot (R , E ) , 0.0) ,
    shininess ) ;
    vec4 diffuse = diffuseProduct * floor( Kd * levels ) * scaleFactor; ;
    vec4 specular = Ks * specularProduct ;
    vec4 ambient = ambientProduct ;
    frag_color = ambient + diffuse;// + specular ;
    frag_color . a = 1.0;
}

