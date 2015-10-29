#pragma once

namespace cubey2 {
	template<typename ServiceT>
	class ServiceLocator {
	public:
		static ServiceT* service() {
			return service_;
		}

		static void set_service(ServiceT* _service) {
			service_ = _service;
		}
	private:
		static ServiceT* service_;
	};

	template<typename ServiceT>
	ServiceT* ServiceLocator<ServiceT>::service_ = nullptr;
}