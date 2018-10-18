xof 0303txt 0032
//
// DirectX file: F:\Modelling - conversions\sceneassets\images\square.x
//
// Converted by the PolyTrans geometry converter from Okino Computer Graphics, Inc.
// Date/time of export: 10/09/2008 19:40:31
//
// Bounding box of geometry = (-0.5,0,-0.5) to (0.5,0,0.5).


template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
  <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
  <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
  <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
  <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template FrameTransformMatrix {
 <F6F23F41-7686-11cf-8F52-0040333594A3>
 Matrix4x4 frameMatrix;
}

template Frame {
 <3D82AB46-62DA-11cf-AB39-0020AF71E433>
 [...]
}

template FloatKeys {
 <10DD46A9-775B-11cf-8F52-0040333594A3>
 DWORD nValues;
 array FLOAT values[nValues];
}

template TimedFloatKeys {
 <F406B180-7B3B-11cf-8F52-0040333594A3>
 DWORD time;
 FloatKeys tfkeys;
}

template AnimationKey {
 <10DD46A8-775B-11cf-8F52-0040333594A3>
 DWORD keyType;
 DWORD nKeys;
 array TimedFloatKeys keys[nKeys];
}

template AnimationOptions {
 <E2BF56C0-840F-11cf-8F52-0040333594A3>
 DWORD openclosed;
 DWORD positionquality;
}

template Animation {
 <3D82AB4F-62DA-11cf-AB39-0020AF71E433>
 [...]
}

template AnimationSet {
 <3D82AB50-62DA-11cf-AB39-0020AF71E433>
 [Animation]
}

template XSkinMeshHeader {
 <3CF169CE-FF7C-44ab-93C0-F78F62D172E2>
 WORD nMaxSkinWeightsPerVertex; 
 WORD nMaxSkinWeightsPerFace; 
 WORD nBones; 
}

template VertexDuplicationIndices {
 <B8D65549-D7C9-4995-89CF-53A9A8B031E3>
 DWORD nIndices; 
 DWORD nOriginalVertices; 
 array DWORD indices[nIndices]; 
}

template SkinWeights {
 <6F0D123B-BAD2-4167-A0D0-80224F25FABB>
 STRING transformNodeName;
 DWORD nWeights; 
 array DWORD vertexIndices[nWeights]; 
 array float weights[nWeights]; 
 Matrix4x4 matrixOffset; 
}

template FVFData {
 <b6e70a0e-8ef9-4e83-94ad-ecc8b0c04897>
 DWORD dwFVF; 
 DWORD nDWords; 
 array DWORD data[nDWords]; 
}

template EffectInstance {
 <e331f7e4-0559-4cc2-8e99-1cec1657928f>
 STRING EffectFilename; 
 [...] 
}

template EffectParamFloats {
 <3014b9a0-62f5-478c-9b86-e4ac9f4e418b>
 STRING ParamName; 
 DWORD nFloats; 
 array FLOAT Floats[nFloats]; 
}

template EffectParamString {
 <1dbc4c88-94c1-46ee-9076-2c28818c9481>
 STRING ParamName; 
 STRING Value; 
}

template EffectParamDWord {
 <e13963bc-ae51-4c5d-b00f-cfa3a9d97ce5>
 STRING ParamName; 
 DWORD Value; 
}

Header {
	1; // Major version
	0; // Minor version
	1; // Flags
}

Material xof_default {
	0.400000;0.400000;0.400000;1.000000;;
	32.000000;
	0.700000;0.700000;0.700000;;
	0.000000;0.000000;0.000000;;
}

Material n_01___Default {
	1.0;1.0;1.0;1.000000;;
	3.000000;
	0.000000;0.000000;0.000000;;
	0.000000;0.000000;0.000000;;
	TextureFilename {
		"red.png";
	}
}

