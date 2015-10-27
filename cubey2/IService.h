#pragma once

#include "ServiceLocator.h"

namespace cubey2 {
	template<typename ServiceType, typename ServiceName>
	class IService {
	public:
		virtual ~IService() {}

		virtual void Init() {}
		virtual void Destroy() {}

		static void InitService() {
			ServiceName* new_service = new ServiceName();
			new_service->Init();
			ServiceLocator<ServiceType>::set_service(new_service);
		}
	};
}