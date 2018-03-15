#include "GameObject.h"


GameObject::GameObject() 
    : position(0, 0), size(1, 1), velocity(0.0f), color(1.0f), rotation(0.0f), isSolid(false), destroyed(false){ }

GameObject::GameObject(const glm::vec2 pos, const glm::vec2 size, const Texture2D sprite, const glm::vec3 color, const glm::vec2 velocity) 
    : position(pos), size(size), velocity(velocity), color(color), rotation(0.0f), isSolid(false), destroyed(false), sprite(sprite) { }

void GameObject::Draw(SpriteRenderer &renderer)
{
    renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
}