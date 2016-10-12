#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

//template <typename T>
class InputMemoryStream
{
public:
    InputMemoryStream(char *inBuffer, uint32_t inByteCount) :
        mCapacity(inByteCount), mHead(0) {}
    ~InputMemoryStream() { std::free(mBuffer); }
    uint32_t GetRemainingDataSize() const { return mCapacity - mHead; }

    void Read(void *outData, uint32_t inByteCount);
    template<typename T> void Read(T inData) {
        static_assert(std::is_arithmetic<T>::value ||
                std::is_enum<T>::value,
                "Generic write only supports primitive types");
        Write(&inData, sizeof(inData));
    }
private:
    char *mBuffer;
    uint32_t mHead;
    uint32_t mCapacity;

};

void InputMemoryStream::Read(void* outData, uint32_t inByteCount)
{
    uint32_t resultHead = mHead + inByteCount;
    if( resultHead > mCapacity )
    {
        //handle error, no data to read!
    }
    std::memcpy(outData, mBuffer + mHead, inByteCount);
    mHead = resultHead;
}


class OutputMemoryStream
{
public:
    OutputMemoryStream() :
        mBuffer(nullptr), mHead(0), mCapacity(0)
    {
        ReallocBuffer(32);
    }
    ~OutputMemoryStream() { std::free(mBuffer); }

    // get a pointer to the data in the stream
    const char *GetBufferPtr() const { return mBuffer; }

    void Write(const void *inData, size_t inByteCount);
    template<typename T> void Write(T inData) {
        static_assert(std::is_arithmetic<T>::value ||
                std::is_enum<T>::value,
                "Generic write only supports primitive types");
        Write(&inData, sizeof(inData));
    }
    //void Write(uint32_t inData) { Write(&inData, sizeof( inData)); }
    //void Write(int32_t inData) { Write(&inData, sizeof( inData)); }

private:
    void ReallocBuffer(uint32_t inNewLength);

    char *mBuffer;
    uint32_t mHead;
    uint32_t mCapacity;
};

void OutputMemoryStream::ReallocBuffer(uint32_t inNewLength)
{
    mBuffer = static_cast<char*>(std::realloc(mBuffer, inNewLength));
    // handle failure
    mCapacity = inNewLength;
}

void OutputMemoryStream::Write(const void *inData, size_t inByteCount)
{
    uint32_t resultHead = mHead + static_cast<uint32_t>(inByteCount);
    if (resultHead > mCapacity)
    {
        ReallocBuffer(std::max(mCapacity*2, resultHead));
    }
    std::memcpy(mBuffer + mHead, inData, inByteCount);
    mHead = resultHead;
}

// compose a new class
class RoboCat
{
public:
    RoboCat(): mHealth(0), mMeowCount(3), mName("Sylvester") {}
    void Write(OutputMemoryStream& oStream) const;
    void Read(InputMemoryStream& iStream);
    void Dump() {
        std::stringstream os;
        os << "health = " << mHealth << ", ";
        os << "meows = " << mMeowCount << ", ";
        os << "name = " << mName;
        std::string s = os.str();
        std::cout << s << '\n';
    }
private:
    int32_t mHealth;
    int32_t mMeowCount;
    std::string mName;
};

void RoboCat::Write(OutputMemoryStream& oStream) const
{
    oStream.Write(mName.c_str(), mName.size());
    oStream.Write(mHealth);
    oStream.Write(mMeowCount);
}

void RoboCat::Read(InputMemoryStream& iStream)
{
}

using namespace std;

int main()
{
    OutputMemoryStream oms;
    RoboCat rc;
    rc.Write(oms);
    rc.Dump();
    //cout << oms.GetBufferPtr() << endl;
}
