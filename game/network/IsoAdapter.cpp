//
// Created by Matthew Periut on 10/20/21.
//

#include "IsoAdapter.h"
#include "TestMessage.h"
#include "server/IsoServer.h"

// the message factory
YOJIMBO_MESSAGE_FACTORY_START(GameMessageFactory, (int)GameMessageType::COUNT);
    YOJIMBO_DECLARE_MESSAGE_TYPE((int)GameMessageType::TEST, TestMessage);
YOJIMBO_MESSAGE_FACTORY_FINISH();

yojimbo::MessageFactory* IsoAdapter::CreateMessageFactory(yojimbo::Allocator& allocator)
{
    return YOJIMBO_NEW(allocator, GameMessageFactory, allocator);
}

void IsoAdapter::OnServerClientConnected(int clientIndex)
{
    if (m_server != NULL)
    {
        reinterpret_cast<IsoServer*>(m_server)->ClientConnected(clientIndex);
    }
}

void IsoAdapter::OnServerClientDisconnected(int clientIndex)
{
    if (m_server != NULL)
    {
        reinterpret_cast<IsoServer*>(m_server)->ClientDisconnected(clientIndex);
    }
}