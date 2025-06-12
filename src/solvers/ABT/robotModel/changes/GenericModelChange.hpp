#pragma once
#include "solvers/ABT/solver/abstract-problem/ModelChange.hpp"
#include "oppt/robotEnvironment/include/EnvironmentChanges.hpp"

namespace oppt
{
class GenericModelChange: public abt::ModelChange
{
public:
    GenericModelChange(const EnvironmentChangeSharedPtr &environmentChange):
        abt::ModelChange(),
        environmentChange_(environmentChange){

    }

    EnvironmentChangeSharedPtr getChange() const {
	return environmentChange_;
    }

private:
   EnvironmentChangeSharedPtr environmentChange_;

};
}

