#pragma once

struct SPShader {
    unsigned int vshader;
    unsigned int fshader;
    unsigned int program;

    char *vsur;
    char *fsur;
};

void spinit_shader(struct SPShader *shader, const char *vfilename, const char *ffilename);
void spuse_shader(struct SPShader *shader);
