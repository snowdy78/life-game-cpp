#pragma once
#include <vector>

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
		Vec2f getPoint(float percent) const;
		std::vector<Vec2f> getEdges() const;
		void resize(const size_t &count);
	private:
		void recount();
		static Vec2f count_points(const std::vector<Vec2f> &edges, const float &t);
	};
	
}


