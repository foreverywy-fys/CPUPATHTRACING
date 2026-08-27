#include "shape/scene.hpp"
#include <glm/gtc/matrix_transform.hpp>

void Scene::addShape(const Shape &shape,const Material *material, const glm::vec3 &pos, const glm::vec3 &scale, const glm::vec3 &rotate)
{
    const glm::mat4 world_from_object =
        glm::translate(glm::mat4(1.0F), pos) *
        glm::rotate(glm::mat4(1.0F), glm::radians(rotate.x), glm::vec3(1.0F, 0.0F, 0.0F)) *
        glm::rotate(glm::mat4(1.0F), glm::radians(rotate.y), glm::vec3(0.0F, 1.0F, 0.0F)) *
        glm::rotate(glm::mat4(1.0F), glm::radians(rotate.z), glm::vec3(0.0F, 0.0F, 1.0F)) *
        glm::scale(glm::mat4(1.0F), scale);
    instances.push_back(ShapeInstance { shape, material, world_from_object, glm::inverse(world_from_object) });
}

std::optional<HitInfo> Scene::intersect(const Ray &ray, float t_min, float t_max) const
{
    return scene_bvh.intersect(ray, t_min, t_max);
}
