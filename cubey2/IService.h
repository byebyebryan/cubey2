#pragma once

#include "ServiceLocator.h"

namespace cubey2 {
	template<typename ServiceType, typename ServiceName>
	class IService {
	public:
		static void InitService() {
			ServiceLocator<ServiceType>::set_service(new ServiceName);
		}
	};
}