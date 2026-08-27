#include "shape/model.hpp"
#include <cstddef>
#include <optional>
#include <glm/glm.hpp>
#include "shape/triangle.hpp"
#include "until/profile.hpp"
#include <rapidobj/rapidobj.hpp>
#include <iostream>
#include <vector>


Model::Model(const std::filesystem::path &filename)
{
    PROFILE("Load model" + filename.string())
    auto result = rapidobj::ParseFile(filename, rapidobj::MaterialLibrary::Ignore());
    std::cout << "[Model] Loading: " << filename << '\n';
    if (result.error)
    {
        std::cerr << "[Model] Failed to parse " << filename
                  << " at line " << result.error.line_num
                  << ": " << result.error.code.message() << '\n';
        if (!result.error.line.empty())
        {
            std::cerr << "[Model] Source line: " << result.error.line << '\n';
        }
        return;
    }

    std::vector<Triangle> triangles;
    for (auto &shape : result.shapes)
    {
        size_t index_offset = 0;
        for (size_t num_face_vectex : shape.mesh.num_face_vertices)
        {
            if (num_face_vectex == 3)
            {
                auto index = shape.mesh.indices[index_offset];
                glm::vec3 pos0
                {
                    result.attributes.positions[index.position_index * 3],
                    result.attributes.positions[index.position_index * 3 + 1],
                    result.attributes.positions[index.position_index * 3 + 2],
                };
                index = shape.mesh.indices[index_offset + 1];
                glm::vec3 pos1
                {
                    result.attributes.positions[index.position_index * 3],
                    result.attributes.positions[index.position_index * 3 + 1],
                    result.attributes.positions[index.position_index * 3 + 2],
                };
                index = shape.mesh.indices[index_offset + 2];
                glm::vec3 pos2
                {
                    result.attributes.positions[index.position_index * 3],
                    result.attributes.positions[index.position_index * 3 + 1],
                    result.attributes.positions[index.position_index * 3 + 2],
                };

                if (index.normal_index >= 0)
                {
                    index = shape.mesh.indices[index_offset];
                    glm::vec3 normal0
                    {
                        result.attributes.normals[index.normal_index * 3],
                        result.attributes.normals[index.normal_index * 3 + 1],
                        result.attributes.normals[index.normal_index * 3 + 2],
                    };
                    index = shape.mesh.indices[index_offset + 1];
                    glm::vec3 normal1
                    {
                        result.attributes.normals[index.normal_index * 3],
                        result.attributes.normals[index.normal_index * 3 + 1],
                        result.attributes.normals[index.normal_index * 3 + 2],
                    };
                    index = shape.mesh.indices[index_offset + 2];
                    glm::vec3 normal2
                    {
                        result.attributes.normals[index.normal_index * 3],
                        result.attributes.normals[index.normal_index * 3 + 1],
                        result.attributes.normals[index.normal_index * 3 + 2],
                    };
                    triangles.push_back(Triangle
                    {
                        pos0, pos1, pos2, normal0, normal1, normal2
                    });
                }
                else 
                {
                    triangles.push_back(Triangle
                    {
                        pos0, pos1, pos2
                    });
                }
            }
            index_offset += num_face_vectex;
        }
    }

    std::cout << "[Model] Parsed " << result.attributes.positions.size() / 3
              << " vertices, " << result.shapes.size() << " shapes, "
              << triangles.size() << " triangles\n";
    if (triangles.empty())
    {
        std::cerr << "[Model] Warning: no triangles were generated\n";
    }

    bvh.build(std::move(triangles));
}

std::optional<HitInfo> Model::intersect(const Ray &ray, float t_min, float t_max) const
{
    return bvh.intersect(ray, t_min, t_max);
}
