MavLink������ֲ������
1. ��SerialPort-mav�ļ����е�MAVINK�ļ�����ӵ������ļ���
2. ��� SendMavlink.h �� SendMavlink.cpp
3. ����ʾ����

		byte cse[sizeof(mavlink_message_t)];
		SendMavlink send;
		int len = send.sendHeartBeat(MoveDirection,cse);
		len = len + MAVLINK_NUM_NON_PAYLOAD_BYTES; ///Ҫ�����޸�����Ϣ֡����
		m_SerialPort.WriteToPort(cse, len);
4. Լ��  
// ���mavlink��Ϣ��movedirectionΪ�ƶ�����
// ǰ(0000 0000 0011 0000 0000 0000 0000 0000)
//�� 0000 0000 0000 0011 0000 0000 0000 0000
//�� 0000 0000 0000 0000 0011 0000 0000 0000
//�� 0000 0000 0000 0000 0000 0011 0000 0000

//�� 0000 0000 0000 0000 0000 0000 0011 0000
//�� 0000 0000 0000 0000 0000 0000 0000 0011