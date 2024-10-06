#include "object/object_factory.h"
#include "renderer/renderer.h"

int main()
{
    yart::renderer renderer{ 1600, 900 };
    yart::scene scene;

    scene.add_object(
        yart::factory::make_sphere(glm::vec3{ 0.f, 0.f, -5.f }, 3.f));

    scene.camera_get().look_at({}, { 0.f, 1.f, 0.f }, { 0.f, 0.f, -1.f });

    renderer.render_scene(scene);
}
