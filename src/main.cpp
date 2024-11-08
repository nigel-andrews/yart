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

    // TODO: Scene manager for dynamic drawing (preferably with some UI)
    renderer renderer{ std::atoi(argv[1]), std::atoi(argv[2]) };
    scene scene;

    const auto obj = scene.add_object(
        factory::make_sphere(glm::vec3{ 0.f, 0.f, -1.f }, 0.5f));

    scene.add_object(
        factory::make_sphere(glm::vec3{ -.25f, 0.25f, -0.5f }, 0.1f));

    const auto ground = scene.add_object(
        factory::make_sphere(glm::vec3{ 0.f, -100.5f, -1.f }, 100.f));

    ground->material.albedo = glm::vec3{ 0.f, 1.f, 0.f };

    obj->material.albedo = glm::vec3{ 1.f, 0.f, 0.f };

    scene.camera_get().look_at({}, { 0.f, 1.f, 0.f }, { 0.f, 0.f, -1.f });

    scene.light_source_set({ -1.f, 1.f, 0.f });

    renderer.render_scene(scene);
    renderer.display(render_functions::ppm3_renderer{});
}
