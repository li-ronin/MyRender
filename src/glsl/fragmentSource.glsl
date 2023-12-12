#version 330 core			

in vec2 TexCoord;

out vec4 FragColor;			

uniform sampler2D ourTexture;
uniform sampler2D ourFace;

void main(){				
	FragColor = mix(texture(ourTexture,TexCoord), texture(ourFace,TexCoord), texture(ourFace,TexCoord).a*0.2);
}





