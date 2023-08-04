/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Math/MatrixMxN.h>
#include <MachineLearning/INeuralNetwork.h>
#include <Models/Layer.h>
#include <AzCore/Asset/AssetCommon.h>

namespace MachineLearning
{
    //! This is a basic multilayer perceptron neural network capable of basic training and feed forward operations.
    class MultilayerPerceptron
        : public INeuralNetwork
        , public AZ::Data::AssetData
    {
    public:

        AZ_CLASS_ALLOCATOR(MultilayerPerceptron, AZ::SystemAllocator);
        AZ_RTTI(MultilayerPerceptron, "{E12EF761-41A5-48C3-BF55-7179B280D45F}", AZ::Data::AssetData, INeuralNetwork);

        //! AzCore Reflection.
        //! @param context reflection context
        static void Reflect(AZ::ReflectContext* context);

        MultilayerPerceptron() = default;
        MultilayerPerceptron(AZStd::size_t activationCount);
        virtual ~MultilayerPerceptron() = default;

        //! INeuralNetwork interface
        //! @{
        void AddLayer(AZStd::size_t layerDimensionality, ActivationFunctions activationFunction = ActivationFunctions::Linear) override;
        AZStd::size_t GetLayerCount() const override;
        Layer& GetLayer(AZStd::size_t layerIndex) override;
        AZStd::size_t GetParameterCount() const override;
        const AZ::VectorN& Forward(const AZ::VectorN& activations) override;
        void Reverse(LossFunctions lossFunction, const AZ::VectorN& activations, const AZ::VectorN& expected) override;
        void GradientDescent(float learningRate) override;
        //! @}

    private:

        void OnActivationCountChanged();

        //! The number of neurons in the activation layer.
        AZStd::size_t m_activationCount = 0;

        //! The set of layers in the network.
        AZStd::vector<Layer> m_layers;
    };
}
