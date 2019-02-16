#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/math/Math.hpp>
#include <quartz/core/events/Event.hpp>
#include <quartz/core/events/EventEnums.hpp>

namespace qz
{
	namespace events
	{
		class QZ_API MouseMovedEvent : public Event
		{
		public:
			MouseMovedEvent(const Vector2 pos) : m_mousePos(pos) {}

			Vector2 getPos() const { return m_mousePos; }

			EVENT_CLASS_TYPE(MOUSE_CURSOR_MOVED);
			EVENT_CLASS_CATEGORY(EventCategory::MOUSE | EventCategory::INPUT);

		private:
			Vector2 m_mousePos;
		};

		class QZ_API MouseScrolledEvent : public Event
		{
		public:
			MouseScrolledEvent(const Vector2 scrollOffset) : m_mouseScrollWheelOffset(scrollOffset) {}

			Vector2 getOffset() const { return m_mouseScrollWheelOffset; };

			EVENT_CLASS_TYPE(MOUSE_SCROLLED);
			EVENT_CLASS_CATEGORY(EventCategory::MOUSE | EventCategory::INPUT);

		private:
			Vector2 m_mouseScrollWheelOffset;
		};

		class QZ_API MouseButtonEvent : public Event
		{
		public:
			MouseButton getMouseButton() const { return m_button; }
			Vector2 getButtonEventPos() const { return m_buttonEventPos; };

			EVENT_CLASS_CATEGORY(EventCategory::MOUSE | EventCategory::INPUT);

		protected:
			MouseButtonEvent(const MouseButton button, const Vector2 pos) : m_button(button), m_buttonEventPos(pos) {}

			MouseButton m_button;
			Vector2 m_buttonEventPos;
		};

		class QZ_API MouseButtonPressedEvent : public MouseButtonEvent
		{
		public:
			MouseButtonPressedEvent(const MouseButton button, const Vector2 pressPos) : MouseButtonEvent(button, pressPos) {}

			EVENT_CLASS_TYPE(MOUSE_BUTTON_PRESSED);
		};

		class QZ_API MouseButtonReleasedEvent : public MouseButtonEvent
		{
		public:
			MouseButtonReleasedEvent(const MouseButton button, const Vector2 releasePos) : MouseButtonEvent(button, releasePos) {}

			EVENT_CLASS_TYPE(MOUSE_BUTTON_RELEASED);
		};
	}
}
