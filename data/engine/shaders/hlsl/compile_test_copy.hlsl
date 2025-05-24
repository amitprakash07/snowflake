/*
This is a test shader to see the compilation of HLSL code using DXC works.
It is not intended to be used in any real application.
*/

[numthreads(1, 1, 1)]
void test_dxc_compilation_cs(
    uint3 dispatchThreadID : SV_DispatchThreadID,
    uint3 groupThreadID : SV_GroupThreadID,
    uint3 groupID : SV_GroupID)
{
    // This is a test shader for DXC compilation
}
