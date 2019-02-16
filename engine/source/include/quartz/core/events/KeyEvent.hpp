#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/events/Event.hpp>
#include <quartz/core/events/EventEnums.hpp>

namespace qz
{
	namespace events
	{
		class QZ_API KeyEvent : public Event
		{
		public:
			Key getKeyCode() const { return m_keyCode; }

			EVENT_CLASS_CATEGORY(EventCategory::KEYBOARD | EventCategory::INPUT);

		protected:
			KeyEvent(const Key keycode) : m_keyCode(keycode) {}

			Key m_keyCode;
		};

		class QZ_API KeyPressedEvent : public KeyEvent
		{
		public:
			KeyPressedEvent(const Key keycode, const int repeatCount)
				: KeyEvent(keycode), m_repeatCount(repeatCount) {}

			int getRepeatCount() const { return m_repeatCount; }

			EVENT_CLASS_TYPE(KEY_PRESSED);

		private:
			int m_repeatCount;
		};

		class QZ_API KeyReleasedEvent : public KeyEvent
		{
		public:
			KeyReleasedEvent(const Key keycode)
				: KeyEvent(keycode) {}

			EVENT_CLASS_TYPE(KEY_RELEASED);
		};
	}
}
