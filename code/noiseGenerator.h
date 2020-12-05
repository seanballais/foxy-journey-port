#pragma once
#include <deque>
#include <vector>

static void generateNoise(const std::deque<float> &seed, std::deque<float> & result, int octaves, float bias)
{
	result.clear();

	for (int i = 0; i < seed.size(); i++)
	{
		float noise = 0.0f;

		float scaleFactor = 1.0f;

		float accumulatedScale = 0.0f;

		for (int octave = 0; octave < octaves; octave++)
		{
			int pitch = seed.size() >> octave;

			int firstSample = (i / pitch) * pitch;

			int secondSample = (firstSample + pitch) % seed.size();

			float blend = (float)(i - firstSample) / (float)pitch;

			float sample = (1.0f - blend) * seed[firstSample] + blend * seed[secondSample];

			accumulatedScale += scaleFactor;
			noise += sample * scaleFactor;
			scaleFactor = scaleFactor / bias;

		}
		
		result.push_back(noise / accumulatedScale);

	}
}



