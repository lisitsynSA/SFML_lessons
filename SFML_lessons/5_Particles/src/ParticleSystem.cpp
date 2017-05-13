/*
 * ParticleSystem.cpp
 *
 *  Created on: 11 мая 2017 г.
 *      Author: FOXikOz
 */

#include "ParticleSystem.h"
#include <cstdlib>
#include <cmath>

enum Button
    {
        Left 	= 1,    ///< The left mouse button
        Right 	= 2,    ///< The right mouse button
        Middle 	= 4     ///< The middle (wheel) mouse button
    };

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = NULL;

	// draw the vertex array
	target.draw(m_vertices, states);
}

void ParticleSystem::resetParticle(std::size_t index)
{
	// give a random velocity and lifetime to the particle
	float angle = (std::rand() % 360) * 3.14f / 180.f;
	float speed = (m_button&Left ? 25 : (std::rand() % 50)) + 50.f*m_scale/125;
	m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	m_particles[index].lifetime = sf::milliseconds((m_button&Right ? 500 : (std::rand() % 2000)) + 1000);

	// reset the position of the corresponding vertex
	m_vertices[index].position = m_emitter;
	if (m_button&Middle)
	{
		m_vertices[index].color.r = std::rand() % 255;
		m_vertices[index].color.g = std::rand() % 255;
		m_vertices[index].color.b = std::rand() % 255;
	} else
		m_vertices[index].color = sf::Color::White;
}

void ParticleSystem::update(sf::Time elapsed)
{
	for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= elapsed;

		// if the particle is dead, respawn it
		if (p.lifetime <= sf::Time::Zero)
			resetParticle(i);

		// update the position of the corresponding vertex
		m_vertices[i].position += p.velocity * elapsed.asSeconds();

		// update the alpha (transparency) of the particle according to its lifetime
		float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
		m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
	}
}
