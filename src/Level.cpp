#include "Level.h"
#include <iostream>

Level::Level(void) { }

Level::~Level(void)
{
    for(unsigned int i = 0; i < m_layers.size(); i++)
    {
        delete m_layers[i];
    }
    m_layers.clear();
}


void Level::render(void)
{
    for (unsigned int i = 0; i < m_layers.size(); i++)
    {
        // std::cout << "rendering m_layers[" << i << "]\n";        
        m_layers[i]->render();
    }
    for (unsigned int i = 0; i < m_objectLayers.size(); i++)
    {
        // std::cout << "rendering m_objectLayers[" << i << "]\n";
        m_objectLayers[i]->render();
    }
}

void Level::update(void)
{
    // std::cout << "Updating Level\n";
    for (unsigned int i = 0; i < m_layers.size(); i++)
    {
        // std::cout << "updating m_layers: " << m_layers[i] << "\n";
        m_layers[i]->update(this);
    }
    for (unsigned int i = 0; i < m_objectLayers.size(); i++)
    {
        m_objectLayers[i]->update(this);
    }
}
