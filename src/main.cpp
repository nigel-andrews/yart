#include <format>

#include "object/object_factory.h"
#include "renderer/diffuse_functions.h"
#include "renderer/renderer.h"

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

    // FIXME: if objects are vectors of variants that would be visited, no need
    // to have the factory and thus we could return scene& and chain add objects
    const auto obj = scene.add_object(
        factory::make_sphere(glm::vec3{ 0.f, 0.f, -1.f }, 0.5f));

    const auto light = scene.add_object(
        factory::make_sphere(glm::vec3{ 0.f, 1.f, 0.f }, 0.5f));

    light->mat.emit_color = glm::vec3{ 1.f };
    light->mat.light_intensity = 1.f;

    const auto ground = scene.add_object(
        factory::make_sphere(glm::vec3{ 0.f, -100.5f, -1.f }, 100.f));

    ground->mat.albedo = glm::vec3{ 0.f, 1.f, 0.f };

    obj->mat.albedo = glm::vec3{ 1.f, 0.f, 0.f };

    scene.camera_get().look_at({}, { 0.f, 1.f, 0.f }, { 0.f, 0.f, -1.f });

    sampler uniform;
    bsdf bsdf{ diffuse_functions::lambertian{},
               [](utils::view_ptr<object>, const glm::vec3&, const glm::vec3&,
                  const glm::vec3&) { return glm::vec3{}; } };
    renderer.render_scene(scene, uniform, bsdf);
    renderer.display(render_functions::ppm3_renderer{});
}
