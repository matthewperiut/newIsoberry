//
// Created by Matthew Periut on 10/20/21.
//

#pragma once

#include <yojimbo.h>
#include "../IsoAdapter.h"
#include "../TestMessage.h"

class IsoClient
{
public:
    GameConnectionConfig m_connectionConfig;
    yojimbo::Client m_client;
    IsoAdapter m_adapter;

    explicit IsoClient(const yojimbo::Address& serverAddress);

    void Update(float dt);
    void TEST();
    void ProcessMessages();
    void ProcessMessage(yojimbo::Message *message);
    void ProcessTestMessage(TestMessage *message);
};