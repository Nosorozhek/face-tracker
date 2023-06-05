#include "app.h"

int main(int argc, char* argv[])
{
    App app;
    while (true)
    {
        app.RecognizeLandmarks();
        app.GenerateModel();
        app.RenderModel();
    }
}
