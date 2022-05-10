/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <XR/XRFactory.h>

#include <OpenXRVk_Platform.h>
#include <OpenXRVk/OpenXRVkDevice.h>
#include <OpenXRVk/OpenXRVkInstance.h>
#include <OpenXRVk/OpenXRVkPhysicalDevice.h>
#include <OpenXRVk/OpenXRVkSession.h>
#include <OpenXRVk/OpenXRVkInput.h>
#include <OpenXRVk/OpenXRVkSwapChain.h>
#include <OpenXRVk/OpenXRVkGraphicsBinding.h>

namespace OpenXRVk
{
    //! Interface responsible for creating all the XR objects which are
    //! internally backed by concrete objects
    class Factory final
        : public XR::Factory
    {
    public:
        AZ_CLASS_ALLOCATOR(Factory, AZ::SystemAllocator, 0);
        AZ_RTTI(Factory, "{11C46EF4-2AB5-47F7-B4F6-D30DDD53F1D8}", XR::Factory);

        Factory();
        ~Factory();

        // Create XR::Instance object
        AZStd::intrusive_ptr<XR::Instance> CreateInstance() override;

        // Create XR::Device object
        AZStd::intrusive_ptr<XR::Device> CreateDevice() override;

        // Return a list of XR::PhysicalDevice
        AZStd::vector<AZStd::intrusive_ptr<XR::PhysicalDevice>> EnumerateDeviceList() override;

        // Create XR::Session object
        AZStd::intrusive_ptr<XR::Session> CreateSession() override;

        // Create XR::Input object
        AZStd::intrusive_ptr<XR::Input> CreateInput() override;

        // Create XR::SwapChain object
        AZStd::intrusive_ptr<XR::SwapChain> CreateSwapchain() override;

        // Create XR::ViewSwapChain object
        AZStd::intrusive_ptr<XR::SwapChain::View> CreateViewSwapchain() override;

        // Create RPI::XR::GraphicsBindingDescriptor that will contain
        // renderer information needed to start a session
        AZStd::intrusive_ptr<XR::GraphicsBindingDescriptor> CreateGraphicsBindingDescriptor() override;

    };
}