// Top-most frame encompassing the 'World'
Frame Frame_World {
	FrameTransformMatrix {
		1.000000, 0.0, 0.0, 0.0, 
		0.0, 1.000000, 0.0, 0.0, 
		0.0, 0.0, -1.000000, 0.0, 
		0.0, 0.0, 0.0, 1.000000;;
	}

Frame Frame_Plane02 {
	FrameTransformMatrix {
		1.000000, 0.0, 0.0, 0.0, 
		0.0, 1.000000, 0.0, 0.0, 
		0.0, 0.0, 1.000000, 0.0, 
		0.0, 0.0, 0.0, 1.000000;;
	}

// Original object name = "Plane02"
Mesh Plane02 {
	25;		// 25 vertices
	-0.500000;0.000000;0.500000;,
	-0.250000;0.000000;0.500000;,
	0.000000;0.000000;0.500000;,
	0.250000;0.000000;0.500000;,
	0.500000;0.000000;0.500000;,
	-0.500000;0.000000;0.250000;,
	-0.250000;0.000000;0.250000;,
	0.000000;0.000000;0.250000;,
	0.250000;0.000000;0.250000;,
	0.500000;0.000000;0.250000;,
	-0.500000;0.000000;0.000000;,
	-0.250000;0.000000;0.000000;,
	0.000000;0.000000;0.000000;,
	0.250000;0.000000;0.000000;,
	0.500000;0.000000;0.000000;,
	-0.500000;0.000000;-0.250000;,
	-0.250000;0.000000;-0.250000;,
	0.000000;0.000000;-0.250000;,
	0.250000;0.000000;-0.250000;,
	0.500000;0.000000;-0.250000;,
	-0.500000;0.000000;-0.500000;,
	-0.250000;0.000000;-0.500000;,
	0.000000;0.000000;-0.500000;,
	0.250000;0.000000;-0.500000;,
	0.500000;0.000000;-0.500000;;

	32;		// 32 faces
	3;6,0,5;,
	3;0,6,1;,
	3;7,1,6;,
	3;1,7,2;,
	3;8,2,7;,
	3;2,8,3;,
	3;9,3,8;,
	3;3,9,4;,
	3;11,5,10;,
	3;5,11,6;,
	3;12,6,11;,
	3;6,12,7;,
	3;13,7,12;,
	3;7,13,8;,
	3;14,8,13;,
	3;8,14,9;,
	3;16,10,15;,
	3;10,16,11;,
	3;17,11,16;,
	3;11,17,12;,
	3;18,12,17;,
	3;12,18,13;,
	3;19,13,18;,
	3;13,19,14;,
	3;21,15,20;,
	3;15,21,16;,
	3;22,16,21;,
	3;16,22,17;,
	3;23,17,22;,
	3;17,23,18;,
	3;24,18,23;,
	3;18,24,19;;

	MeshMaterialList {
		1;1;0;;
		{n_01___Default}
	}

	MeshNormals {
		1; // 1 normals
		0.000000;1.000000;0.000000;;

		32;		// 32 faces
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;,
		3;0,0,0;;
	}  // End of Normals

	MeshTextureCoords {
		25; // 25 texture coords
		0.000000;1.000000;,
		0.250000;1.000000;,
		0.500000;1.000000;,
		0.750000;1.000000;,
		1.000000;1.000000;,
		0.000000;0.750000;,
		0.250000;0.750000;,
		0.500000;0.750000;,
		0.750000;0.750000;,
		1.000000;0.750000;,
		0.000000;0.500000;,
		0.250000;0.500000;,
		0.500000;0.500000;,
		0.750000;0.500000;,
		1.000000;0.500000;,
		0.000000;0.250000;,
		0.250000;0.250000;,
		0.500000;0.250000;,
		0.750000;0.250000;,
		1.000000;0.250000;,
		0.000000;0.000000;,
		0.250000;0.000000;,
		0.500000;0.000000;,
		0.750000;0.000000;,
		1.000000;0.000000;;
	}  // End of texture coords
} // End of Mesh
} // End of frame for 'Plane02'
} // End of "World" frame
