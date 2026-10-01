// Note that semantics starting with "SV" cannot be changed.
// VertexShader.hlsl
// A simple vertex shader that transforms 3D vertex positions by a constant
// matrix and forwards a per-vertex color to the pixel shader.
//
// For beginners:
// - The vertex shader runs once per vertex. Its primary job is to transform
//   vertex positions from model space into clip space using a transformation
//   matrix (here provided via a constant buffer named CBuf).
// - Any additional per-vertex data (like color) can be passed through to the
//   pixel shader by adding fields to the output structure.

cbuffer CBuf
{
    // The shader receives a 4x4 transformation matrix. This can encode
    // rotation, scaling, translation and projection. We transpose the matrix
    // on the CPU side if necessary to match HLSL's expected memory layout.
    matrix transform;
};

// Vertex shader entry point. Accepts a position (float3), then
// outputs a transformed position
float4 main( float3 pos : Position) : SV_Position
{
    // Here we return the homogeneus coordinates
    return mul(float4(pos, 1.0f), transform);
}
