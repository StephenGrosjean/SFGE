/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <extensions/aabb_system.h>
#include <engine/engine.h>
#include <engine/config.h>
#include <graphics/graphics2d.h>
#include <physics/body2d.h>
#include <physics/physics2d.h>



namespace sfge::ext
{

	AABBSystem::AABBSystem(Engine& engine) :
		System(engine)

	{
	}

	void AABBSystem::OnEngineInit()
	{
		m_Transform2DManager = m_Engine.GetTransform2dManager();
		m_Body2DManager = m_Engine.GetPhysicsManager()->GetBodyManager();
		m_TextureManager = m_Engine.GetGraphics2dManager()->GetTextureManager();
		m_Graphics2DManager = m_Engine.GetGraphics2dManager();
		m_SpriteManager = m_Engine.GetGraphics2dManager()->GetSpriteManager();


		auto config = m_Engine.GetConfig();
		fixedDeltaTime = config->fixedDeltaTime;
		screenSize = sf::Vector2f(config->screenResolution.x, config->screenResolution.y);
		auto* entityManager = m_Engine.GetEntityManager();
		entityManager->ResizeEntityNmb(entitiesNmb);

		entities = entityManager->GetEntitiesWithType(ComponentType::BODY2D);

		for (auto i = 0u; i < entitiesNmb; i++)
		{
			//auto body = m_Body2DManager->GetComponentPtr(entities[i]);
			//bodies.push_back(body->GetBody());

		}

	}

	void AABBSystem::OnUpdate(float dt)
	{
		(void)dt;
	}


	void AABBSystem::OnFixedUpdate()
	{
		
	}

	void AABBSystem::OnDraw()
	{
		rmt_ScopedCPUSample(PlanetSystemDraw, 0);
#ifdef WITH_VERTEXARRAY
		sf::RenderStates renderStates;
		renderStates.texture = texture;
		auto window = m_Graphics2DManager->GetWindow();
		window->draw(m_VertexArray, renderStates);
#endif
	}

}
