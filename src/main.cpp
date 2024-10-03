#include <iostream>

#include "renderer/renderer.h"

int main()
{
    yart::renderer renderer{ 1600, 900 };
    yart::scene scene;

    renderer.render_scene(scene);
}
