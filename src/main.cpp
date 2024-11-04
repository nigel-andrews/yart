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

    // FIXME: I should probably get rid of the yart namespace, this project is
    // not a library
    yart::renderer renderer{ std::atoi(argv[1]), std::atoi(argv[2]) };
    yart::scene scene;

    const auto obj = scene.add_object(
        yart::factory::make_sphere(glm::vec3{ 0.f, 0.f, -1.f }, 0.5f));

    const auto ground = scene.add_object(
        yart::factory::make_sphere(glm::vec3{ 0.f, -100.5f, -1.f }, 100.f));

    ground->material.albedo = glm::vec3{ 0.f, 1.f, 0.f };

    obj->material.albedo = glm::vec3{ 1.f, 0.f, 0.f };

    scene.camera_get().look_at({}, { 0.f, 1.f, 0.f }, { 0.f, 0.f, -1.f });

    scene.light_source_set({ -4.f, 0.f, -4.f });

    renderer.render_scene(scene);
}
