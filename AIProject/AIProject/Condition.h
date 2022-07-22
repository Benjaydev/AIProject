#pragma once
#include "Agent.h"

namespace Conditions {

    class Condition
    {
    public:
        virtual bool IsTrue(Agent* agent, float deltaTime) = 0;
    };

    class SqrDistanceCondition : public Condition
    {
    private:
        float m_distance;
        bool m_lessThan;

    public:
        SqrDistanceCondition(float d, bool lt) : m_distance(d), m_lessThan(lt) {}
        virtual bool IsTrue(Agent* agent, float deltaTime);
    };

    class SeeCondition : public Condition
    {
    private:
        float viewDistance;
        float viewAngle;

        float viewTime;
        float viewTimeCount;

    public:
        SeeCondition(float vDistance, float vAngle, float vTime) : viewDistance(vDistance), viewAngle(vAngle), viewTime(vTime) {}
        virtual bool IsTrue(Agent* agent, float deltaTime);
    };

    class SeeSuspiciousCondition : public Condition
    {
    private:
        float viewDistance;
        float viewAngle;

        float viewTime;
        float viewTimeCount;

        bool isSuspicious = false;


    public:
        SeeSuspiciousCondition(float vDistance, float vAngle, float vTime) : viewDistance(vDistance), viewAngle(vAngle), viewTime(vTime) {}
        virtual bool IsTrue(Agent* agent, float deltaTime);
    };



}


