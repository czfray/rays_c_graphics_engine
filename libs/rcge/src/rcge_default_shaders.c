#include <rcge/rcge_shader.h>
#include <rcge/rcge_default_shaders.h>

rcge_shader rcge_default_unlit_shader_create(void)
{
    const char *vert_source = "#version 150 core\n"
                              "in vec3 position;\n"
                              "in vec2 texcoord;\n"
                              "out vec2 _texcoord;\n"
                              "uniform mat4 model;\n"
                              "uniform mat4 view;\n"
                              "uniform mat4 proj;\n"
                              "void main()\n"
                              "{\n"
                              "    gl_Position = proj * view * model * vec4(position, 1.0);\n"
                              "    _texcoord = texcoord;\n"
                              "}\n";

    const char *frag_source = "#version 150 core\n"
                              "in vec2 _texcoord;\n"
                              "out vec4 outColor;\n"
                              "uniform sampler2D tex;\n"
                              "uniform vec4 color;\n"
                              "void main()\n"
                              "{\n"
                              "    outColor = texture(tex, _texcoord) * color;\n"
                              "}\n";
    
    rcge_shader_comp vertex_comp = rcge_shader_comp_create(vert_source, SHADER_VERT);
    rcge_shader_comp fragment_comp = rcge_shader_comp_create(frag_source, SHADER_FRAG);

    rcge_shader shader = rcge_shader_create(2, 5);
    rcge_shader_attach(shader, vertex_comp);
    rcge_shader_attach(shader, fragment_comp);
    rcge_shader_color_out_location(shader, RCGE_DEF_UNLIT_SHADER_COLOROUT_LOC, "outColor");
    rcge_shader_compile(shader);

    rcge_shader_attrib_set(shader, RCGE_DEF_UNLIT_SHADER_POSITION_ATTRIB, "position", 3, DATATYPE_FLOAT, false);
    rcge_shader_attrib_set(shader, RCGE_DEF_UNLIT_SHADER_TEXCOORD_ATTRIB, "texcoord", 2, DATATYPE_FLOAT, false);

    rcge_shader_uniform_loc_set(shader, RCGE_DEF_UNLIT_SHADER_MODEL_UNF, "model");
    rcge_shader_uniform_loc_set(shader, RCGE_DEF_UNLIT_SHADER_VIEW_UNF, "view");
    rcge_shader_uniform_loc_set(shader, RCGE_DEF_UNLIT_SHADER_PROJ_UNF, "proj");
    rcge_shader_uniform_loc_set(shader, RCGE_DEF_UNLIT_SHADER_COLOR_UNF, "color");
    rcge_shader_uniform_loc_set(shader, RCGE_DEF_UNLIT_SHADER_TEXTURE_UNF, "tex");

    rcge_shader_uniform_purpose_set(shader, RCGE_DEF_UNLIT_SHADER_MODEL_UNF, SHADER_UNIFORM_MODEL);
    rcge_shader_uniform_purpose_set(shader, RCGE_DEF_UNLIT_SHADER_VIEW_UNF, SHADER_UNIFORM_VIEW);
    rcge_shader_uniform_purpose_set(shader, RCGE_DEF_UNLIT_SHADER_PROJ_UNF, SHADER_UNIFORM_PROJECTION);
    rcge_shader_uniform_purpose_set(shader, RCGE_DEF_UNLIT_SHADER_COLOR_UNF, SHADER_UNIFORM_COLOR);
    
    rcge_shader_comp_delete(vertex_comp);
    rcge_shader_comp_delete(fragment_comp);
    return shader;
}
