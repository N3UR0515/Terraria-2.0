#pragma once

//http://www.arendpeter.com/Perlin_Noise.html

#include <cmath>

class Noise
{
public:
	//Perlin Noise
	static float PerlinNoise_1D(float x, float freq, float ampl) // 1 octave!
	{
		float total = 0;

		int frequency = int(freq);
		int amplitude = int(ampl);

		total += InterpolatedNoise(x * float(frequency)) * float(amplitude);

		return total;
	}

	static float PerlinNoise_1DWithCubic(float x, float freq, float ampl) // 1 octave!
	{
		float total = 0;

		int frequency = int(freq);
		int amplitude = int(ampl);

		total += InterpolatedNoiseWithCubic(x * float(frequency)) * float(amplitude);

		return total;
	}

	//This is nothing important
	static float map(float n, float start1, float start2, float stop1, float stop2)
	{
		return ((n - start1) / (stop1 - start1)) * (stop2 - start2) + start2;
	}
private:
	//Noise
	static float IntNoise(int x)
	{
		x = (x << 13) ^ x;
		return (1.0f - ((x * (x * x * 15731 + 789221) + 1376312589)) / 1073741824);
	}

	static float SmoothNoise(float x)
	{
		return IntNoise(int(x)) / 2 + IntNoise(int(x) - 1) / 4 + IntNoise(int(x) + 1) / 4;
	}

	//Interpolation
	static float Cosine_Interpolate(float a, float b, float x)
	{
		float ft = x * 3.1415927f;
		float f = (1 - cos(ft)) * 0.5f;

		return  a * (1 - f) + b * f;
	}

	static float Cubic_Interpolation(float v0, float v1, float v2, float v3, float x)
	{
		float P = (v3 - v2) - (v0 - v1);
		float Q = (v0 - v1) - P;
		float R = v2 - v0;
		float S = v1;

		return P * pow(x, 3) + Q * pow(x, 2) + R * x + S;
	}

	//InterpolatedNoiseWithCosineInterpolation
	static float InterpolatedNoise(float x)
	{
		int integer_X = int(x);
		float fractional_X = x - integer_X;

		float v1 = SmoothNoise(float(integer_X));
		float v2 = SmoothNoise(float(integer_X + 1));

		return Cosine_Interpolate(v1, v2, fractional_X);
	}
public:
	//InterpolatedNoiseWithCubicInterpolation
	static float InterpolatedNoiseWithCubic(float x)
	{
		int integer_X = int(x);
		float fractional_X = x - integer_X;

		float v0 = SmoothNoise(float(integer_X - 1));
		float v1 = SmoothNoise(float(integer_X));
		float v2 = SmoothNoise(float(integer_X + 1));
		float v3 = SmoothNoise(float(integer_X + 1));

		return Cubic_Interpolation(v0, v1, v2, v3, fractional_X);

	}
};