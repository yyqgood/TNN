// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "onnx_utils.h"

#include <algorithm>

namespace TNN_CONVERTER {

TNN_NS::DimsVector ConvertTensorShapeProtoToDimsVector(onnx::TensorShapeProto tensor_shape_proto) {
    TNN_NS::DimsVector dims_vector;
    int dim_size = tensor_shape_proto.dim_size();
    for (int i = 0; i < dim_size; ++i) {
        int dim = std::max(1, (int)tensor_shape_proto.dim(i).dim_value());
        dims_vector.push_back(dim);
    }
    return dims_vector;
}

onnx::AttributeProto_AttributeType GetAttributeType(const char *type_name) {
    if (type_name == typeid(int64_t).name()) {
        return onnx::AttributeProto_AttributeType_INT;
    } else if (type_name == typeid(int64_t[]).name()) {
        return onnx::AttributeProto_AttributeType_INTS;
    } else if (type_name == typeid(float).name()) {
        return onnx::AttributeProto_AttributeType_FLOAT;
    } else if (type_name == typeid(float[]).name()) {
        return onnx::AttributeProto_AttributeType_FLOATS;
    } else if (type_name == typeid(std::string).name()) {
        return onnx::AttributeProto_AttributeType_STRING;
    } else if (type_name == typeid(std::string[]).name()) {
        return onnx::AttributeProto_AttributeType_STRINGS;
    } else if (type_name == typeid(onnx::TensorProto).name()) {
        return onnx::AttributeProto_AttributeType_TENSOR;
    } else if (type_name == typeid(onnx::TensorProto[]).name()) {
        return onnx::AttributeProto_AttributeType_TENSORS;
    } else if (type_name == typeid(onnx::GraphProto).name()) {
        return onnx::AttributeProto_AttributeType_GRAPH;
    } else if (type_name == typeid(onnx::GraphProto[]).name()) {
        return onnx::AttributeProto_AttributeType_GRAPHS;
    } else {
        return onnx::AttributeProto_AttributeType_UNDEFINED;
    }
}
int GetAttributeInt(const onnx::NodeProto &node, const std::string &name, int64_t default_value) {
    for (const auto &iter : node.attribute()) {
        if (iter.name() != name) {
            continue;
        }
        assert(iter.type() == onnx::AttributeProto_AttributeType_INT);
        return iter.i();
    }
    return default_value;
}

std::vector<int64_t> GetAttributeIntVector(const onnx::NodeProto &node, const std::string &name) {
    std::vector<int64_t> attributes;
    for (const auto &iter : node.attribute()) {
        if (iter.name() != name) {
            continue;
        }
        assert(iter.type() == onnx::AttributeProto_AttributeType_INTS);
        for (const auto &value : iter.ints()) {
            attributes.push_back(value);
        }
    }
    return attributes;
}

float GetAttributeFloat(const onnx::NodeProto &node, const std::string &name, float default_value) {
    for (const auto &iter : node.attribute()) {
        if (iter.name() != name) {
            continue;
        }
        assert(iter.type() == onnx::AttributeProto_AttributeType_INT);
        return iter.f();
    }
    return default_value;
}
}  // namespace TNN_CONVERTER