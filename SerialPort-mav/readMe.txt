MavLink发送移植方法：
1. 将SerialPort-mav文件夹中的MAVINK文件夹添加到工程文件夹
2. 添加 SendMavlink.h 和 SendMavlink.cpp
3. 调用示例：

		byte cse[sizeof(mavlink_message_t)];
		SendMavlink send;
		int len = send.sendHeartBeat(MoveDirection,cse);
		len = len + MAVLINK_NUM_NON_PAYLOAD_BYTES; ///要加上无负载消息帧长度
		m_SerialPort.WriteToPort(cse, len);
4. 约定  
// 打包mavlink消息，movedirection为移动方向
// 前(0000 0000 0011 0000 0000 0000 0000 0000)
//后 0000 0000 0000 0011 0000 0000 0000 0000
//左 0000 0000 0000 0000 0011 0000 0000 0000
//右 0000 0000 0000 0000 0000 0011 0000 0000

//上 0000 0000 0000 0000 0000 0000 0011 0000
//下 0000 0000 0000 0000 0000 0000 0000 0011