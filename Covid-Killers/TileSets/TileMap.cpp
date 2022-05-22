#include "TileMap.h"


void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = this->tileset;

    // draw the vertex array
    target.draw(this->vertices, states);
}

void TileMap::load(sf::Texture* tileset, sf::Vector2f scale)
{
    this->width = tileset->getSize().x * scale.x;
    this->height = tileset->getSize().y * scale.y;

    this->tileset = tileset;

    this->vertices.setPrimitiveType(sf::Quads);
    this->vertices.resize(4);

    this->vertices[0].position = multiplyVector(sf::Vector2f(0.f, 0.f), scale);
    this->vertices[1].position = multiplyVector(sf::Vector2f(tileset->getSize().x, 0.f), scale);
    this->vertices[2].position = multiplyVector(sf::Vector2f(tileset->getSize().x, tileset->getSize().y), scale);
    this->vertices[3].position = multiplyVector(sf::Vector2f(0.f, tileset->getSize().y), scale);

    // define its 4 texture coordinates
    this->vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
    this->vertices[1].texCoords = sf::Vector2f(tileset->getSize().x, 0.f);
    this->vertices[2].texCoords = sf::Vector2f(tileset->getSize().x, tileset->getSize().y);
    this->vertices[3].texCoords = sf::Vector2f(0.f, tileset->getSize().y);
}

void TileMap::load(sf::Texture* tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, sf::Vector2f scale)
{
    this->width = width * tileSize.x * scale.x;
    this->height = height * tileSize.y * scale.y;

    this->tileset = tileset;

    this->vertices.setPrimitiveType(sf::Quads);
    this->vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * width];

            // find its position in the tileset texture
            int tu = tileNumber % (this->tileset->getSize().x / tileSize.x); // Personal Notes: Finds X Coordinates
            int tv = tileNumber / (this->tileset->getSize().x / tileSize.x); // Personal Note: Finds Y Coordinates

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &this->vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x * scale.x, j * tileSize.y * scale.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x * scale.x, j * tileSize.y * scale.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x * scale.x, (j + 1) * tileSize.y * scale.y);
            quad[3].position = sf::Vector2f(i * tileSize.x * scale.x, (j + 1) * tileSize.y * scale.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
}

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, sf::Vector2f scale)
{
    this->width = width * tileSize.x * scale.x;
    this->height = height * tileSize.y * scale.y;

    // load the tileset texture
    if (!this->tileset->loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the level size
    this->vertices.setPrimitiveType(sf::Quads);
    this->vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * width];

            // find its position in the tileset texture
            int tu = tileNumber % (this->tileset->getSize().x / tileSize.x); // Personal Notes: Finds X Coordinates
            int tv = tileNumber / (this->tileset->getSize().x / tileSize.x); // Personal Note: Finds Y Coordinates

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &this->vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x * scale.x, j * tileSize.y * scale.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x * scale.x, j * tileSize.y * scale.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x * scale.x, (j + 1) * tileSize.y * scale.y);
            quad[3].position = sf::Vector2f(i * tileSize.x * scale.x, (j + 1) * tileSize.y * scale.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}

sf::FloatRect TileMap::getGlobalBounds()
{
    return sf::FloatRect(this->getPosition().x, this->getPosition().y, this->width, this->height);
}

TileMapMovementComponent& TileMap::getMovementComponent()
{
    return this->movementComponent;
}

void TileMap::update(const float& dt, const sf::View& view, const sf::Vector2f& relativePosition)
{
    if (this->movementComponent.isMoving)
    {
        this->move(normalize(this->movementComponent.direction) * this->movementComponent.velocity * dt);

        sf::Vector2f changePosition = this->getPosition();

        if (this->movementComponent.hasRelative && this->getGlobalBounds().left > view.getSize().x)
        {
            changePosition.x = relativePosition.x - this->getGlobalBounds().width + this->getGlobalBounds().width * 0.01f;
        }

        if (this->movementComponent.hasRelative && this->getGlobalBounds().top > view.getSize().y)
        {
            changePosition.y = relativePosition.y - this->getGlobalBounds().height + this->getGlobalBounds().height * 0.01f;
        }

        this->setPosition(changePosition);
    }
}
