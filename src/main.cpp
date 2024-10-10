#include <format>

#include "object/object_factory.h"
#include "renderer/renderer.h"
#include "utils/view_ptr.h"

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << std::format("Usage: {} <width> <height>\n", argv[0]);
        return 1;
    }

    yart::renderer renderer{ std::atoi(argv[1]), std::atoi(argv[2]) };
    yart::scene scene;

    auto obj = scene.add_object(
        yart::factory::make_sphere(glm::vec3{ 0.f, 0.f, -5.f }, 3.f));

    obj->material.albedo = glm::vec3{ 1.f, 0.f, 0.f };

    scene.camera_get().look_at({}, { 0.f, 1.f, 0.f }, { 0.f, 0.f, -1.f });

    scene.light_source_set({ 0.f, 17.f, -6.f });

    renderer.render_scene(scene);
}
