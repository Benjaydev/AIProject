#include "UtilityAI.h"
#include "Agent.h"


UtilityAI::UtilityAI()
{
}

UtilityAI::~UtilityAI()
{
	for (Behaviour* b : m_behaviours) {
		delete b;
	}
}

void UtilityAI::AddBehaviour(Behaviour* b)
{
    m_behaviours.push_back(b);
}

void UtilityAI::Update(Agent* agent, float deltaTime)
{
    // Find new behaviour
    Behaviour* newBehaviour = nullptr;
    if (currentBehaviour == nullptr || currentBehaviour->isFinished) {
        
        float* weights = new float[m_behaviours.size()];
        for (int i = 0; i < m_behaviours.size(); i++)
        {
            Behaviour* b = m_behaviours[i];
            float eval = b->Evaluate(agent);

            weights[i] = eval;
        }
        
        newBehaviour = m_behaviours[GetIndexOfRandomisedWeights(weights, m_behaviours.size())];

        delete[] weights;
    }
    


    // If there is new behaviour
    if (newBehaviour != nullptr)
    {
        // Exit current behaviour
        if (currentBehaviour) {
            currentBehaviour->Exit(agent);
        }
        // Set current behaviour
        currentBehaviour = newBehaviour;
        currentBehaviour->Enter(agent);
    }

    // Update behaviour
    currentBehaviour->Update(agent, deltaTime);

    
}

void UtilityAI::DrawBehaviourValue(Agent* agent, int behaviourIndex, float behaviourValue)
{
    Color textColour = BLACK;
    if (m_behaviours[behaviourIndex]->name == currentBehaviour->name) {
        textColour = RED;
    }

    std::string text = m_behaviours[behaviourIndex]->name + ": " + std::to_string(behaviourValue);
    DrawText(text.c_str(), agent->pathAgent->ownerPhysics->GetPosition().x + 30, agent->pathAgent->ownerPhysics->GetPosition().y - 20 + (behaviourIndex*15), 16, textColour);
}

void UtilityAI::Draw(Agent* agent)
{
    DrawRectangle(agent->pathAgent->ownerPhysics->GetPosition().x + 25, agent->pathAgent->ownerPhysics->GetPosition().y - 25, 150, 5 + m_behaviours.size()*15, GetColor(0xFFFFFFAA));


    for (int i = 0; i < m_behaviours.size(); i++)
    {
        Behaviour* b = m_behaviours[i];
        float eval = b->Evaluate(agent);

        DrawBehaviourValue(agent, i, eval);
    }
}

int UtilityAI::GetIndexOfRandomisedWeights(float* weights, int n)
{
    // Get total sum
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += weights[i];
    }
    
    float randVal = (rand() % (int)(sum * 1000))/1000.0f;
    sum = 0;
    // Find the value that pushes sum above random value
    for (int i = 0; i < n; i++) {
        sum += weights[i];
        // Return current index
        if (sum >= randVal) {
            return i;
        }
    }

    return n;
}

