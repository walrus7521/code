#ifndef _SOCKET_ADDRESS_H
#define _SOCKET_ADDRESS_H

class SocketAddress
{
public:
    SocketAddress(uint32_t inAddress, uint16_t inPort)
    {
        GetAsSockAddrIn()->sin_family = AF_INET;
        GetAsSockAddrIn()->sin_addr.s_addr = htonl(inAddress);
        GetAsSockAddrIn()->sin_port = htons(inPort);
    }
    SocketAddress(const sockaddr& inSockAddr)
    {
        memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
    }
    size_t GetSize() const { return sizeof(sockaddr); }
private:
    sockaddr mSockAddr;
    sockaddr_in* GetAsSockAddrIn()
    { return reinterpret_cast<sockaddr_in*>( &mSockAddr ); }
};

typedef std::shared_ptr<SocketAddress> SocketAddressPtr;


class SocketAddressFactory
{
public:
    static SocketAddressPtr CreateIPv4FromString(const std::string& inString)
    {
        auto pos = inString.find_last_of(':');
        std::string host, service;
        if (pos != std::string::npos)
        {
            host = inString.substr(0, pos);
            service = inString.substr(pos+1);
        }
        else
        {
            host = inString;
            // user default port...
            service = "0";
        }
        addrinfo hint;
        memset(&hint, 0, sizeof(hint));
        hint.ai_family = AF_INET;

        addrinfo *result;
        int error = getaddrinfo(host.c_str(), service.c_str(),
                                    &hint, &result);
        if (error != 0 && result != nullptr)
        {
            freeaddrinfo(result);
            return nullptr;
        }

        while (!result->ai_addr && result->ai_next)
        {
            result = result->ai_next;
        }

        if (!result->ai_addr)
        {
            freeaddrinfo(result);
            return nullptr;
        }
        auto toRet = std::make_shared<SocketAddress>(*result->ai_addr);
        freeaddrinfo(result);

        return toRet;
    }
};

class UDPSocket
{
public:
    ~UDPSocket();
    int Bind(const SocketAddress& inToAddress);
    int SendTo(const void *inData, int inLen, const SocketAddress& inTo);
    int ReceiveFrom(void *inBuffer, int inLen, SocketAddress& outFrom);
private:
    friend class SocketUtil;
    UDPSocket(SOCKET inSocket( : mSocket(inSocket) {}
    SOCKET mSocket;
};
typedef shared_ptr<UDPSocket> UDPSocketPtr;

int UDPSocket::Bind(const SocketAddress& inBindAddress)
{
    int err = bind(mSocket, &inBindAddress.mSockAddr,
            inBindAddress.GetSize());
    if (err != 0)
    {
        SocketUtil::ReportError(L"UDPSocket::Bind");
        return SocketUtil::GetLastError();
    }
    return NO_ERROR;
}

int UDPSocket::SendTo(const void *inData, int inLen,
                      const SocketAddress& inTo)
{
    int bytesSentCount = sendto(mSocket,
                                static_cast<const char*>(inData),
                                inLen,
                                0, &inTo.mSockAddr, inTo.GetSize());
    if (byteSentCount >= 0)
    {
        return byteSetCount;
    }
    else
    {
        // return error as negative number
        SocketUtil::ReportError(L"UDPSocket::SendTo");
        return SocketUtil::GetLastError();
    }
}

int UDPSocket::ReceiveFrom(void *inBuffer, int inLen,
                           SocketAddress& outFrom)
{
    int fromLength = outFromAddress.GetSize();
    int readByteCount = recvfrom(mSocket,
                                 static_cast<char *>(inBuffer),
                                 inMaxLength,
                                 0, &outFromAddress.mSocketAddr,
                                 &fromLength);
    if (readByteCount >= 0)
    {
        return readByteCount;
    }
    else
    {
        SocketUtil::ReportError(L"UDPSocket::ReceiveFrom");
        return SocketUtil::GetLastError();
    }

}

~UDPSocket::UDPSocket()
{
    closesocket(mSocket);
}



#endif


