## Sqrt <a name="Sqrt"></a> {#openvino_docs_ops_arithmetic_Sqrt_1}

**Versioned name**: *Sqrt-1*

**Category**: Arithmetic unary operation 

**Short description**: *Sqrt* performs element-wise square root operation with given tensor.

**Attributes**:

    No attributes available.

**Inputs**

* **1**: An tensor of type T. **Required.**

**Outputs**

* **1**: The result of element-wise sqrt operation. A tensor of type T.

**Types**

* *T*: any numeric type.

*Sqrt* does the following with the input tensor *a*:

\f[
a_{i} = sqrt(a_{i})
\f]

**Examples**

*Example 1*

```xml
<layer ... type="Sqrt">
    <input>
        <port id="0">
            <dim>256</dim>
            <dim>56</dim>
        </port>
    </input>
    <output>
        <port id="1">
            <dim>256</dim>
            <dim>56</dim>
        </port>
    </output>
</layer>
```