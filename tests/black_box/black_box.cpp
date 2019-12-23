/*
********************************************************************************

MobileyeTest
Developer : Mirit Hadar

********************************************************************************
*/

#include <cstddef>      //size_t
#include <ctype.h>      // isdigit

#include "black_box.hpp"

namespace mobileye
{

Request::Request(packet_t packet_)
    : m_type(0),
      //m_type(IsPacketValid(packet_)),
      m_packetSize(0),
      m_command(0),
      m_sizeA(0),
      m_valueA(0),
      m_sizeB(0),
      m_valueB(0),
      m_minSize(0),
      m_maxSize(0)
{
    
}

bool Request::IsPacketValid(packet_t packet_)
{
    if (sizeof(int) != sizeof(packet_))
    {
        throw RequestNotValid("not an int in req");
    }
    if ((packet_ != 0) && !(packet_ == 0))
    {
        throw RequestNotValid("not a number in req");
    }

    return 0;
}


static size_t CountDigits(int num_)
{
    size_t numOfDigits = 0;
    while (0 != num_)
    {
        num_ >>= 1;
        ++numOfDigits;
    }

    return numOfDigits;
}

Response::Response(packet_t packet)
    : m_type(0),
      m_size(0),
      m_status(0),
      m_sizeA(0),
      m_valueA(0)
{

}
void BlackBox::Add(Request req1_, Request req2_,
                   Response &resp1_, Response &resp2_)
{
    // resp1_ = Send(req1_);
    // resp2_ = Send(req2_);
}

Response BlackBox::Send(Request req_)
{
    if (!(IsReqValid(req_)))
    {
        throw RequestNotValid("received non-valid request");
    }

    return Receive(req_);
}

Response BlackBox::Receive(Request &req_)
{
    Response response(0);
    response.SetSize(req_.GetSize());
    response.SetStatus(req_.GetStatus());
    response.SetSizeA(req_.GetSizeA());
    response.SetValueA(req_.GetValueA());

    if (!(IsRespValid(response)))
    {
        throw ResponseNotValid("created non-valid response");
    }
    
    return response;
    
}

bool BlackBox::IsReqValid(Request &req_)
{
    int reqNun = *(reinterpret_cast<int*>(&req_));
    size_t numOfDigits = CountDigits(reqNun);
    if ((numOfDigits < req_.GetMinSize()) ||
             (numOfDigits > req_.GetMaxSize()))
    {
        throw RequestNotValid("Request received is too long or too short");
    }
}

bool BlackBox::IsRespValid(Response &resp_)
{
    
}

} // namespace mobileye



