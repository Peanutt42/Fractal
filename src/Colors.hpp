#pragma once

using ColorFunc = std::function<sf::Color(double iterations, int max_iterations)>;

sf::Color greyscale(double iterations, int max_iterations) {
	int value = 255 * (1.0 - iterations / max_iterations);
	return sf::Color(value, value, value);
}

sf::Color blue(double iterations, int max_iterations) {
	double value = iterations / max_iterations;
	return sf::Color(65 * value, 90 * value, 160 * value);
}


sf::Color fromHsl(float hue, float saturation, float lightness);

sf::Color colorful(double iterations, int max_iterations) {
	double hue = std::fmod(iterations * 10.0, 360.0);
	double lightness = 0.5 + std::log(1.0 + iterations) / std::log(1.0 + max_iterations);

	return fromHsl(hue, 1.0, lightness);
}


sf::Color fromHsl(float hue, float saturation, float lightness) {
	// Ensure hue is in the range [0, 360]
	hue = fmod(hue, 360.0f);
	if (hue < 0.0f) {
		hue += 360.0f;
	}

	// Ensure saturation and lightness are in the range [0, 1]
	saturation = std::max(0.0f, std::min(1.0f, saturation));
	lightness = std::max(0.0f, std::min(1.0f, lightness));

	// If the saturation is close to zero, the color is a shade of gray
	if (saturation < 0.00001f) {
		uint8_t grayValue = static_cast<uint8_t>(lightness * 255.0f);
		return sf::Color(grayValue, grayValue, grayValue);
	}

	float q = (lightness < 0.5f) ? (lightness * (1.0f + saturation)) : (lightness + saturation - lightness * saturation);
	float p = 2.0f * lightness - q;

	float hk = hue / 360.0f;

	// Convert HSL to RGB using the specified formula
	float tr = hk + 1.0f / 3.0f;
	float tg = hk;
	float tb = hk - 1.0f / 3.0f;

	auto hueToRGB = [&](float t) {
		if (t < 0.0f) t += 1.0f;
		if (t > 1.0f) t -= 1.0f;
		if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
		if (t < 0.5f) return q;
		if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
		return p;
		};

	uint8_t red = static_cast<uint8_t>(hueToRGB(tr) * 255.0f);
	uint8_t green = static_cast<uint8_t>(hueToRGB(tg) * 255.0f);
	uint8_t blue = static_cast<uint8_t>(hueToRGB(tb) * 255.0f);

	return sf::Color(red, green, blue);
}