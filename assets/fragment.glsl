#version 330 core
out vec4 FragColor;

in vec4 tcolor;
in vec4 bcolor;

void main(){
    // Based on height
    float intensity = gl_FragCoord.y / 800.0;
    vec3 color = mix(tcolor.rgb, bcolor.rgb, intensity);
    FragColor = vec4(color.rgb, 1.0);
}
