#pragma once

#include <functional>
#include <map>

#include "IDGenerator.h"

namespace cubey2 {

	struct IEvent {
		void* sender = nullptr;
	};

	template<typename EventT>
	class EventLisenter {
	public:
		EventLisenter() :
				id_(0),
				is_active_(true) {}

		EventLisenter(const std::function<void(const EventT&)>& _handler_func) : 
				id_(IDGenerator<EventT>::NextID()),
				is_active_(true),
				handler_func_(_handler_func) {}

		~EventLisenter() {
			RemoveFromChannel();
		}

		void PushToChannel();
		void RemoveFromChannel();

		UID id_;
		bool is_active_;
		std::function<void(const EventT&)> handler_func_;
	};

	template<typename EventT>
	class EventChannel {
	public:
		static void Add(const EventLisenter<EventT>& _listener) {
			if (listeners_.find(_listener.id_) == listeners_.end()) {
				listeners_[_listener.id_] = _listener;
			}
		}

		static EventLisenter<EventT> Add(const std::function<void(const EventT&)>& _handler_func) {
			EventLisenter<EventT> new_listener(_handler_func);
			Add(new_listener);
			return new_listener;
		}

		static void Broadcast(const EventT& _event) {
			if (!is_muted_) {
				for (auto it = listeners_.rbegin(); it != listeners_.rend(); ++it) {
					if (it->second.is_active_) {
						it->second.handler_func_(_event);
					}
				}
			}
		}

		static void Broadcast(std::initializer_list<EventT> init_list) {
			EventT e(init_list);
			Broadcast(e);
		}

		static void Remove(const EventLisenter<EventT>& _listener) {
			listeners_.erase(_listener.id_);
		}

		static void Mute() {
			is_muted_ = true;
		}

		static void Unmute() {
			is_muted_ = false;
		}

	private:
		static std::map<UID, EventLisenter<EventT>> listeners_;
		static bool is_muted_;
	};

	template <typename EventT>
	std::map<UID, EventLisenter<EventT>> EventChannel<EventT>::listeners_;

	template <typename EventT>
	bool EventChannel<EventT>::is_muted_ = false;

	template <typename EventT>
	void EventLisenter<EventT>::PushToChannel() {
		EventChannel<EventT>::Add(*this);
	}

	template <typename EventT>
	void EventLisenter<EventT>::RemoveFromChannel() {
		EventChannel<EventT>::Remove(*this);
	}

}