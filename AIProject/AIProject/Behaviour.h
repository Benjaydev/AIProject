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

		float duration = 3;
		bool isFinished = false;

		virtual std::string GetName(){return name; }

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
		float cooldownCount = 2;

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
		FollowTargetBehaviour() {
			name = "Follow";
		}
		virtual void Enter(Agent* agent);
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Exit(Agent* agent) {
			isFinished = false;
		};

		Vector2 lastTargetPosition;

		int distanceToEnter = 0;

		float cooldown = 2;
		float cooldownCount = 2;

		virtual float Evaluate(Agent* agent);
	};
	
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	// FLEE TARGET BEHAVIOUR
	class FleeTargetBehaviour : public Behaviour
	{
	public:
		FleeTargetBehaviour(int cellDistance) {
			distanceToEnter = cellDistance;
			name = "Flee"; 

		
		}
		FleeTargetBehaviour() {
			name = "Flee";
		}
		virtual void Enter(Agent* agent);
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Exit(Agent* agent){};

		int distanceToEnter = 0;

		float cooldown = 5;
		float cooldownCount = 5;

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
		virtual void Enter(Agent* agent);
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Exit(Agent* agent){};

		float cooldown = 2;
		float cooldownCount = 2;

		float lifeTime = 10;

		virtual float Evaluate(Agent* agent);
	};	
	
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	// SEARCH AREA BEHAVIOUR
	class SearchAreaBehaviour : public Behaviour
	{
	private:
		float radius = 5.0f;
	public:
		SearchAreaBehaviour(float r) {
			radius = r;
			name = "Search";
		};
		virtual void Enter(Agent* agent);
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Exit(Agent* agent) { 
			isFinished = false;
			lifeTime = 10;
		};

		Vector2 searchArea;


		float cooldown = 2;
		float cooldownCount = 2;

		float lifeTime = 10;

		virtual float Evaluate(Agent* agent);
	};
	
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	// GO TO IMPORTANT LOCATION BEHAVIOUR
	class GoToImportantBehaviour : public Behaviour
	{
	public:
		GoToImportantBehaviour() {
			name = "GoToImportant";
		};
		
		GoToImportantBehaviour(float chanceOfEvaluate) {
			name = "GoToImportant";
			chance = chanceOfEvaluate;
		};
		virtual void Enter(Agent* agent);
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Exit(Agent* agent) { isFinished = false; };

		bool started = false;
		float chance = 0.05f;



		virtual float Evaluate(Agent* agent);
	};
	
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	// GO TO TOILET LOCATION BEHAVIOUR
	class GoToToiletBehaviour : public Behaviour
	{
	public:
		GoToToiletBehaviour() {
			name = "GoToToilet";
		};
		GoToToiletBehaviour(float chanceOfEvaluate) {
			name = "GoToToilet";
			chance = chanceOfEvaluate;
		};
		virtual void Enter(Agent* agent);
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Exit(Agent* agent) { isFinished = false; };

		bool started = false;

		float evalCount = 0;

		float chance = 0.05f;

		float toiletDuration = 15;
		float toiletDurationCount = 0;

		virtual float Evaluate(Agent* agent);
	};
	
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	// DEFEND TARGET BEHAVIOUR
	class DefendBehaviour : public Behaviour
	{
	public:
		DefendBehaviour(Agent* toDefend) {
			name = "DefendTarget";
			agentToDefend = toDefend;
		};
	

		virtual void Enter(Agent* agent);
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Exit(Agent* agent) { isFinished = false; };

		bool started = false;


		float cooldown = .5;
		float cooldownCount = 0;

		Vector2 lastAgentPosition;

		Agent* agentToDefend;

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
