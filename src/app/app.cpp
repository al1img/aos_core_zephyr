/*
 * Copyright (C) 2023 Renesas Electronics Corporation.
 * Copyright (C) 2023 EPAM Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "app.hpp"
#include "log.hpp"

/***********************************************************************************************************************
 * Variables
 **********************************************************************************************************************/

App App::sApp;

/***********************************************************************************************************************
 * Static
 **********************************************************************************************************************/

void PrintCSR(const char* csr)
{
    auto        len = strlen(csr);
    const char* p   = csr;
    char        buffer[257];

    while (p < csr + len) {
        printk("%s", strncpy(buffer, p, sizeof(buffer) - 1));
        p += sizeof(buffer) - 1;
    }
}

/***********************************************************************************************************************
 * Public
 **********************************************************************************************************************/

aos::Error App::Init()
{
    LOG_INF() << "Initialize application";

    aos::Error err;

    if (!(err = mStorage.Init()).IsNone()) {
        return err;
    }

    if (!(err = mRunner.Init(mLauncher)).IsNone()) {
        return err;
    }

    if (!(err = mDownloader.Init(mCommunication)).IsNone()) {
        return err;
    }

    if (!(err = mServiceManager.Init(mJsonOciSpec, mDownloader, mStorage)).IsNone()) {
        return err;
    }

    if (!(err = mResourceUsageProvider.Init()).IsNone()) {
        return err;
    }
    /*
        if (!(err = mResourceMonitor.Init(mResourceUsageProvider, mCommunication, mCommunication)).IsNone()) {
            return err;
        }

        if (!(err = mLauncher.Init(
                  mServiceManager, mRunner, mJsonOciSpec, mCommunication, mStorage, mResourceMonitor, mCommunication))
                 .IsNone()) {
            return err;
        }

        if (!(err = mCommOpenChannel.Init(VChannel::cXSOpenReadPath, VChannel::cXSOpenWritePath)).IsNone()) {
            return err;
        }

        if (!(err = mCommSecureChannel.Init(VChannel::cXSCloseReadPath, VChannel::cXSCloseWritePath)).IsNone()) {
            return err;
        }

        if (!(err = mClockSync.Init(mCommunication)).IsNone()) {
            return err;
        }

        if (!(err = mProvisioning.Init()).IsNone()) {
            return err;
        }
    */
    if (!(err = mCryptoProvider.Init()).IsNone()) {
        return err;
    }

    if (!(err = InitCertHandler()).IsNone()) {
        return err;
    }
    /*
        if (!(err = mCommunication.Init(mCommOpenChannel, mCommSecureChannel, mLauncher, mCertHandler, mResourceManager,
                  mResourceMonitor, mDownloader, mClockSync, mProvisioning))
                 .IsNone()) {
            return err;
        }
    */
    return aos::ErrorEnum::eNone;
}

aos::Error App::TestCertHandler()
{
    auto err = mCertHandler.Clear("sm");
    if (!err.IsNone()) {
        return err;
    }

    err = mCertHandler.SetOwner("sm", "12345");
    if (!err.IsNone()) {
        return err;
    }

    err = mCertHandler.CreateKey("sm", "test", "12345", mCSR);
    if (!err.IsNone()) {
        return err;
    }

    PrintCSR(mCSR.CStr());

    return aos::ErrorEnum::eNone;
}

/***********************************************************************************************************************
 * Private
 **********************************************************************************************************************/

aos::Error App::InitCertHandler()
{
    aos::Error                              err;
    aos::iam::certhandler::ExtendedKeyUsage keyUsage[] = {aos::iam::certhandler::ExtendedKeyUsageEnum::eClientAuth,
        aos::iam::certhandler::ExtendedKeyUsageEnum::eServerAuth};

    // Register iam cert module

    if (!(err = mIAMHSMModule.Init("iam", {cPKCS11ModuleLibrary, {}, {}, cPKCS11ModuleTokenLabel, cPKCS11ModulePinFile},
              mPKCS11Manager, mCryptoProvider))
             .IsNone()) {
        return err;
    }

    if (!(err = mIAMCertModule.Init("iam",
              {aos::crypto::KeyTypeEnum::eECDSA, 1, aos::Array<aos::iam::certhandler::ExtendedKeyUsage>(keyUsage, 2)},
              mCryptoProvider, mIAMHSMModule, mStorage))
             .IsNone()) {
        return err;
    }

    if (!(err = mCertHandler.RegisterModule(mIAMCertModule)).IsNone()) {
        return err;
    }

    // Register sm cert module

    if (!(err = mSMHSMModule.Init("sm", {cPKCS11ModuleLibrary, {}, {}, cPKCS11ModuleTokenLabel, cPKCS11ModulePinFile},
              mPKCS11Manager, mCryptoProvider))
             .IsNone()) {
        return err;
    }

    if (!(err = mSMCertModule.Init("sm",
              {aos::crypto::KeyTypeEnum::eECDSA, 1, aos::Array<aos::iam::certhandler::ExtendedKeyUsage>(keyUsage, 2)},
              mCryptoProvider, mSMHSMModule, mStorage))
             .IsNone()) {
        return err;
    }

    if (!(err = mCertHandler.RegisterModule(mSMCertModule)).IsNone()) {
        return err;
    }

    return aos::ErrorEnum::eNone;
}
