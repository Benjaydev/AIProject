#pragma once
#include "raylib.h"
#include <string>

class Agent;

namespace Behaviours {
	class Behaviour
	{
	public:
		virtual void Enter(Agent* agent) {}
		virtual void Update(Agent* agent, float deltaTime) = 0;
		virtual void Exit(Agent* agent) {}

		// Used by UtilityAI to determine which behaviour to do
		virtual float Evaluate(Agent* agent) { return 0.0f; }
		virtual void Draw(Agent* agent) {};

		std::string name = "Behaviour";
	};


	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	// WANDER BEHAVIOUR
	class WanderBehaviour : public Behaviour
	{
	public:
		WanderBehaviour(int cellDistance) { 
			distanceToExit = cellDistance;
			name = "Wander"; 
		}
		virtual void Enter(Agent* agent);
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Exit(Agent* agent);

		int distanceToExit = 0;

		float cooldown = 2;
		float cooldownCount = 0;

		virtual float Evaluate(Agent* agent);

	};

	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	// GO TO POINT BEHAVIOUR
	class GoToPointBehaviour : public Behaviour
	{
	public:
		GoToPointBehaviour() { name = "GoTo"; }
		virtual void Enter(Agent* agent) {}
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Exit(Agent* agent) {}

		virtual float Evaluate(Agent* agent);
	};

	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	// FOLLOW TARGET BEHAVIOUR
	class FollowTargetBehaviour : public Behaviour
	{
	public:
		FollowTargetBehaviour(int cellDistance) { 
			distanceToEnter = cellDistance;
			name = "Follow"; 
		
		}
		virtual void Enter(Agent* agent);
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Exit(Agent* agent);;

		Vector2 lastTargetPosition;

		int distanceToEnter = 0;

		float cooldown = 1;
		float cooldownCount = 0;

		virtual float Evaluate(Agent* agent);
	};

	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	// LINGER BEHAVIOUR
	class LingerBehaviour : public Behaviour
	{
	private:
		float radius = 5.0f;
	public:
		LingerBehaviour(float r) {
			radius = r;
			name = "Linger";
		};
		virtual void Enter(Agent* agent) {};
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Exit(Agent* agent) {};


		float cooldown = 2;
		float cooldownCount = 0;

		virtual float Evaluate(Agent* agent);
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
