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

#include <cmath>
#include "ngraph/coordinate_transform.hpp"
#include "ngraph/runtime/reference/max.hpp"
#include "ngraph/runtime/reference/sum.hpp"
#include "ngraph/shape_util.hpp"

namespace ngraph
{
    namespace runtime
    {
        namespace reference
        {
            template <typename T>
            void log_softmax(const T* arg, T* out, const Shape& shape, const AxisSet& axes)
            {
                auto temp_shape = reduce(shape, axes, true);
                auto temp_elements = shape_size(temp_shape);
                auto temp_max = std::vector<T>(temp_elements, 0);
                auto temp_sum = std::vector<T>(temp_elements, 0);

                max(arg, temp_max.data(), shape, axes, true);

                CoordinateTransform transform(shape);
                CoordinateTransform temp_transform(temp_shape);
                for (const Coordinate& coord : transform)
                {
                    Coordinate temp_coord = reduce(coord, axes, true);
                    out[transform.index(coord)] = std::exp(
                        arg[transform.index(coord)] - temp_max[temp_transform.index(temp_coord)]);
                }

                sum(out, temp_sum.data(), shape, axes, true);

                for (const Coordinate& coord : transform)
                {
                    Coordinate temp_coord = reduce(coord, axes, true);
                    out[transform.index(coord)] =
                        (arg[transform.index(coord)] - temp_max[temp_transform.index(temp_coord)]) -
                        std::log(temp_sum[temp_transform.index(temp_coord)]);
                }
            }
        } // namespace reference
    }     // namespace runtime
} // namespace ngraph
