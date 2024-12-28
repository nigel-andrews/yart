#include <CLI/CLI.hpp>
#include <cstdint>
#include <format>
#include <glm/geometric.hpp>

#include "object/object_factory.h"
#include "renderer/diffuse_functions.h"
#include "renderer/render_functions.h"
#include "renderer/renderer.h"
#include "renderer/window.h"

// FIXME: Use Rune when texture displays available
int main(int argc, char** argv)
{
    CLI::App yart;

    bool windowed{};
    yart.add_flag("--windowed,-w", windowed,
                  "Render scene in a window and update over time")
        ->take_last();

    int width{};
    int height{};
    auto width_opt =
        yart.add_option("width", width, "Width of the rendered scene");
    auto height_opt =
        yart.add_option("height", height, "Width of the rendered scene")
            ->take_first();

    yart.needs(width_opt);
    yart.needs(height_opt);

    CLI11_PARSE(yart, argc, argv);

    // TODO: Scene manager for dynamic drawing (preferably with some UI)
    renderer renderer{ width, height };
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

    if (!windowed)
    {
        renderer.render_scene(scene, sampler{}, bsdf);
        renderer.display(render_functions::ppm3_renderer{});
        return 0;
    }

    init_graphics();

    window window{ width, height };
    render_functions::sdl2_renderer render_func{ window };

    SDL_Event event;
    int frames = 0;
    bool quit = false;

    // FIXME: render scene in diff thread
    do
    {
        if (++frames == 100)
        {
            frames = 0;
            renderer.render_scene(scene, sampler{}, bsdf);
            renderer.display(render_func);
            window.present();
        }
        quit = SDL_PollEvent(&event) && event.type == SDL_QUIT;
    } while (!quit);

    destroy_graphics();
}
