/*
 * ParticleSystem.h
 *
 *  Created on: 11 мая 2017 г.
 *      Author: FOXikOz
 */

#ifndef PARTICLESYSTEM_H_
#define PARTICLESYSTEM_H_

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include <iostream>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
private:

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
    unsigned char m_button;
    unsigned char m_scale;
    sf::Color m_color;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void resetParticle(std::size_t index);

public:
	ParticleSystem(unsigned int count) :
	m_particles(count),
	m_vertices(sf::Points, count),
	m_lifetime(sf::seconds(3)),
	m_emitter(0, 0),
	m_button(0),
	m_scale(0),
	m_color(sf::Color::White)
	{}
	virtual ~ParticleSystem() {}

	void setEmitter(sf::Vector2f position)
	{	m_emitter = position;	}

	void pressedButton(unsigned char button)
	{	m_button |= button;	dumpButton(); }
	void releasedButton(unsigned char button)
	{	m_button ^= button;	dumpButton(); }
	void changeScale(unsigned char delta)
	{	m_scale += delta;	dumpButton(); }
	void dumpButton()
	{	std::cout << (int) m_button << " " <<(int) m_scale << "\n"; }

	void update(sf::Time elapsed);
};

#endif /* PARTICLESYSTEM_H_ */
