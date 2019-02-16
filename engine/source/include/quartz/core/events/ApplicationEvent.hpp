#pragma once

#include <quartz/core/Core.hpp>
#include <quartz/core/events/Event.hpp>

namespace qz
{
	namespace events
	{
		class QZ_API WindowCloseEvent : public Event
		{
		public:
			WindowCloseEvent() = default;

			EVENT_CLASS_TYPE(WINDOW_CLOSE);
			EVENT_CLASS_CATEGORY(EventCategory::APPLICATION);
		};

		class QZ_API WindowResizeEvent : public Event
		{
		public:
			WindowResizeEvent(const unsigned int width, const unsigned int height) : m_width(width), m_height(height) {}

			unsigned int getWidth() const { return m_width; }
			unsigned int getHeight() const { return m_height; }

			EVENT_CLASS_TYPE(WINDOW_RESIZE);
			EVENT_CLASS_CATEGORY(EventCategory::APPLICATION);

		private:
			unsigned int m_width;
			unsigned int m_height;
		};

		class QZ_API WindowFocusEvent : public Event
		{
		public:
			WindowFocusEvent() = default;

			EVENT_CLASS_TYPE(WINDOW_FOCUS);
			EVENT_CLASS_CATEGORY(EventCategory::APPLICATION);
		};

		class QZ_API WindowLostFocusEvent : public Event
		{
		public:
			WindowLostFocusEvent() = default;

			EVENT_CLASS_TYPE(WINDOW_LOST_FOCUS);
			EVENT_CLASS_CATEGORY(EventCategory::APPLICATION);
		};

		class QZ_API AppTickEvent : public Event
		{
		public:
			AppTickEvent() = default;

			EVENT_CLASS_TYPE(APP_TICK);
			EVENT_CLASS_CATEGORY(EventCategory::APPLICATION);
		};

		class QZ_API AppUpdateEvent : public Event
		{
		public:
			AppUpdateEvent() = default;

			EVENT_CLASS_TYPE(APP_UPDATE);
			EVENT_CLASS_CATEGORY(EventCategory::APPLICATION);
		};

		class QZ_API AppRenderEvent : public Event
		{
		public:
			AppRenderEvent() = default;

			EVENT_CLASS_TYPE(APP_RENDER);
			EVENT_CLASS_CATEGORY(EventCategory::APPLICATION);
		};
	}
}
