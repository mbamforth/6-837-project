#if !defined(SETDESIGN_H)
#define SETDESIGN_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <vecmath.h>
#include "extra.h"

#include "MatrixStack.h"

class SetDesign
{
public:
    void load(int argc, char* argv[]);
    void draw(Matrix4f cameraMatrix);
    void drawSet();

private:

    MatrixStack m_matrixStack;
    int argc;
    char** argv;
};

#endif // SETDESIGN_H
