#include <format>
#include <glm/geometric.hpp>

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
    //
#ifndef CORNELL
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

    scene.camera_get().look_at(glm::vec3{}, { 0.f, 1.f, 0.f },
                               glm::vec3{ 0.f, 0.f, -1.f });
#else
    scene
        .add_object(factory::make_plane(
            glm::vec3{ 555, 0, 0 },
            glm::cross(glm::vec3(0, 555, 0), glm::vec3(0, 0, 555))))
        ->mat.albedo = glm::vec3{ .12f, .45f, .15f };
    scene
        .add_object(factory::make_plane(
            glm::vec3{ 0, 0, 0 },
            glm::cross(glm::vec3(0, 555, 0), glm::vec3(0, 0, 555))))
        ->mat.albedo = glm::vec3{ 0.65f, 0.05f, 0.05f };
    scene
        .add_object(factory::make_plane(
            glm::vec3{ 0, 0, 0 },
            glm::cross(glm::vec3(555, 0, 0), glm::vec3(0, 0, 555))))
        ->mat.albedo = glm::vec3{ 0.73f };
    scene
        .add_object(factory::make_plane(
            glm::vec3{ 555, 555, 555 },
            glm::cross(glm::vec3(-555, 0, 0), glm::vec3(0, 0, -555))))
        ->mat.albedo = glm::vec3{ 0.73f };
    scene
        .add_object(factory::make_plane(
            glm::vec3{ 0, 0, 555 },
            glm::cross(glm::vec3{ 555, 0, 0 }, glm::vec3{ 0, 555, 0 })))
        ->mat.albedo = glm::vec3{ 0.73f };
    const auto cornell_light = scene.add_object(factory::make_plane(
        glm::vec3{ 343, 554, 332 },
        glm::cross(glm::vec3(-130, 0, 0), glm::vec3(0, 0, -105))));
    cornell_light->mat.emit_color = glm::vec3{ 15.f };
    cornell_light->mat.light_intensity = 1.f;
    scene.camera_get().look_at(glm::vec3{ 278.f, 278.f, -800.f },
                               { 0.f, 1.f, 0.f },
                               glm::vec3{ 278.f, 278.f, 0.f });
#endif /* !CORNELL */

    bsdf bsdf{ diffuse_functions::lambertian{},
               [](utils::view_ptr<object>, const glm::vec3&, const glm::vec3&,
                  const glm::vec3&) { return glm::vec3{}; } };
    renderer.render_scene(scene, sampler{}, bsdf);
    renderer.display(render_functions::ppm3_renderer{});
}
