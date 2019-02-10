#pragma once

#include <quartz/core/Core.hpp>

#include <functional>

namespace qz
{
	namespace events
	{
		enum class EventType
		{
			NONE,
			WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LOST_FOCUS,
			APP_TICK, APP_UPDATE, APP_RENDER,
			KEY_PRESSED, KEY_RELEASED,
			MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_CURSOR_MOVED, MOUSE_SCROLLED
		};

		enum EventCategory : int
		{
			NONE = 0,
			APPLICATION		= 1 << 0,
			INPUT			= 1 << 1,
			KEYBOARD		= 1 << 2,
			MOUSE			= 1 << 3,
			MOUSE_BUTTON	= 1 << 4,
		};

#		define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; } \
										EventType getEventType() const override { return EventType::type; } \

#		define EVENT_CLASS_CATEGORY(category) int getCategoryFlags() const override { return category; }

		class QZ_API Event
		{
		public:
			virtual ~Event() = default;

			virtual EventType getEventType() const = 0;
			virtual int getCategoryFlags() const = 0;

			bool isInCategory(EventCategory category) const { return getCategoryFlags() & category; }

		protected:
			bool m_handled = false;

		private:
			friend class EventDispatcher;
		};

		class QZ_API EventDispatcher
		{
			template <typename T>
			using EventFunc = std::function<bool(T&)>;

		public:
			EventDispatcher(Event& event) : m_event(event) {}

			template <typename T>
			bool dispatch(EventFunc<T> func)
			{
				if (m_event.getEventType() == T::getStaticType())
				{
					m_event.m_handled = func(*static_cast<T*>(&m_event));
					return true;
				}

				return false;
			}

		private:
			Event& m_event;
		};
	}
}