// smartcard.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WINSCARD.h"

class NFCReader
{
public:


	static NFCReader* getInstance()
	{
		if (m_pInstance ==NULL)
		{
			m_pInstance == new NFCReader();
			return m_pInstance;
		}
	}
	void Init()
	{
		retCode = SCardEstablishContext(SCARD_SCOPE_USER,
			NULL,
			NULL,
			&hContext);

		DWORD size = 256;
		retCode = SCardListReadersA(hContext,
			NULL,
			readerName,
			&size);
	}

	void getCardNumb(BYTE* outbuf)
	{
		retCode = SCardConnectA(hContext,
			readerName,
			SCARD_SHARE_SHARED,
			SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,
			&hCard,
			&dwActProtocol);
		
		memset(SendBuff, 0, sizeof(SendBuff));
		SendBuff[0] = 0xFF;					//CLA
		SendBuff[1] = 0xCA;					//INS
		SendLen = 5;
		RecvLen = 0xFF;


		ioRequest.dwProtocol = dwActProtocol;
		ioRequest.cbPciLength = sizeof(SCARD_IO_REQUEST);

		retCode = SCardTransmit(hCard,
			&ioRequest,
			SendBuff,
			SendLen,
			NULL,
			RecvBuff,
			&RecvLen);

		if (!retCode)
		{
			memcpy(outbuf, RecvBuff, RecvLen);
		}
	}

private:

	SCARDCONTEXT			hContext;
	SCARDHANDLE				hCard;
	unsigned long			dwActProtocol;

	SCARD_IO_REQUEST		ioRequest;
	int						retCode;
	char					readerName[256];
	DWORD					SendLen, RecvLen;
	BYTE					SendBuff[262], RecvBuff[262];

	NFCReader()
	{
		hContext = 0;
		hCard = 0;
		dwActProtocol = 0;

		ioRequest = { 0 };
		retCode = 0;
		readerName[256] = { 0 };
		SendLen = RecvLen = 0;
		SendBuff[262] = { 0 }, RecvBuff[262] = { 0 };
	}
	static NFCReader* m_pInstance;

};

	SCARDCONTEXT			hContext;
	SCARDHANDLE				hCard;
	unsigned long			dwActProtocol;

	SCARD_IO_REQUEST		ioRequest;
	int						retCode;
    char					readerName [256];
	DWORD					SendLen, RecvLen;
	BYTE					SendBuff[262], RecvBuff[262];


int _tmain(int argc, _TCHAR* argv[])
{

	retCode = SCardEstablishContext( SCARD_SCOPE_USER,
									 NULL,
									 NULL,
									 &hContext );

	if( retCode != SCARD_S_SUCCESS )
	{
		
		//DisplayOut( GetScardErrMsg( retCode ), RED );
		
	}

	
	DWORD size = 256;
	retCode = SCardListReadersA( hContext,
								NULL,
								readerName,
								&size );
	
	retCode = SCardConnectA( hContext,
		readerName,
		SCARD_SHARE_SHARED,
		SCARD_PROTOCOL_T0|SCARD_PROTOCOL_T1,
		&hCard,
		&dwActProtocol );

	SendBuff[0] = 0xFF;					//CLA
	SendBuff[1] = 0xCA;					//INS
	SendLen = 5;
	RecvLen = 0xFF;
    

    ioRequest.dwProtocol = dwActProtocol;
	ioRequest.cbPciLength = sizeof( SCARD_IO_REQUEST );
		
	retCode = SCardTransmit( hCard,
							 &ioRequest,
							 SendBuff,
							 SendLen,
							 NULL,
							 RecvBuff,
							 &RecvLen );

	return 0;
}

