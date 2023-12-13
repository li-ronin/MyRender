#version 330 core			

in vec2 TexCoord;      // uv位置坐标
in vec3 FragPos;       // 顶点在世界空间的坐标
in vec3 Normal;        // 顶点在世界空间的法向量

out vec4 FragColor;			

uniform sampler2D ourTexture;
uniform sampler2D ourFace;
//uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;
struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float reflectivity;
};
uniform Material ObjMaterial;

void main(){

	vec3 normal = normalize(Normal);
	vec3 light = lightPos - FragPos;
	vec3 lightDir = normalize(light);
	// 距离因素对光强的影响，距离越大强度越低
	float Energy = 180 / (pow(light.x, 2)+pow(light.y, 2)+pow(light.z, 2));
	// 角度因素对光强的影响：光线与法向量的夹角关系，超过90度认定为光线被遮挡
	float diff = max(dot(normal, lightDir), 0);  
	// 漫反射 = 光的颜色 × 距离因素对光强的影响 × 角度因素对光强的影响
	vec3 diffuse = ObjMaterial.diffuse * lightColor * Energy * diff;

	vec3 cameraDir = normalize(cameraPos - FragPos);
	// 镜面反射
	vec3 reflectDir = reflect(-lightDir, normal); // 光线反射方向，入射光线：-lightDir
			 // Blinn-Phong模型的镜面  使用半程向量
			 //观察方向和镜面反射方向足够接近的时候，其实也就是半程向量与法线方向足够接近的时候,我们衡量能不能看到高光，只要看n和h是不是接近
	vec3 half_vector = normalize(cameraDir + lightDir);
	float spec = pow(max(dot(normal, half_vector), 0.0f), ObjMaterial.reflectivity);
	// Phong模型的镜面
	//float spec = pow(max(dot(reflectDir, cameraDir), 0), 100);
	vec3 specular =  ObjMaterial.specular * lightColor * Energy * spec ;

	vec3 ambient = ObjMaterial.ambient * ambientColor;
	// 物体的皮肤
	vec4 objTexture = mix(texture(ourTexture,TexCoord), texture(ourFace,TexCoord), texture(ourFace,TexCoord).a*0.2);
	//vec4 objColor= vec4(1.0f, 0.5f, 0.31f,1.0f);
	FragColor = vec4(diffuse+specular+ambient, 1.0) * objTexture;
}





