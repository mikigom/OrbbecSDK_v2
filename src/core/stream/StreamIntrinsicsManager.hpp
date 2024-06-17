#pragma once

#include "openobsdk/h/ObTypes.h"
#include "StreamProfile.hpp"
#include <map>
#include <memory>
#include <vector>
#include <mutex>


namespace libobsensor {

class StreamIntrinsicsManager {
private:
    StreamIntrinsicsManager();

    static std::mutex                             instanceMutex_;
    static std::weak_ptr<StreamIntrinsicsManager> instanceWeakPtr_;

public:
    static std::shared_ptr<StreamIntrinsicsManager> getInstance();

    ~StreamIntrinsicsManager() noexcept;

    void               registerVideoStreamIntrinsics(const std::shared_ptr<const StreamProfile>& profile, const OBCameraIntrinsic &intrinsics);
    OBCameraIntrinsic  getVideoStreamIntrinsics(const std::shared_ptr<const StreamProfile>& profile);
    void               registerVideoStreamDistortion(const std::shared_ptr<const StreamProfile>& profile, const OBCameraDistortion &distortion);
    OBCameraDistortion getVideoStreamDistortion(const std::shared_ptr<const StreamProfile>& profile);
    void               registerGyroStreamIntrinsics(const std::shared_ptr<const StreamProfile>& profile, const OBGyroIntrinsic &intrinsics);
    OBGyroIntrinsic    getGyroStreamIntrinsics(const std::shared_ptr<const StreamProfile>& profile);
    void               registerAccelStreamIntrinsics(const std::shared_ptr<const StreamProfile>& profile, const OBAccelIntrinsic &intrinsics);
    OBAccelIntrinsic   getAccelStreamIntrinsics(const std::shared_ptr<const StreamProfile>& profile);

private:
    std::mutex mutex_;

    std::map<std::weak_ptr<const StreamProfile>, OBCameraIntrinsic, StreamProfileWeakPtrCompare>  videoStreamIntrinsics_;
    std::map<std::weak_ptr<const StreamProfile>, OBCameraDistortion, StreamProfileWeakPtrCompare> videoStreamDistortion_;
    std::map<std::weak_ptr<const StreamProfile>, OBGyroIntrinsic, StreamProfileWeakPtrCompare>    gyroStreamIntrinsics_;
    std::map<std::weak_ptr<const StreamProfile>, OBAccelIntrinsic, StreamProfileWeakPtrCompare>   accelStreamIntrinsics_;

    std::shared_ptr<Logger> logger_;  // Manages the lifecycle of the logger object.
};

}  // namespace libobsensor