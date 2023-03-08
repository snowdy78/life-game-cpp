#pragma once

namespace rn
{
	class Curve : public sf::VertexArray
	{
		float step;
		std::vector<Vec2f> edges;
	public:
		Curve(const std::vector<Vec2f> &edges);
		void setEdges(const std::vector<Vec2f> &edges);
		void setEdge(const Vec2f &vertex, size_t index);
		void addEdge(const Vec2f &v);
		Vec2f getPoint(float percent) const { return count_points(edges, percent); }
		std::vector<Vec2f> getEdges() const { return edges; }
		void resize(const size_t &count);
	private:
		void recount();
		static Vec2f count_points(const std::vector<Vec2f> &edges, const float &t);
	};
	inline Curve::Curve(const std::vector<Vec2f> &edges) : VertexArray(sf::LineStrip, 25)
	{
		this->edges = edges;
		resize(getVertexCount());
	}
	inline void Curve::setEdges(const std::vector<Vec2f> &edges)
	{
		this->edges = edges;
		resize(getVertexCount());
	}
	inline void Curve::resize(const size_t &count)
	{
		VertexArray::resize(count);
		step = 1.f / static_cast<float>(getVertexCount());
		recount();
	}
	inline void Curve::recount()
	{
		size_t i = 0;
		for (float t = 0.f; t < 1.0f; t = std::clamp(t + step, 0.0f, 1.0f))
		{
			(*this)[i++].position = count_points(edges, t);
		}
	}
	inline void Curve::addEdge(const Vec2f &v)
	{
		edges.push_back(v);
		recount();
	}
	inline void Curve::setEdge(const Vec2f &vertex, size_t index)
	{
		edges.at(index) = vertex;
		recount();
	}
	inline Vec2f Curve::count_points(const std::vector<Vec2f> &edges, const float &t)
	{
		std::vector<Vec2f> next_points;
		if (edges.empty())
			return {0, 0};
		if (edges.size() == 1)
			return edges[0];
		for (size_t i = 0, j = 1; j < edges.size(); i++, j++)
		{
			auto &p1 = edges[i];
			auto &p2 = edges[j];
			const float &x1 = p1.x, x2 = p2.x;
			const float &y1 = p1.y, y2 = p2.y;
			float x3 = x1 + (x2 - x1) * t;
			float y3 = y1 + (y2 - y1) * t;
			next_points.emplace_back(x3, y3);
		}
		return count_points(next_points, t);
	}
}


