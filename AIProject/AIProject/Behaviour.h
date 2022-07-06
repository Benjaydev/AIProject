#pragma once
#include "raylib.h"
class Agent;

namespace Behaviours {
	class Behaviour
	{
	public:
		virtual void Enter(Agent* agent) {}
		virtual void Update(Agent* agent, float deltaTime) = 0;
		virtual void Exit(Agent* agent) {}
	};


	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	// WANDER BEHAVIOUR
	class WanderBehaviour : public Behaviour
	{
	public:
		virtual void Enter(Agent* agent);
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Exit(Agent* agent);


		float cooldown = 2;
		float cooldownCount = 0;

	};

	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	// GO TO POINT BEHAVIOUR
	class GoToPointBehaviour : public Behaviour
	{
	public:
		virtual void Enter(Agent* agent) {}
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Exit(Agent* agent) {}
	};

	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	// FOLLOW TARGET BEHAVIOUR
	class FollowTargetBehaviour : public Behaviour
	{
	public:
		virtual void Enter(Agent* agent);
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Exit(Agent* agent);;

		Vector2 lastTargetPosition;


		float cooldown = 1;
		float cooldownCount = 0;


	};

	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	// SELECTOR BEHAVIOUR
	class SelectorBehaviour : public Behaviour
	{
	private:
		Behaviour* m_b1;
		Behaviour* m_b2;
		Behaviour* m_selected;

	public:
		SelectorBehaviour(Behaviour* b1, Behaviour* b2) : m_b1(b1), m_b2(b2) {}
		~SelectorBehaviour() {
			delete m_b1;
			delete m_b2;
		}

		void SetBehaviour(Behaviour* b, Agent* agent);
		virtual void Enter(Agent* agent) {}
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Exit(Agent* agent) {}
	};



}
