#include "stdafx.h"
#include "SendMavlink.h"


SendMavlink::SendMavlink()
{
}
// ���mavlink��Ϣ��movedirectionΪ�ƶ�����
// ǰ(0000 0000 0011 0000 0000 0000 0000 0000)
//�� 0000 0000 0000 0011 0000 0000 0000 0000
//�� 0000 0000 0000 0000 0011 0000 0000 0000
//�� 0000 0000 0000 0000 0000 0011 0000 0000

//�� 0000 0000 0000 0000 0000 0000 0011 0000
//�� 0000 0000 0000 0000 0000 0000 0000 0011
int SendMavlink::sendHeartBeat(uint32_t MoveDirection, byte* cse)
{
	mavlink_message_t msgSend = { 0 };
	uint8_t base_mode = MAV_MODE_FLAG_CUSTOM_MODE_ENABLED;
	uint8_t system_status = 0;
	uint32_t custom_mode = MoveDirection;

	mavlink_msg_heartbeat_pack(
		1,
		0,
		&msgSend,
		MAV_TYPE_QUADROTOR,
		MAV_AUTOPILOT_ARDUPILOTMEGA,
		base_mode,
		custom_mode,
		system_status);
	//byte cse[sizeof(msgSend)];
	memcpy(cse, &msgSend, sizeof(msgSend));
	mavlink_msg_to_send_buffer(cse, &msgSend);
	return msgSend.len;

}

SendMavlink::~SendMavlink()
{
}
