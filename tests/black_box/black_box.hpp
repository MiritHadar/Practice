/*
********************************************************************************

MobileyeTest
Developer : Mirit Hadar

********************************************************************************
*/

#ifndef _black_box
#define _black_box

#include <stdint.h>		    // uint32_t
#include <exception>        // exceptions
#include <stdexcept>	
#include "uncopyable.hpp"   // Uncopyable class

#if __cplusplus < 201103L
#define noexcept throw()
#endif

namespace mobileye
{

typedef char byte_t;
typedef int packet_t;

class Request
{
public:
    //Ctors
    /* non explicit */ Request(packet_t packet_);
    // Request(const Request &other_) = default;
    //~Request() noexcept = default;
    
    //Operators
    //Request &operator=(const Request &other_) = default;

    //Functions
    byte_t GetSize(){}
    byte_t GetStatus(){}
    byte_t GetSizeA(){}
    uint32_t GetValueA(){}
    size_t GetMinSize(){}
    size_t GetMaxSize(){}

private:
    //data members
    const byte_t m_type;      // always zero
    byte_t m_packetSize;
    byte_t m_command;
    byte_t m_sizeA;
    uint32_t m_valueA;        // 8 bytes allocated for biggest size optional of sizeA
    byte_t m_sizeB;
    uint32_t m_valueB;        // 8 bytes allocated for biggest size optional of sizeB
    const size_t m_minSize;   // initialized to 7
    const size_t m_maxSize;   // initialized to 23

    //methods
    bool IsPacketValid(packet_t packet);
};

class Response
{
public:
    //Ctors
    /* non explicit */ Response(packet_t packet_);
    // Response(const Response &other_) = default;
    //~Response() noexcept = default;
    
    //Operators
    //Response &operator=(const Response &other_) = default;

    //Functions
    void SetSize(byte_t size_){}
    void SetStatus(byte_t status_){}
    void SetSizeA(byte_t sizeA_){}
    void SetValueA(byte_t valueA_){}

private:
    //data members
    const byte_t m_type; // always zero
    byte_t m_size;
    byte_t m_status;
    byte_t m_sizeA;
    uint32_t m_valueA;

    //methods
    bool IsPacketValid(packet_t packet){}
};

// Designed as Singletone
class BlackBox : private Uncopyable
{
public:
    static BlackBox *GetInstance() {}
    static Response Send(Request req_);
    static void Add(Request req1_, Request req2_,
                    Response &resp1_, Response &resp2_);

private:
    explicit BlackBox();    // preventing user from using regular Ctor
    static BlackBox *m_pInstance;
    static Response Receive(Request &req_);
    static bool IsReqValid(Request &req_);
    static bool IsRespValid(Response &resp_);
};

// exceptions
struct RequestNotValid : public std::runtime_error
{
    public:
        explicit RequestNotValid(const std::string &what_);  
};

struct ResponseNotValid : public std::runtime_error
{
    public:
        explicit ResponseNotValid(const std::string &what_);  
};

} // namespace mobileye


#endif /* _black_box */


