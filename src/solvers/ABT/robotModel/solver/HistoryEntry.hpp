#pragma once
#include "solvers/ABT/solver/HistoryEntry.hpp"

namespace abt
{
class OPPTHistoryEntry: public HistoryEntry
{
public:
    OPPTHistoryEntry();

    OPPTHistoryEntry(abt::HistorySequence* owningSequence, IdType entryId);

protected:
    virtual void registerNode(abt::BeliefNode* node, bool addParticle = true) override;

};
}

