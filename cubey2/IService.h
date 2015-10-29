#pragma once

#include "ServiceLocator.h"

namespace cubey2 {
	template<typename ServiceT>
	class IService {
	public:
		virtual ~IService() {}

		virtual void Init() {}
		virtual void Destroy() {}

		template<typename ServiceName = ServiceT>
		static void InitService(ServiceName* _new_service = nullptr) {
			ServiceT* old_service = ServiceLocator<ServiceT>::service();

			if (old_service && old_service != _new_service) {
				old_service->Destroy();
				delete old_service;
			}

			if (!_new_service) {
				_new_service = new ServiceName();
				_new_service->Init();
			}
			
			ServiceLocator<ServiceT>::set_service(_new_service);
		}

		static ServiceT* GetInstance() {
			return ServiceLocator<ServiceT>::service();
		}
	};
}