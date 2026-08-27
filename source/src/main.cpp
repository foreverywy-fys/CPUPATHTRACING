#include "until/rgb.hpp"
#include "shape/sphere.hpp"
#include "shape/model.hpp"
#include "camera/film.hpp"
#include "camera/camera.hpp"
#include "shape/plane.hpp"
#include "material/diffuse_material.hpp"
#include "material/dieletric_material.hpp"
#include "material/ground_material.hpp"
#include "material/conductor_material.hpp"
#include "shape/scene.hpp"
#include "renderer/path_tracing_renderer.hpp"
#include "renderer/previewer.hpp"
#include <vector>

int main()
{
    Film film { 192 * 4, 108 * 4 };

    Camera camera { film, { -8.0F, 3.0F, 0.0F }, { 0.0F, 0.5F, 0.0F }, 50.0F };
    Sphere sphere { { 0, 0, 0 }, 1 };
    Plane plane { { 0, 0, 0 }, { 0, 1, 0 } };
    Model dragon_model { "models/dragon_871k.obj" };
    const glm::vec3 test_sphere_scale { 0.8F, 0.8F, 0.8F };
    const float test_sphere_spacing = 2.0F;
    const float dielectric_row_height = 0.5F;
    const float conductor_row_height = 2.5F;

    GroundMaterial ground_material { glm::vec3 { RGB { 120, 204, 157 } } };
    ground_material.setEmissive({ 0.0F, 0.0F, 0.0F });
    DiffuseMaterial light_material { glm::vec3 { 1.0F, 1.0F, 1.0F } };
    light_material.setEmissive({ 0.95F, 0.95F, 1.0F });
    std::vector<DieletricMaterial> dielectric_materials;
    dielectric_materials.reserve(7);
    std::vector<ConductorMaterial> conductor_materials;
    conductor_materials.reserve(7);
    DieletricMaterial dragon_dielectric_material
    {
        1.5F,
        { 0.85F, 0.95F, 1.0F },
        0.25F,
        0.25F
    };
    ConductorMaterial dragon_conductor_material
    {
        { 0.2F, 1.2F, 1.8F },
        { 3.0F, 2.5F, 1.5F },
        0.25F,
        0.25F
    };

    Scene scene = {};

    for (int i = -3; i <= 3; ++i)
    {
        float roughness = 0.1F + 0.1F * static_cast<float>(i + 3);
        dielectric_materials.emplace_back
        (
            1.1F + 0.2F * static_cast<float>(i + 3),
            glm::vec3 { 1.0F, 1.0F, 1.0F },
            roughness,
            roughness
        );
        scene.addShape
        (
            sphere,
            &dielectric_materials.back(),
            { 0.0F, dielectric_row_height, static_cast<float>(i) * test_sphere_spacing },
            test_sphere_scale
        );
    }

    for (int i = -3; i <= 3; ++i)
    {
        glm::vec3 color = RGB::GenerateHeatmapRGB
        (
            static_cast<float>(i + 3) / 6.0F
        );
        float roughness = 0.1F + 0.1F * static_cast<float>(i + 3);
        conductor_materials.emplace_back
        (
            glm::vec3 { 2.0F } - color * 2.0F,
            glm::vec3 { 2.0F } + color * 3.0F,
            roughness,
            roughness
        );
        scene.addShape
        (
            sphere,
            &conductor_materials.back(),
            { 0.0F, conductor_row_height, static_cast<float>(i) * test_sphere_spacing },
            test_sphere_scale
        );
    }

    scene.addShape(plane, &ground_material, { 0.0F, -0.5F, 0.0F });
    scene.addShape(plane, &light_material, { 0.0F, 10.0F, 0.0F });
    scene.addShape
    (
        dragon_model,
        &dragon_dielectric_material,
        { -3.5F, 0.4F, -2.0F },
        { 0.8F, 0.8F, 0.8F }
    );
    scene.addShape
    (
        dragon_model,
        &dragon_conductor_material,
        { -3.5F, 0.4F, 2.0F },
        { 0.8F, 0.8F, 0.8F }
    );
    scene.build();


    PathTracingRenderer path_tracing_renderer { camera, scene };
    Previewer previewer { path_tracing_renderer };
    if (previewer.preview())
    {
        path_tracing_renderer.render(4096, "PT_microfacet_test.ppm");
    }

    return 0;
}

//Debug Mode:
//ssp 32
//Load Model 133ms
//ParalleFor 450ms
//save 220ms
//render 32spp 687937ms

//Release Mode:
//ssp 32
//Load Model 68ms
//ParalleFor 390ms
//save 280ms
//render 32spp 530641ms

//Chunked ParalleFor:
//ParalleFor 0ms

//Save ParalleFor:
//save 6ms

//Add Bounds
//Load Model 153ms
//render 32spp 105676ms

//RapidObj
//Load Model 12ms

//Add BVH
//ssp 128
//render 128spp 107176ms

//Dragon 871k + BVH + Debug Renderers
//Loading: models/dragon_871k.obj
//Parsed 435545 vertices, 1 shapes, 871306 triangles
//BVH total_node_count 1328235
//BVH total_triangle_count 871306
//BVH leaf_node_count 664118
//BVH max_leaf_node_triangle_count 67
//Load Model 1873ms
//render 128spp 8891ms

//Dragon 871k + SAH + Debug Renderers
//Loading: models/dragon_871k.obj
//Parsed 435545 vertices, 1 shapes, 871306 triangles
//BVH total_node_count 1742423
//BVH total_triangle_count 871306
//BVH leaf_node_count 871212
//BVH max_leaf_node_triangle_count 3
//Load Model 43488ms
//render 128spp 8975ms

//Dragon 871k + Bucket BVH
//Loading: models/dragon_871k.obj
//Parsed 435545 vertices, 1 shapes, 871306 triangles
//BVH total_node_count 1742425
//BVH total_triangle_count 871306
//BVH leaf_node_count 871213
//BVH max_leaf_node_triangle_count 3
//Load Model 5959ms
//render 128spp 8785ms

//non thread local RNG
//10149ms

//thread local RNG
//2159ms
