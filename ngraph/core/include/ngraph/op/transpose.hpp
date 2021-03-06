//*****************************************************************************
// Copyright 2017-2021 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************

#pragma once

#include "ngraph/axis_vector.hpp"
#include "ngraph/node.hpp"
#include "ngraph/op/op.hpp"

namespace ngraph
{
    namespace op
    {
        namespace v1
        {
            /// \brief Tensor transpose operation.
            class NGRAPH_API Transpose : public Op
            {
            public:
                NGRAPH_RTTI_DECLARATION;

                Transpose() = default;
                ///
                /// \brief      Constructs a transpose operation.
                ///
                /// \param      arg          Node producing the tensor to be transposed.
                /// \param      input_order  Node producing the permutation to apply to the axes
                ///                          of the input shape. Must be a vector with shape [n],
                ///                          where n is the rank of arg. The tensor's value must
                ///                          contain every integer in the range [0, n-1].
                ///
                Transpose(const Output<Node>& arg, const Output<Node>& input_order);

                bool visit_attributes(AttributeVisitor& visitor) override;
                void validate_and_infer_types() override;

                virtual std::shared_ptr<Node>
                    clone_with_new_inputs(const OutputVector& new_args) const override;

                bool evaluate(const HostTensorVector& outputs,
                              const HostTensorVector& inputs) const override;
            };
        }
        using v1::Transpose;
    }
}
