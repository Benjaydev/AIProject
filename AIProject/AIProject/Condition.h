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

        float lastSeenCountdown;
        float lastSeenCountdownCount;

    public:
        SeeCondition(float vDistance, float vAngle, float lastSeenCooldown) : viewDistance(vDistance), viewAngle(vAngle), lastSeenCountdown(lastSeenCooldown) {}
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
    
    
    class NearUrgantSituationCondition : public Condition
    {
    private:
        float viewDistance;

        bool isSuspicious = false;


    public:
        NearUrgantSituationCondition(float vDistance) : viewDistance(vDistance) {}
        virtual bool IsTrue(Agent* agent, float deltaTime);
    };



}


