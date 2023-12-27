/*
 * Copyright (C) 2023 Renesas Electronics Corporation.
 * Copyright (C) 2023 EPAM Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CMCLIENT_HPP_
#define CMCLIENT_HPP_

#include <aos/sm/launcher.hpp>

#include <proto/servicemanager/v3/servicemanager.pb.h>

#include "downloader/downloader.hpp"
#include "resourcemanager/resourcemanager.hpp"

#include "messagesender.hpp"

/**
 * CM client instance.
 */
class CMClient {
public:
    /**
     * Creates CM client.
     */
    CMClient() = default;

    /**
     * Initializes CM client instance.
     *
     * @param launcher launcher instance.
     * @param resourceManager resource manager instance.
     * @param downloader downloader instance.
     * @param messageSender message sender instance.
     * @return aos::Error.
     */
    aos::Error Init(aos::sm::launcher::LauncherItf& launcher, ResourceManagerItf& resourceManager,
        DownloadReceiverItf& downloader, MessageSenderItf& messageSender);

    /**
     * Processes received message.
     *
     * @param methodName protocol method name.
     * @param requestID protocol request ID.
     * @param data raw message data.
     * @return aos::Error.
     */
    aos::Error ProcessMessage(const aos::String& methodName, uint64_t requestID, const aos::Array<uint8_t>& data);

    /**
     * Returns pointer for receive buffer.
     *
     * @return void*.
     */
    void* GetReceiveBuffer() const { return mReceiveBuffer.Get(); }

    /**
     * Returns receive buffer size.
     *
     * @return size_t
     */
    size_t GetReceiveBufferSize() const { return mReceiveBuffer.Size(); }

private:
    aos::Error ProcessGetUnitConfigStatus();
    aos::Error ProcessCheckUnitConfig(const servicemanager_v3_CheckUnitConfig& pbUnitConfig);
    aos::Error ProcessSetUnitConfig(const servicemanager_v3_SetUnitConfig& pbUnitConfig);
    aos::Error ProcessRunInstances(const servicemanager_v3_RunInstances& pbRunInstances);
    aos::Error ProcessImageContentInfo(const servicemanager_v3_ImageContentInfo& pbContentInfo);
    aos::Error ProcessImageContent(const servicemanager_v3_ImageContent& pbContent);
    aos::Error SendOutgoingMessage(
        const servicemanager_v3_SMOutgoingMessages& message, aos::Error messageError = aos::ErrorEnum::eNone);

    aos::sm::launcher::LauncherItf* mLauncher {};
    ResourceManagerItf*             mResourceManager {};
    DownloadReceiverItf*            mDownloader {};
    MessageSenderItf*               mMessageSender {};

    aos::StaticAllocator<sizeof(servicemanager_v3_SMIncomingMessages) + sizeof(servicemanager_v3_SMOutgoingMessages)
        + aos::Max(sizeof(aos::ServiceInfoStaticArray) + sizeof(aos::LayerInfoStaticArray)
                + sizeof(aos::InstanceInfoStaticArray),
            sizeof(ImageContentInfo) + sizeof(FileChunk))>
        mAllocator;

    aos::StaticBuffer<servicemanager_v3_SMIncomingMessages_size> mReceiveBuffer;
    aos::StaticBuffer<servicemanager_v3_SMOutgoingMessages_size> mSendBuffer;
};

#endif
