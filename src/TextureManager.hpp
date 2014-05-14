#ifndef Texture_MANAGER_H
#define Texture_MANAGER_H
#include <SFML/Graphics.hpp>
#include <ResourceManager.hpp>

class TextureManager : public ResourceManager<sf::Texture>
{
    private:
    protected:
        virtual sf::Texture* load( const std::string& strId );
    public:
};

extern TextureManager gTextureManager;
#endif
