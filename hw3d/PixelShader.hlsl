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

float4 main(float3 color : Color) : SV_TARGET
{
	// Return the interpolated color with full opacity (alpha = 1.0)
	return float4(color, 1.0f);
}
