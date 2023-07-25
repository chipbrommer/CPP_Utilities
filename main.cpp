#include "CPP_Utilities/utilties.h"

int main()
{
	struct msg
	{
		uint8_t sync;
		uint8_t msgID;
		uint8_t dataOne;
		uint16_t dataTwo;
		uint8_t spares[7];
		uint16_t checksum;
	};

	int msgSize = sizeof(msg);

	msg MyMsg = { 0 };
	MyMsg.sync = 0x41;
	MyMsg.msgID = 0x01;
	MyMsg.dataOne = 0x11;
	MyMsg.dataTwo = 0x2222;
	MyMsg.checksum = Essentials::Utilities::fletcher16((uint8_t*)&MyMsg, msgSize, 0, sizeof(MyMsg.checksum));

	Essentials::Utilities::printBufferInHex((uint8_t*)&MyMsg, msgSize,8);

	return 0;
}
