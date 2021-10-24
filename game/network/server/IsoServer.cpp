//
// Created by Matthew Periut on 10/20/21.
//

#include <stdexcept>
#include <iostream>
#include <string>
#include "IsoServer.h"
#include "../TestMessage.h"

IsoServer::IsoServer(const yojimbo::Address& address) :
        m_adapter(this),
        m_server(yojimbo::GetDefaultAllocator(), DEFAULT_PRIVATE_KEY, address, m_connectionConfig, m_adapter, 0.0)
{
    // start the server
    m_server.Start(MAX_PLAYERS);
    if (!m_server.IsRunning())
    {
        throw std::runtime_error("Could not start server at port " + std::to_string(address.GetPort()));
    }

    // print the port we got in case we used port 0
    char buffer[256];
    m_server.GetAddress().ToString(buffer, sizeof(buffer));
    std::cout << "Server address is " << buffer << std::endl;

    // ... load game ...
}

void IsoServer::Run()
{
    float fixedDt = 1.0f / 60.0f;
    while (m_running) {
        double currentTime = yojimbo_time();
        if (m_time <= currentTime) {
            Update(fixedDt);
            m_time += fixedDt;
        } else {
            yojimbo_sleep(m_time - currentTime);
        }
    }
}

void IsoServer::Update(float dt)
{
    // stop if server is not running
    if (!m_server.IsRunning())
    {
        m_running = false;
        return;
    }

    // update server and process messages
    m_server.AdvanceTime(m_time);
    m_server.ReceivePackets();
    ProcessMessages();

    // ... process client inputs ...
    // ... update game ...
    // ... send game state to clients ...

    m_server.SendPackets();
}

void IsoServer::ProcessMessages() {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (m_server.IsClientConnected(i)) {
            for (int j = 0; j < m_connectionConfig.numChannels; j++) {
                yojimbo::Message* message = m_server.ReceiveMessage(i, j);
                while (message != NULL) {
                    ProcessMessage(i, message);
                    m_server.ReleaseMessage(i, message);
                    message = m_server.ReceiveMessage(i, j);
                }
            }
        }
    }
}

void IsoServer::ProcessMessage(int clientIndex, yojimbo::Message* message) {
    switch (message->GetType()) {
        case (int)GameMessageType::TEST:
            ProcessTestMessage(clientIndex, (TestMessage*)message);
            break;
        default:
            break;
    }
}

void IsoServer::ProcessTestMessage(int clientIndex, TestMessage* message)
{
    std::cout << "Test message received from client " << clientIndex << " with data " << message->m_data << std::endl;
    TestMessage* testMessage = (TestMessage*)m_server.CreateMessage(clientIndex, (int)GameMessageType::TEST);
    testMessage->m_data = message->m_data;
    m_server.SendMessage(clientIndex, (int)GameChannel::RELIABLE, testMessage);
}

void IsoServer::ClientConnected(int i)
{

}

void IsoServer::ClientDisconnected(int i)
{

}
