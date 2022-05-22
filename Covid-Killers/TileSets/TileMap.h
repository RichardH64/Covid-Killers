#ifndef TILEMAP_H
#define TILEMAP_H


#include "../Physics.h"

struct TileMapMovementComponent
{
    bool isMoving;
    bool hasRelative;
    float velocity;
    sf::Vector2f direction;
};

// Taken From sfml-dev.org/tutorials/2.4/graphics-vertex-array.php
class TileMap : public sf::Drawable, public sf::Transformable
{
private:
    float width;
    float height;

    TileMapMovementComponent movementComponent;

    sf::VertexArray vertices;
    sf::Texture* tileset;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    void load(sf::Texture* tileset, sf::Vector2f scale);
    void load(sf::Texture* tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, sf::Vector2f scale);
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, sf::Vector2f scale);

    sf::FloatRect getGlobalBounds();

    TileMapMovementComponent& getMovementComponent();

    void update(const float& dt, const sf::View& view, const sf::Vector2f& relativePosition = sf::Vector2f(0.f, 0.f));
};


#endif // !TILEMAP_H
