//
// Created by Matthew Periut on 10/20/21.
//

#pragma once

#include <yojimbo.h>
#include "../IsoAdapter.h"
#include "../TestMessage.h"

class IsoServer
{
public:
    bool m_running = true;
    float m_time = 0.f;


    GameConnectionConfig m_connectionConfig;
    yojimbo::Server m_server;
    IsoAdapter m_adapter;

    IsoServer(const yojimbo::Address &address);

    void Run();
    void ClientConnected(int i);
    void ClientDisconnected(int i);

    void Update(float dt);

    void ProcessMessages();
    void ProcessMessage(int clientIndex, yojimbo::Message *message);
    void ProcessTestMessage(int clientIndex, TestMessage *message);
};