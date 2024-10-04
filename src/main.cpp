#include <iostream>

#include "object/sphere.h"
#include "renderer/renderer.h"

int main()
{
    yart::renderer renderer{ 1600, 900 };
    yart::scene scene;

    // TODO: probably use an object factory for easier addition to the scene
    auto sphere = new yart::sphere;
    sphere->radius = 3.f;
    sphere->position = { 0.f, 0.f, -5.f };
    scene.add_object(sphere);

    scene.camera_get().look_at({}, { 0.f, 1.f, 0.f }, sphere->position);

    renderer.render_scene(scene);
}
