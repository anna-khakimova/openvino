// Copyright (C) 2018-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <ie_common.h>
#include <mkldnn_node.h>
#include <string>
#include <memory>
#include <vector>
#include <nodes/common/softmax.h>

namespace MKLDNNPlugin {

struct jit_args_logistic {
    const void* src;
    void* dst;
    size_t work_amount;
};

struct jit_logistic_config_params {
    InferenceEngine::Precision src_dt;
    InferenceEngine::Precision dst_dt;
    unsigned src_data_size = 0;
    unsigned dst_data_size = 0;
};

struct jit_uni_logistic_kernel {
    void (*ker_)(const jit_args_logistic *);

    void operator()(const jit_args_logistic *args) { assert(ker_); ker_(args); }

    virtual void create_ker() = 0;

    jit_uni_logistic_kernel() : ker_(nullptr) {}
    virtual ~jit_uni_logistic_kernel() {}
};

class MKLDNNRegionYoloNode : public MKLDNNNode {
public:
    MKLDNNRegionYoloNode(const std::shared_ptr<ngraph::Node>& op, const mkldnn::engine& eng, MKLDNNWeightsSharing::Ptr &cache);

    void getSupportedDescriptors() override {};
    void initSupportedPrimitiveDescriptors() override;
    void createPrimitive() override;
    void execute(mkldnn::stream strm) override;
    bool created() const override;

    static bool isSupportedOperation(const std::shared_ptr<ngraph::Node>& op, std::string& errorMessage) noexcept;

private:
    int classes;
    int coords;
    int num;
    float do_softmax;
    std::vector<int64_t> mask;
    InferenceEngine::Precision input_prec, output_prec;

    std::string errorPrefix;

    int block_size;
    std::shared_ptr<jit_uni_logistic_kernel> logistic_kernel;
    std::shared_ptr<SoftmaxGeneric> softmax_kernel;

    union U {
        float as_float_value;
        int as_int_value;
    };

    inline float logistic_scalar(float src);
    inline void calculate_logistic(size_t start_index, int count, uint8_t * dst_data);
};

}  // namespace MKLDNNPlugin