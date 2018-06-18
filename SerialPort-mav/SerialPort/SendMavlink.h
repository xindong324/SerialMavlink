#pragma once
#include"MAVLINK/mavlink_avoid_errors.h"
#include"MAVLINK/common/mavlink.h"

class SendMavlink
{
public:
	SendMavlink();
	int sendHeartBeat(uint32_t MoveDirection, byte* cse);
	~SendMavlink();
};

