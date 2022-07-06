#pragma once
#include "Agent.h"

namespace Conditions {

    class Condition
    {
    public:
        virtual bool IsTrue(Agent* agent) = 0;
    };

    class SqrDistanceCondition : public Condition
    {
    private:
        float m_distance;
        bool m_lessThan;

    public:
        SqrDistanceCondition(float d, bool lt) : m_distance(d), m_lessThan(lt) {}
        virtual bool IsTrue(Agent* agent);
    };

}


