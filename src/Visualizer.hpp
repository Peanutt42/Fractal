#pragma once

#include "Fractals.hpp"
#include "Colors.hpp"
#include "ThreadPool.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cassert>
#include <functional>

inline double clamp(double min, double max, double value) {
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

class Visualizer {
public:
	Visualizer(uint32_t width, uint32_t height, int max_iterations)
		: m_Width(width), m_Height(height), m_MaxIterations(max_iterations)
	{
		Resize(m_Width, m_Height);
	}

	void Resize(uint32_t width, uint32_t height) {
		m_Width = width;
		m_Height = height;
		m_Image.create({ m_Width, m_Height }, sf::Color::Black);
	}

	void Zoom(int x, int y, double amount) {
		double factor = 1.0 + (amount * 0.1);
		m_OffsetX -= (x - (m_Width / 2.0)) / m_Zoom * ((1.0 / factor) - 1.0);
		m_OffsetY -= (y - (m_Height / 2.0)) / m_Zoom * ((1.0 / factor) - 1.0);
		m_Zoom *= factor;
	}

	void Pan(double deltaX, double deltaY) {
		m_OffsetX -= deltaX / m_Zoom;
		m_OffsetY -= deltaY / m_Zoom;
	}

	void Update(const FractalFunc& fractalFunc, const ColorFunc& colorFunc) {
		assert(m_Image.getSize() == sf::Vector2u(m_Width, m_Height));
		for (uint32_t x = 0; x < m_Width; ++x) {
			if (m_MultithreadingEnabled) {
				m_ThreadPool.add([this, x, fractalFunc, colorFunc] {
					Work(x, fractalFunc, colorFunc);
                });
			}
			else
				Work(x, fractalFunc, colorFunc);
		}

		if (m_MultithreadingEnabled)
			m_ThreadPool.wait();
	}

	void Draw(sf::RenderWindow& window) {
		m_Texture.setSmooth(true);
		if (m_Image.getSize() != m_Texture.getSize()) {
			if (!m_Texture.loadFromImage(m_Image))
				std::cout << "Failed to load texture from image!\n";
		}
		else
			m_Texture.update(m_Image);

		sf::Sprite sprite(m_Texture);
		window.draw(sprite);
	}

	void SaveToFile(const std::filesystem::path& filepath) const {
		if (!m_Image.saveToFile(filepath))
			std::cout << "Failed to save output to " << filepath.string() << std::endl;
	}

	void SetMultithreading(bool enabled) { m_MultithreadingEnabled = enabled; }

	void SetMaxIterations(int maxIterations) { m_MaxIterations = maxIterations; }
	int GetMaxIterations() const { return m_MaxIterations; }

private:
	void Work(uint32_t x, const FractalFunc& fractalFunc, const ColorFunc& colorFunc) {
		for (uint32_t y = 0; y < m_Height; ++y) {
			double new_x = (((x - m_Width / 2.0) / m_Zoom) + m_OffsetX);
			double new_y = (((y - m_Height / 2.0) / m_Zoom) + m_OffsetY);

			double result = fractalFunc(new_x, new_y, m_MaxIterations);
			if ((int)result == m_MaxIterations)
				m_Image.setPixel({ x,y }, sf::Color::Black);
			else
				m_Image.setPixel({ x, y }, colorFunc(std::abs(result), m_MaxIterations));
		}
	}

private:
	sf::Image m_Image;
	sf::Texture m_Texture;

	bool m_MultithreadingEnabled = true;
	ThreadPool m_ThreadPool;

	uint32_t m_Width = 0, m_Height = 0;
	int m_MaxIterations = 0;

	double m_OffsetX = 0.0, m_OffsetY = 0.0;
	double m_Zoom = 1.0;
};