#pragma once
#include "solvers/ABT/solver/Histories.hpp"

namespace abt
{
class OPPTHistories: public Histories
{
public:
    OPPTHistories();
protected:
    virtual HistorySequence* createSequence() override;
};
}

