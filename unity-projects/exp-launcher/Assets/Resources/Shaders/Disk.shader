// Pcx - Point cloud importer & renderer for Unity
// https://github.com/keijiro/Pcx

Shader "Point Cloud/Disk"
{
	Properties
	{
		_Tint("Tint", Color) = (0.5, 0.5, 0.5, 1)
		_PointSize("Point Size", Float) = 0.05
		_Circles("Circle", Range(0, 1)) = 0
		_Details("DetailLevel", Int) = 2
	}

	SubShader
	{
		Tags{ "RenderType" = "Opaque" }
		ZWrite On
		LOD 200

		Cull Off
		Pass{
			Tags{ "LightMode" = "ForwardBase" }
			CGPROGRAM
			#pragma vertex Vertex
			#pragma geometry Geometry
			#pragma fragment Fragment
			#include "Disk2.cginc"
			ENDCG
		}
	}
	CustomEditor "Pcx.DiskMaterialInspector"
}


//Blend SrcFactor DstFactor : Configure and enable blending.The generated color is multiplied by the SrcFactor.The color already on screen is multiplied by DstFactor and the two are added together.
// SrcAlpha 	The value of this stage is multiplied by the source alpha value.
// OneMinusDstAlpha 	The value of this stage is multiplied by (1 - destination alpha).
//Blend SrcAlpha OneMinusSrcAlpha



//// Pcx - Point cloud importer & renderer for Unity
//// https://github.com/keijiro/Pcx
//
//Shader "Point Cloud/Disk"
//{
//	Properties
//	{
//		_Tint("Tint", Color) = (0.5, 0.5, 0.5, 1)
//		_PointSize("Point Size", Float) = 0.05
//	}
//		SubShader
//	{
//		//Tags{ "RenderType" = "Opaque" }
//		Tags{ "Queue" = "Transparent" "RenderType" = "Transparent" }
//		ZWrite On
//		Blend SrcAlpha OneMinusSrcAlpha
//		Cull Off
//		Pass
//	{
//		Tags{ "LightMode" = "ForwardBase" }
//		CGPROGRAM
//#pragma vertex Vertex
//#pragma geometry Geometry
//#pragma fragment Fragment
//#pragma multi_compile_fog
//#pragma multi_compile _ UNITY_COLORSPACE_GAMMA
//#pragma multi_compile _ _COMPUTE_BUFFER
//#include "Disk.cginc"
//		ENDCG
//	}
//		Pass
//	{
//		Tags{ "LightMode" = "ShadowCaster" }
//		CGPROGRAM
//#pragma vertex Vertex
//#pragma geometry Geometry
//#pragma fragment Fragment
//#pragma multi_compile _ _COMPUTE_BUFFER
//#define PCX_SHADOW_CASTER 1
//#include "Disk.cginc"
//		ENDCG
//	}
//	}
//		CustomEditor "Pcx.DiskMaterialInspector"
//}
