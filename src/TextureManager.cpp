#include <iostream>
#include <TextureManager.hpp>

TextureManager gTextureManager;

sf::Texture* TextureManager::load( const std::string& strId )
{
    sf::Texture* Texture = new sf::Texture();
    if( !Texture->loadFromFile( strId ) )
    {
        std::cout << "[WARN] TextureManager failed to load: " << strId << std::endl;
        delete Texture;
        Texture = nullptr;
    }

    return Texture;
}
