#pragma once
#include "OpptUserData.hpp"
#include "typedefs.hpp"

namespace oppt
{
class RobotStateUserData: public OpptUserData
{
public:
	using OpptUserData::OpptUserData;

	_NO_COPY_BUT_MOVE(RobotStateUserData)

	RobotStateUserData() = default;

	virtual ~RobotStateUserData() = default;

	RobotStateSharedPtr previousState = nullptr;

};

typedef std::shared_ptr<RobotStateUserData> RobotStateUserDataSharedPtr;

}

