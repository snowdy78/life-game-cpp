#pragma once
namespace rn
{
	class MonoBehaviour
	{
	public:
		MonoBehaviour() = default;
		MonoBehaviour(MonoBehaviour &&) = default;
		MonoBehaviour(const MonoBehaviour &) = default;
		virtual ~MonoBehaviour() = 0;
		virtual void start() {}
		virtual void update() {}
		virtual void onEvent(sf::Event &event) {}
		MonoBehaviour &operator=(MonoBehaviour &&) = default;
		MonoBehaviour &operator=(const MonoBehaviour &) = default;
	};
	inline MonoBehaviour::~MonoBehaviour() = default;

}
