// A colour is represnted as 4D (RGB and Alpha)
// PixelShader.hlsl
// Very small fragment (pixel) shader used by the tutorial. It receives an
// interpolated color from the vertex shader and returns it as the final
// pixel color.
//
// For beginners:
// - The pixel shader runs once per pixel that the rasterizer determines is
//   covered by a triangle.
// - Inputs to the pixel shader are interpolated across the primitive by the
//   GPU automatically (so per-vertex colors produce smooth gradients).

// Add buffer for color faces
cbuffer cbuf
{
    float4 face_colors[6];
};

// Since we no longer need color input (the buffer handles it now), we instead pass in triangleID
// We divide by 2 because there are 2 triangles on every face on the cube
float4 main(uint triangleID : SV_PrimitiveID) : SV_TARGET
{
    return face_colors[triangleID / 2];
}
