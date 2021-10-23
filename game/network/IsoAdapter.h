//
// Created by Matthew Periut on 10/20/21.
//

#pragma once

#include <yojimbo.h>

static const uint8_t DEFAULT_PRIVATE_KEY[yojimbo::KeyBytes] = { 0 };
static const int MAX_PLAYERS = 64;

// a simple test message
enum class GameMessageType {
    TEST,
    COUNT
};

// two channels, one for each type that Yojimbo supports
enum class GameChannel {
    RELIABLE,
    UNRELIABLE,
    COUNT
};

// the client and server config
struct GameConnectionConfig : yojimbo::ClientServerConfig {
    GameConnectionConfig()  {
        numChannels = 2;
        channel[(int)GameChannel::RELIABLE].type = yojimbo::CHANNEL_TYPE_RELIABLE_ORDERED;
        channel[(int)GameChannel::UNRELIABLE].type = yojimbo::CHANNEL_TYPE_UNRELIABLE_UNORDERED;
    }
};

class IsoAdapter : public yojimbo::Adapter
{
public:
    explicit IsoAdapter(void* server = NULL) :
    m_server(server) {}

    yojimbo::MessageFactory* CreateMessageFactory(yojimbo::Allocator& allocator) override;
    void OnServerClientConnected(int clientIndex) override;
    void OnServerClientDisconnected(int clientIndex) override;

private:
    void* m_server;
};