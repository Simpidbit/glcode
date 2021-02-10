#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct SPShader {
    unsigned int vshader;
    unsigned int fshader;
    unsigned int program;

    char *vsur;
    char *fsur;
};

void spinit_shader(struct SPShader *shader, const char *vfilename, const char *ffilename);
void spuse_shader(struct SPShader *shader);

void set_uniform_1i(struct SPShader *shader, const char *name, int value);
void set_uniform_1f(struct SPShader *shader, const char *name, float value);
void set_uniform_2i(struct SPShader *shader, const char *name,
                    int value1, int value2);
void set_uniform_2f(struct SPShader *shader, const char *name, float value1, float value2);
void set_uniform_3i(struct SPShader *shader, const char *name,
                    int value1, int value2, int value3);
void set_uniform_3f(struct SPShader *shader, const char *name,
                    float value1, float value2, float value3);
void set_uniform_4i(struct SPShader *shader, const char *name,
                    int value1, int value2, int value3, int value4);
void set_uniform_4f(struct SPShader *shader, const char *name,
                    float value1, float value2, float value3, float value4);
void set_uniform_4fm(struct SPShader *shader, const char *name, glm::mat4 trans);
