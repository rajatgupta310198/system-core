/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef IGATEKEEPER_SERVICE_H_
#define IGATEKEEPER_SERVICE_H_

#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace android {

/*
 * This must be kept manually in sync with frameworks/base's IGateKeeperService.aidl
 */
class IGateKeeperService : public IInterface {
public:
    enum {
        ENROLL = IBinder::FIRST_CALL_TRANSACTION + 0,
        VERIFY = IBinder::FIRST_CALL_TRANSACTION + 1,
    };

    // DECLARE_META_INTERFACE - C++ client interface not needed
    static const android::String16 descriptor;
    virtual const android::String16& getInterfaceDescriptor() const;
    IGateKeeperService() {}
    virtual ~IGateKeeperService() {}

    /**
     * Enrolls a password with the GateKeeper. Returns 0 on success, negative on failure.
     */
    virtual status_t enroll(uint32_t uid,
            const uint8_t *current_password_handle, uint32_t current_password_handle_length,
            const uint8_t *current_password, uint32_t current_password_length,
            const uint8_t *desired_password, uint32_t desired_password_length,
            uint8_t **enrolled_password_handle, uint32_t *enrolled_password_handle_length) = 0;

    /**
     * Verifies a password previously enrolled with the GateKeeper.
     * Returns 0 on success, negative on failure.
     */
    virtual status_t verify(uint32_t uid,
            const uint8_t *enrolled_password_handle, uint32_t enrolled_password_handle_length,
            const uint8_t *provided_password, uint32_t provided_password_length) = 0;
};

// ----------------------------------------------------------------------------

class BnGateKeeperService: public BnInterface<IGateKeeperService> {
public:
    virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply,
            uint32_t flags = 0);
};

} // namespace android

#endif

