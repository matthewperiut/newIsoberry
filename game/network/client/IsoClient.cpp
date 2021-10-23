//
// Created by Matthew Periut on 10/20/21.
//

#include <iostream>
#include "IsoClient.h"
#include "../TestMessage.h"

IsoClient::IsoClient(const yojimbo::Address& serverAddress) :
        m_client(yojimbo::GetDefaultAllocator(), yojimbo::Address("0.0.0.0"), m_connectionConfig, m_adapter, 0.0)
{
    uint64_t clientId;
    yojimbo::random_bytes((uint8_t*)&clientId, 8);
    m_client.InsecureConnect(DEFAULT_PRIVATE_KEY, clientId, serverAddress);
}

void IsoClient::TEST()
{
    TestMessage* message = (TestMessage*)m_client.CreateMessage((int)GameMessageType::TEST);
    message->m_data = 42;
    m_client.SendMessage((int)GameChannel::RELIABLE, message);
}

void IsoClient::Update(float dt)
{
    // update client
    m_client.AdvanceTime(m_client.GetTime() + dt);
    m_client.ReceivePackets();

    if (m_client.IsConnected())
    {
        ProcessMessages();

        // ... do connected stuff ...


    }

    m_client.SendPackets();
}

void IsoClient::ProcessMessages() {
    for (int i = 0; i < m_connectionConfig.numChannels; i++)
    {
        yojimbo::Message* message = m_client.ReceiveMessage(i);
        while (message != NULL)
        {
            ProcessMessage(message);
            m_client.ReleaseMessage(message);
            message = m_client.ReceiveMessage(i);
        }
    }
}

void IsoClient::ProcessMessage(yojimbo::Message* message)
{
    switch (message->GetType())
    {
        case (int)GameMessageType::TEST:
            ProcessTestMessage((TestMessage*)message);
            break;
        default:
            break;
    }
}

void IsoClient::ProcessTestMessage(TestMessage* message)
{
    std::cout << "Test message received from server with data " << message->m_data << std::endl;
}
